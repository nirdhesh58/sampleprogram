//
// Included Files
//
#include "f28x_project.h"
#include <stdio.h>
#include <math.h> // For sine and cosine functions, and M_PI
#include <srm/MKadc.h>
#include <srm/MKpwm.h>
#include <stdbool.h> // For boolean types
#include <srm/SignalProcessing.h>
#include <srm/VirtualEncoder.h>
#include <srm/ISR.h>
#include <srm/AngleConversion.h>
#include <srm/remote.h>
#include <srm/SwitchConfiguration.h>
#include <srm/SwitchStateMachine.h>
#include <srm/Constants.h>
#include <srm/SpeedRegulation.h>
#include <srm/LockTest.h>

void InitDAC(void);
void InitTimer1ForRpm(void);
void InitTimer0ForRemote(void);
void InitTimer2ForVirtual(void);
void triggerCoversions(void);
float getTargetAngle(float theta);
inline double ProcessAdcValues(void);
void RpmCalculation(double currentTheta);
void handleButtonPress(void);
void motorRunningCode_withBlades(double theta);
void motorRunningCode_withoutBlades(double theta);
/**
 * @brief Initializes the system, including device clock, peripherals, GPIO, and interrupts.
 *
 * This function performs the necessary initializations for the system clock,
 * GPIO pins, ADCs, PWMs, and interrupt vector table. It also disables all PWMs initially
 * and maps the interrupt service routines to the corresponding interrupt vectors.
 */
void systemSetup(void) {
    // Previous initialization code...
#ifdef _FLASH

memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
#endif
    InitSysCtrl();
    // DisableDog();
    // Initialize GPIO
   // MKinitGPIO();
    MKinitGPIO_CNDR();
  //  MKinitGPIO_CNDR();
   // MKinitGPIOLaunchpad();
    // Disable CPU interrupts
    DINT;

    // Initialize the PIE control registers to their default state.
    InitPieCtrl();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt Service Routines (ISR).
    InitPieVectTable();
    // Configure the ADC, ePWM, SCI modules
    MKinitAdc();
    InitDAC();
    MKintItPwm4();      //H1+L1
    MKintItPwm1();      //H2+L2
    MKintItPwm6();      //H3+L3
    MKintItPwm2();      //H4+L4
    MKintItPwm7();    // buzzer
    // PWM Off
    EALLOW;
    EPwm4Regs.TZFRC.bit.OST = 1;
    EPwm6Regs.TZFRC.bit.OST = 1;
    EPwm2Regs.TZFRC.bit.OST = 1;
    EPwm1Regs.TZFRC.bit.OST = 1;
    EDIS;
    MKintItPwm5();  // for sampling @40khz

    /////////////////Cpu timer0 for remote/////////////////////////////
    InitTimer0ForRemote();   //timer 0 for remote
    InitTimer1ForRpm();      // timer 1 for rpm calculation
    InitTimer2ForVirtual();    // timer 2 for Virtual encoder
    Cmpss1Regs.DACLVALS.bit.DACVAL=2048;
    // Enable individual interrupts and assign ISR functions
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;
    EALLOW;
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1; // ADC A interrupt
    PieCtrlRegs.PIEIER1.bit.INTx2 = 1; // ADC C interrupt
    PieCtrlRegs.PIEIER3.bit.INTx5 = 1; // EPwm 5 interrupt
    PieCtrlRegs.PIEIER1.bit.INTx7=1;     //timer0

    // Map ISR functions
    PieVectTable.ADCA1_INT = &CosineSamplingIsr;       // ISR function for cosine sampling
    PieVectTable.ADCC1_INT = &SineSamplingIsr;         // ISR function for sine sampling
    PieVectTable.EPWM5_INT = &TriggerAdcSamplingIsr;  // Function for PWM5 interrupt, renamed
    PieVectTable.TIMER0_INT=&Timer0ForRemote;
    PieVectTable.TIMER1_INT=&Timer1ForRPM;
    PieVectTable.TIMER2_INT=&Timer2ForVirtual;
    EDIS;

    // Enable global Interrupts and higher priority real-time debug events:
    IER |= M_INT1 | M_INT8 | M_INT9 | M_INT14 | M_INT3 | M_INT13 |  M_INT10;
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM
}

//////Global variables/////////


volatile uint16_t CosNegative=0,CosPositive=0,SinPositive=0,SinNegative=0;
volatile bool isSineSampleComplete = false;
volatile bool isCosineSampleComplete = false;
SignalProcessorState sineState, cosineState;
// Global variable for target angle

volatile double stateBoudnaries[12];
 StateMachine stateMachine;

// Manually Tuneable Params

 double PwmPeriod=1/(PWM_Frequency*SystemBaseClk);
volatile double OnePercentDuty=1/(PWM_Frequency*SystemBaseClk*100);
volatile uint16_t PwmDutyCycle1=(DefaultDuty_percent*(1/(PWM_Frequency*SystemBaseClk*100))), PwmDutyCycle2=0, PwmDutyCycle3=0;    //180 count = 1%

volatile double Pwm1DutyPercent, Pwm2DutyPercent, Pwm3DutyPercent;
volatile double ConductionAngle=0, OverlapAngle=0, AdvanceAngle=0, ConductionAngle2=0;//(0.61);
volatile int PowerOn;
volatile int SwitchPressed=0;
int isTimerInitialized = 0;
double RPM=0;
//volatile double mechanicalOffset=-2.89454;//2.9452;//-2.362432;//-2.9452;//-2.363553;//-3.130575;//-2.9452; //M38=-2.9511;//M37=-2.9452;//-3.06315;//M33=-2.9467;//2.89145;//-2.90815;//-3.0031;//2.9331;//2.918;//2.934;//2.7207;//2.0924;//M29=2.084816;//1.456506;//2.084816;//1.456506;//2.63191;//(1.37529);
int BuzzerOn=0;
volatile uint16_t BuzzerCount=0;

//////added for virtual
volatile double angleOfInterest = 0.0f;
volatile int currentBoundary = -1;
volatile int VitualTimerStarted=0;
volatile int StartVirtual=0;
volatile int sampleCounter = 0;
volatile int VirtualencoderStarted=0;
//////////////////////Rpm/////////
volatile bool triggerAllowed = true;  // Flag to allow triggering when theta crosses zero
volatile double samplingCountFactor=0;
volatile int numSamplesToconsider=0;
volatile double previousFirstZeroValue=0;
/////////////for 5speed and regulation//////////////////
uint16_t SetSpeed=0,CurrentSpeed=0,SetRPM=0,CurrentRpm=0;
uint16_t SetPwmDuty1=0;
uint16_t StepSize_Duty1=0;
volatile int RemoteRegulation=0;
volatile int remote_RegulationStep=0;
uint16_t SetPwmDutyCycle1=0;
volatile int startSpeedRegulation=0;
///////////for blade and without blades//////////
volatile bool isWithoutBlades = false;

/////////////////for lock test////////////////////////////
double mechanicalAngle=0.0;
int retryCount = 0;
double initialAngle = 0.0;
double angleMoved = 0.0;
uint32_t loopCounter = 0;
int LockTimerON=0;
volatile int LockCount=0;
int ReadRemote=1;
////////////added for debug//////
double x,y,z=(1/(PWM_Frequency*SystemBaseClk)),A,B,C,D,E,F,Aa;
double TestAngle=0;
double adv;
uint32_t count=0,count1=0;
//////////////end Global Variables/////////////////


/**
 * @brief Main function of the program.
 *
 * Sets up the system and then enters an infinite loop where the main operational
 * logic of the program would reside. Currently, it only sets a flag in the loop.
 */
void main(void) {
    systemSetup();
    ConductionAngle= degreesToRadians(40);
    ConductionAngle2=degreesToRadians(5);
    OverlapAngle=degreesToRadians(1);
    initializeSignalProcessor(&sineState);
    initializeSignalProcessor(&cosineState);
  //  initVirtualEncoder(&virtualEncoder);
    //initializeAngleConstants();
//x=radiansToDegrees(1);
    initStateFunctions(&stateMachine);
    computeBoundaries(OverlapAngle, ConductionAngle,ConductionAngle2, stateBoudnaries);
     updateStateBoundaries(&stateMachine, stateBoudnaries);
     sineState.lastMax=sineState.max=sineState.trackingMax= 1020;
     sineState.lastMin=sineState.min=sineState.trackingMin=-1088;

     cosineState.lastMax=cosineState.max=cosineState.trackingMax=1131;
     cosineState.lastMin=cosineState.min=cosineState.trackingMin=-980;
  //  setFiring(&stateMachine, 1);
    
          samplingCountFactor=60/(RotorPoles*SamplingTime);
    while(1) {

        // Check if both ADC readings are complete
        if (isSineSampleComplete && isCosineSampleComplete){
           // z=ConductionAngle1_Max_Limit;
          //  GpioDataRegs.GPATOGGLE.bit.GPIO29=1;
            double theta = ProcessAdcValues();
            checkRpmTriggerAtBoundary(theta);  // Handle RPM start timing
          //  handleButtonPress();
                 if (stateMachine.isFirstTargetSet == 0) {
                            setCurrentStateByAngle(&stateMachine, theta);
                        }

                        // Choose the transition function based on RPM
                 if(isWithoutBlades)
                 {
                     motorRunningCode_withoutBlades(theta);
                 }
                 else
                 {
                  motorRunningCode_withBlades(theta);
                 }
                 ///////////////////////////////////////////////////////////////////////////////////
                     if (stateMachine.StartTimer == 1) {
                              RpmCalculation(theta);
                              numSamplesToconsider=samplingCountFactor/RPM;

                            if ((RPM>150)&&(SetRPM!=RPM)&&(RemoteRegulation==0)&&(isWithoutBlades==0))
                             {
                                control_rpm(SetRPM,RPM);
                            }
                     }

              GetDataFromRemote(); // extract data from remote in case if user press button
              if(BuzzerOn==1)
               {
                  BuzzerCount++;
                  if(BuzzerCount>=40000)        //1 sec count
                  {
                      EPwm7Regs.CMPA.bit.CMPA = 0;   // turn off buzzer
                      BuzzerCount=0;
                      BuzzerOn=0;      // controller is ready to read RF data after 1 sec
                  }
               }
             else
              {
                 if(ReadRemote==1)
                        {
               RFsignalCalculate();
                        }
               }

    // GpioDataRegs.GPATOGGLE.bit.GPIO29=1;
   //  GpioDataRegs.GPADAT.bit.GPIO16=0;
    }
}

}
inline double ProcessAdcValues(void) {
        // Process the ADC values here
        isSineSampleComplete = false;
        isCosineSampleComplete = false;

        signed int openEndedCoSine = (CosPositive-CosNegative);
        signed int openEndedSine = (SinPositive-SinNegative);


        // Filter and process signals

        double filteredSine = processSignal(&sineState, openEndedSine);
        double filteredCosine = processSignal(&cosineState, openEndedCoSine);

        double mechAngle = atan2(filteredSine, filteredCosine);

        x=mechAngle;

//        uint32_t count=CpuTimer0Regs.TIM.all;
//       uint32_t count1 =(2000000/( 2*PI))*(x+PI);
//        if(count>count1)
//        {
//            GpioDataRegs.GPADAT.bit.GPIO16=0;
//        }
//        else
//        {
//            GpioDataRegs.GPADAT.bit.GPIO16=1;
//        }

     //   GpioDataRegs.GPADAT.bit.GPIO29=0;
    //    Cmpss1Regs.DACLVALS.bit.DACVAL=(x+PI)*500;
        mechAngle-=mechanicalOffset;

        // Normalize the angle to be within -PI and PI
        mechAngle = fmod(mechAngle + PI, 2 * PI);

        if (mechAngle < 0) {
            mechAngle += 2 * PI;
        }
        mechanicalAngle=mechAngle;
        mechAngle -= PI;

      //  mechAngle = fmod()
    //    Cmpss1Regs.DACLVALS.bit.DACVAL=(x+PI)*500;
        // Convert mechanical angle to electrical angle
        double elecAngle = mechanicalToElectricalRotation(mechAngle, AdvanceAngle);
//z=elecAngle;
    Cmpss1Regs.DACLVALS.bit.DACVAL=elecAngle*500;

    if((RPM>RPM_THRESHOLD_LOW_VIRTUAL)&&(RPM<RPM_THRESHOLD_High))
    {
    virtualEncoder(elecAngle);
    }
    else
    {
        sampleCounter=0;
        VirtualencoderStarted=0;
    }
        return elecAngle;
}



void InitDAC(void)
{
    EALLOW;
    AnalogSubsysRegs.CMPSSCTL.bit.CMPSSCTLEN=1;
    AnalogSubsysRegs.CMPSSCTL.bit.CMP1LDACOUTEN=1;
    Cmpss1Regs.COMPCTL.bit.COMPDACE=1;
    EDIS;
}


// Function to initialize one-shot timer
void InitTimer1ForRpm(void) {
    // Initialization code for the timer
    // Configure the timer to trigger an interrupt at the calculated time before the next sampling
    EALLOW;
    CpuTimer1Regs.TCR.bit.TIE=1;
    CpuTimer1Regs.TPR.bit.PSC=0;
   // CpuTimer1Regs.TPR.bit.TDDR=2;
    CpuTimer1Regs.PRD.all=180722892; // period for 1.5sec
    CpuTimer1Regs.TCR.bit.TSS=1;
    CpuTimer1Regs.TCR.bit.TRB = 1;
    CpuTimer1Regs.TCR.bit.FREE=0;
    CpuTimer1Regs.TCR.bit.SOFT=1;
   // CpuTimer1Regs.TCR.bit.TSS=0;
  // count= CpuTimer1Regs.TIM.all;
   EDIS;
}

void InitTimer0ForRemote(void)
{
        EALLOW;
       CpuTimer0Regs.TCR.bit.TIE=1;
       CpuTimer0Regs.TPR.bit.PSC=0;
       CpuTimer0Regs.PRD.all=120722892;    // period for 1 sec
       CpuTimer0Regs.TCR.bit.TSS=1;
       CpuTimer0Regs.TCR.bit.TRB = 1;
       CpuTimer0Regs.TCR.bit.FREE=0;
       CpuTimer0Regs.TCR.bit.SOFT=1;
     //  CpuTimer0Regs.TCR.bit.TSS=0;
       EDIS;
}
void InitTimer2ForVirtual(void)
{
        EALLOW;
       CpuTimer2Regs.TCR.bit.TIE=1;
       CpuTimer2Regs.TPR.bit.PSC=0;
       CpuTimer2Regs.PRD.all=1109; //10us//.5Sec period
       CpuTimer2Regs.TCR.bit.TSS=1;
       CpuTimer2Regs.TCR.bit.TRB = 1;
       CpuTimer2Regs.TCR.bit.FREE=0;
       CpuTimer2Regs.TCR.bit.SOFT=1;
    //   CpuTimer2Regs.TCR.bit.TSS=0; // toStart timer
       EDIS;
}
void RpmCalculation(double currentTheta)
{

  //  GpioDataRegs.GPADAT.bit.GPIO4 = 0;  // Set GPIO4 to 0

    if (isTimerInitialized) {

        // Stop the timer and capture the count
        CpuTimer1Regs.TCR.bit.TSS = 1; // Stop the timer
        uint32_t count = CpuTimer1Regs.TIM.all;  // Get the current count
        CpuTimer1Regs.TCR.bit.TRB = 1;  //reload timer with period value
        CpuTimer1Regs.TCR.bit.TSS = 0; // Start the timer again
        uint32_t elapsedTime = 180722892 - count; // Calculate elapsed time
        double AngleTravelled=currentTheta-previousFirstZeroValue;

        AngleTravelled=AngleTravelled+(2*PI);

        // Calculate the time for one mechanical rotation in seconds
        double rotationTimeSeconds = ((elapsedTime/AngleTravelled)*2*PI) * RotorPoles * 8.3e-9;
        // Calculate RPM
        if(elapsedTime<=12908777)
        {
        double rpm = 60 / rotationTimeSeconds;
        RPM=rpm;
        }
        else
        {
            RPM=0;
        }

        previousFirstZeroValue=currentTheta;

    } else {
        // Just start the timer for the first time
        CpuTimer1Regs.TCR.bit.TSS = 0;
        isTimerInitialized = 1;
    }

    stateMachine.StartTimer = 0;        // Reset StartTimer immediately after using it

}
void handleButtonPress(void)
{
    if((SetSpeed != CurrentSpeed)&&(RemoteRegulation==0))
                             {
                                 uint16_t  diffDuty=0;
                                 if(SetSpeed > CurrentSpeed)
                                 {
                                   diffDuty=SetPwmDutyCycle1-PwmDutyCycle1;
                                 }
                                 else
                                 {
                                   diffDuty=PwmDutyCycle1-SetPwmDutyCycle1;
                                 }
                                 Aa=diffDuty;
                               StepSize_Duty1=diffDuty/20;
                               //Start Timer
                               EALLOW;
                               CpuTimer0Regs.PRD.all=60722892;    // period for 0.5 sec
                               CpuTimer0Regs.TCR.bit.TRB = 1;   //reload
                               CpuTimer0Regs.TCR.bit.TSS=0; //timer startedd
                               EDIS;
                               RemoteRegulation=1;
                             }
}

void motorRunningCode_withBlades(double theta)
{
    if(VirtualencoderStarted==0)
       {
            if (RPM < 20) {
                  if (stateMachine.isFiringON) {
                      PwmDutyCycle1=OnePercentDuty*4;
                      simplifiedTransitionState(&stateMachine, theta);
                      monitorAndRetryAngleMovement(mechanicalAngle);
                  }
              }
            else if(RPM<150)
             {
                  if (stateMachine.isFiringON) {
                      Pwm1DutyPercent=RPM*0.12+3;
                      PwmDutyCycle1=Pwm1DutyPercent*OnePercentDuty;
                      transitionState(&stateMachine, theta);
                     // executeCurrentStateAction(&stateMachine);  // Execute action if RPM > 20 and firing is ON
                  }
              }
       }
       else     // else for virtual Encoder
       {
           if(RPM<150)
            {
             if (stateMachine.isFiringON) {
                 Pwm1DutyPercent=RPM*0.12+3;
                PwmDutyCycle1=Pwm1DutyPercent*OnePercentDuty;
                //  transitionState(&stateMachine, theta);
                    }
             }
           else
           {
                    // have to use button press
               handleButtonPress();
           }
       }
}
void motorRunningCode_withoutBlades(double theta)
{
    if(stateMachine.isFiringON)
    {
    if(RPM<20)
    {
    PwmDutyCycle1=4*OnePercentDuty;
    simplifiedTransitionStateForStart(&stateMachine, theta);
    }
    else if(RPM<RPM_THRESHOLD_LOW_VIRTUAL)
    {
    Pwm1DutyPercent=0.0525*RPM+1.554;
    PwmDutyCycle1=Pwm1DutyPercent*OnePercentDuty;
    transitionState(&stateMachine, theta);
    }
    else if(RPM<SetRPM)
    {
            Pwm1DutyPercent=0.0591*RPM-0.1601;
            PwmDutyCycle1=Pwm1DutyPercent*OnePercentDuty;
    }
if(PwmDutyCycle1>SetPwmDutyCycle1)
{PwmDutyCycle1=SetPwmDutyCycle1;}
    }
}

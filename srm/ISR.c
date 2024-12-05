#include "Globals.h"
#include "f28x_project.h"
#include "remote.h"
#include "SwitchStateMachine.h"
inline void triggerConversions(void);
/**
 * @brief Interrupt Service Routine for cosine sampling.
 * 
 * This ISR is triggered by an ADC conversion completion for the cosine and negative cosine channels.
 * It reads the conversion results, calculates the unfiltered cosine value, and clears the interrupt flag.
 */
__interrupt void CosineSamplingIsr(void) {
    // Read cosine values and clear the interrupt flag
    CosPositive = AdcaResultRegs.ADCRESULT0;
    CosNegative = AdccResultRegs.ADCRESULT0;
    isCosineSampleComplete = true;

    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


/**
 * @brief Interrupt Service Routine for sine sampling.
 * 
 * This ISR handles the ADC conversion completion for the sine and negative sine channels.
 * It reads the conversion results, computes the unfiltered sine value, signals that the angle is ready,
 * and clears the interrupt flag.
 */
__interrupt void SineSamplingIsr(void) {
    // Read sine values and clear the interrupt flag
    SinPositive = AdccResultRegs.ADCRESULT1;
    SinNegative = AdcaResultRegs.ADCRESULT1;
    isSineSampleComplete = true;

    AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

/**
 * @brief Interrupt Service Routine for triggering ADC conversions at a fixed sampling rate.
 * 
 * This ISR is associated with EPWM5 and is triggered at a predefined frequency. It is responsible
 * for manually triggering ADC conversions for both sine and cosine channels at regular intervals.
 */
__interrupt void TriggerAdcSamplingIsr(void) {
    triggerConversions();

    EPwm5Regs.ETCLR.bit.INT = 1;  // Clear the PWM interrupt flag
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;  // Acknowledge the interrupt in the PIE
}

/**
 * @brief Triggers ADC conversions manually for sine and cosine channels.
 * 
 * Sets the start-of-conversion (SOC) flags for the respective ADC channels to begin
 * the conversion process for both sine and cosine measurements.
 */
inline void triggerConversions(void) {
    // Manually trigger ADC SOC for both sine and cosine channels
    AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1; // Trigger conversion for CosPositive
    AdccRegs.ADCSOCFRC1.bit.SOC0 = 1; // Trigger conversion for CosNegative
    AdcaRegs.ADCSOCFRC1.bit.SOC1 = 1; // Trigger conversion for SinNegative
    AdccRegs.ADCSOCFRC1.bit.SOC1 = 1; // Trigger conversion for SinPositive
}

// One-shot Timer ISR for actuation
__interrupt void actuate(void) {
    // Actuation logic based on the targetAngle
    // Update system state or motor control parameters here

    // Clear the timer interrupt flag
    // Acknowledge the interrupt
}
__interrupt void Timer0ForRemote(void)
{  CpuTimer0Regs.TCR.bit.TIF=1;
GpioDataRegs.GPATOGGLE.bit.GPIO16=1;
    if((RemoteRegulation==1))
      {
        if(remote_RegulationStep<=20)
          {
             if(SetSpeed > CurrentSpeed)
               {
                  PwmDutyCycle1 += StepSize_Duty1;
                }
             else
               {
                  PwmDutyCycle1 -= StepSize_Duty1;
                }
                remote_RegulationStep++;

              if(remote_RegulationStep>20)
                {
                  remote_RegulationStep=0;    // regulation steps are also done
                   RemoteRegulation=0;     // timer job is done
                   PwmDutyCycle1=SetPwmDutyCycle1;
                   CurrentSpeed=SetSpeed;
                            EALLOW;
                            CpuTimer0Regs.TCR.bit.TSS = 1; // Stop the timer
                            EDIS;
                 }
          }
      }
    else if(startSpeedRegulation==1)
    {
        startSpeedRegulation=0;
            EALLOW;
             CpuTimer0Regs.TCR.bit.TSS = 1; // Stop the timer
            EDIS;
    }
    else if(LockTimerON==1)
        {
            if(LockCount>5)
            {
                         EALLOW;
                         CpuTimer0Regs.TCR.bit.TSS = 1; // Stop the timer
                        EDIS;
                        stateMachine.isFiringON = 1;
                        LockTimerON=0;
                        LockCount=0;

            }
            else
            {
                LockCount++;
                EDIS;
                CpuTimer0Regs.PRD.all=120722892;    // period for 3 sec
                 CpuTimer0Regs.TCR.bit.TRB = 1;

                CpuTimer0Regs.TCR.bit.TSS = 0; // Start the timer
                EDIS;
            }
        }

  PieCtrlRegs.PIEACK.all=PIEACK_GROUP1;  // Acknowledge the interrupt
 }

__interrupt void Timer1ForRPM(void)
{
    CpuTimer1Regs.TCR.bit.TIF=1;
    RPM=0;
    isTimerInitialized = 0;
    CpuTimer0Regs.TCR.bit.TRB = 1;
    //  CpuTimer0Regs.TCR.bit.TSS=0;
}
__interrupt void Timer2ForVirtual(void)
{
    VitualTimerStarted=0;


    CpuTimer2Regs.TCR.bit.TIF=1; // clear flag
    CpuTimer2Regs.TCR.bit.TSS=1; //stop timer
    if(stateMachine.isFiringON)
    {
    stateMachine.currentState = &(stateMachine.states[currentBoundary]);
    stateMachine.currentState->action();
    }

}

/*
 * remote.c
 *
 *  Created on: 26-Mar-2024
 *      Author: AATPL00MK
 */
#include <srm/remote.h>
#include "f28x_project.h"
#include "srm/Globals.h"
#include "srm/AngleConversion.h"
#include "SwitchConfiguration.h"
#include <srm/Constants.h>
/////////////////variables//////////////////////

int RFsignal=0;
uint16_t rf_raw_valid_data_flag = 0;
int RisingEdge,FallingEdge;
uint32_t LowCount,HighCount;
uint32_t PastHighCount,PastLowCount;
uint32_t PreviousCount;
int timeReady;
int ms_eightLowHappened=0;
uint16_t RfCount[100];
int g=0;
int One_msTime=0;
int One_ms_Started=0;
int eightMS_FirstCount=0;
int bit=0;
int bitArray[33]={0};
uint16_t rf_bit_ptr = 0;
int DataStarted;
int Speed;
///////////getdatafromremote//////////
uint32_t rf_rx_data_raw = 0;
int button_Code=0;

int Add=1;
uint16_t DutyLimitPwm=(1/(PWM_Frequency*SystemBaseClk))*DutyLimit;   //17100 for 6k
//uint16_t OnePercentDuty=PwmPeriod/100;
uint16_t DutyChange = Duty_change*(1/(PWM_Frequency*SystemBaseClk*100));

//float Pwm1Per,Pwm2Per,Pwm3Per;

bool firstButtonPress = true;

extern double z;
extern double adv;
////////////////////////end/////////////////////////////////////
void RFsignalCalculate(void)
{
 //   z=DutyChange;
    if(BuzzerOn==0)
    {
    RFsignal=GpioDataRegs.GPADAT.bit.GPIO0;
if((rf_raw_valid_data_flag==0))
{
             if((RFsignal==1))
             {
                if(FallingEdge==1)
                {
                    PastLowCount=LowCount;
                    PastHighCount=HighCount;
                    PreviousCount=LowCount+HighCount;
                    FallingEdge=0;
                    LowCount=0;
                    HighCount=1;
                    timeReady=1;
                }
                else
                {
                    HighCount++;
                    timeReady=0;
                }
             }
             else
             {
                 LowCount++;
                 FallingEdge=1;
                 timeReady=0;
             }

             if((timeReady==1)&&(ms_eightLowHappened==0))
             {
//                 RfCount[g]=PreviousCount;
//                 g++;
//                                  if(g>100)
//                                  {
//                                      g=0;
//                                  }
                if(((PastLowCount>200)&&(PastLowCount<400)))//|((PastLowCount>400)&&(PastLowCount<850)))
                {
                  ms_eightLowHappened=1;
                }
                else
                {
                    ms_eightLowHappened=0;
                }
             }
             else if((timeReady==1)&&(ms_eightLowHappened==1))
             {

                 if(((PreviousCount>15)&&(PreviousCount<50)))
                       {
                          One_msTime++;
                             if(One_msTime>20)
                               {
                                  DataStarted=1;
                                  One_msTime=0;
                                  eightMS_FirstCount=2;
                                  // ms_eightLowHappened=2;
                                }
                       }
                 else if ((((PastLowCount>200)&&(PastLowCount<400))|((PastLowCount>400)&&(PastLowCount<800)))&&(eightMS_FirstCount==2))
                 {
                     ms_eightLowHappened=2;
                     One_msTime=0;
                     One_ms_Started=1;

                 }
                 else
                 {
                     ms_eightLowHappened=0;
                     One_msTime=0;
                 }

             }
             else if((timeReady==1)&&(ms_eightLowHappened==2)&&(rf_raw_valid_data_flag==0))
             {
                if(((PreviousCount>15)&&(PreviousCount<40)))
                {
                                          if((PastLowCount>12)&&(PastHighCount<12))
                                          {
                                              bit=0;
                                              bitArray[rf_bit_ptr]=bit;
                                            //  Raw_Data &= ~(1<<rf_bit_ptr);
                                              rf_bit_ptr++;
                                          //    rf_rx_data_raw &= ~(0x80000000 >> rf_bit_ptr++);
                                          }
                                          else if((PastLowCount<12)&&(PastHighCount>12))
                                          {
                                              bit=1;
                                              bitArray[rf_bit_ptr]=bit;
                                          //    Raw_Data |= (1<<rf_bit_ptr);
                                              rf_bit_ptr++;
                                            // rf_rx_data_raw &= (0x80000000 >> rf_bit_ptr++);
                                          }
                                          else
                                          {
                                            //  Raw_Data=0;
                                              rf_rx_data_raw=0;
                                              rf_bit_ptr=0;
                                          }
                              if(rf_bit_ptr==32)
                              {
                                //  GpioDataRegs.GPATOGGLE.bit.GPIO4=1;
                                  ms_eightLowHappened=0;
                                //  button_code = (rf_rx_data_raw >> 8) & 0xff;
                                  rf_raw_valid_data_flag=1;
                                  rf_bit_ptr=0;
                                  One_ms_Started=0;
                                  DataStarted=0;
                              }
                }
                else
                {
                    ms_eightLowHappened=0;
                }
           }
}
}
}
int RemoteControl(int code)
{
  if(code==5)
  {
      Speed=1;
  }
  else if(code==15)
  {
            Speed=2;
  }
  else if(code==4)
    {
              Speed=3;
    }
  else if(code==3)
    {
        Speed=4;
    }
  else if(code==2)
    {
        Speed=5;
    }
  else if(code==6)
    {
      Speed=10;
    }
  else if(code==14)
  {
      Speed=11;
  }
    return Speed;
}

void GetDataFromRemote(void)
{

if(rf_raw_valid_data_flag==1)
 {int i;
   for ( i = 0; i < 32; i++)
        {
         rf_rx_data_raw = (rf_rx_data_raw << 1) | bitArray[i];
         }
    int  button_code = (rf_rx_data_raw >> 8) & 0xff;
      SwitchPressed= RemoteControl(button_code);
        rf_raw_valid_data_flag=0;

                         BuzzerOn=1;
                         EPwm7Regs.CMPA.bit.CMPA = 35000;// pwm signal for buzzer
                      //Cmpss1Regs.DACLVALS.bit.DACVAL=SwitchPressed*500;
/////////////////////////////////////////////for first press///////////////////////////////////////////////////////////
                         if (firstButtonPress) {
                           if (SwitchPressed == 5)
                           {
                               isWithoutBlades = true;
                                SwitchPressed=0;
                            } else
                            {
                             isWithoutBlades = false;
                               }
                              firstButtonPress = false;
                             }



  if(SwitchPressed==10)
    {

      AllOff();
    setFiring(&stateMachine, 0);//to power on first time
    PwmDutyCycle1=0;
    retryCount=0;
   loopCounter = 0;
     Add=1;
   //  GpioDataRegs.GPADAT.bit.GPIO16=1;
  //   Cmpss1Regs.DACLVALS.bit.DACVAL=0;
       }
   else if(SwitchPressed==11)
    {
       AllOff();
      Add=0;
      PwmDutyCycle1=0;
      retryCount=0;
      loopCounter = 0;
    //  GpioDataRegs.GPADAT.bit.GPIO16=0;
      setFiring(&stateMachine, 0);//to power on first time
     }

     if(SwitchPressed==1)
     {
                  SetRPM=165;
                  SetSpeed=1;
                  SetPwmDutyCycle1 = (isWithoutBlades ? speed_1_Duty_WithoutBlades : speed_1_Duty_WithBlades) * OnePercentDuty;
                  setFiring(&stateMachine, 1);//to power on first time
     }
     else if (SwitchPressed==2)
     {
                  SetRPM=215;
                  SetSpeed=2;
                  SetPwmDutyCycle1 = (isWithoutBlades ? speed_2_Duty_WithoutBlades : speed_2_Duty_WithBlades) * OnePercentDuty;

                  setFiring(&stateMachine, 1);//to power on first time

     }
     else if(SwitchPressed==3)
     {
                  SetRPM=260;
                  SetSpeed=3;
                  SetPwmDutyCycle1 = (isWithoutBlades ? speed_3_Duty_WithoutBlades : speed_3_Duty_WithBlades) * OnePercentDuty;
                  setFiring(&stateMachine, 1);//to power on first time

     }
    else if(SwitchPressed==4)
    {
                 SetRPM=300;
                 SetSpeed=4;
                 SetPwmDutyCycle1 = (isWithoutBlades ? speed_4_Duty_WithoutBlades : speed_4_Duty_WithBlades) * OnePercentDuty;
                setFiring(&stateMachine, 1);//to power on first time

    }
   else if(SwitchPressed==5)
   {
                SetRPM=335;
                SetSpeed=5;
                SetPwmDutyCycle1 = (isWithoutBlades ? speed_5_Duty_WithoutBlades : speed_5_Duty_WithBlades) * OnePercentDuty;
                setFiring(&stateMachine, 1);//to power on first time

   }
   else
   {
       AdvanceAngle=AdvanceAngle; // @suppress("Assignment to itself")
   }
  }
}

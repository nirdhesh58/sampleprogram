/*
 * MKadc.c
 *
 *  Created on: 30-Sep-2023
 *      Author: Manoj kumar Parupalli
 */

#include "F28x_Project.h"
#include "f280013x_examples.h"
//#include "MKpwm.h"

void MKinitAdc(void)
{
    //ADC_setOffsetTrimAll(ADC_REFERENCE_INTERNAL,ADC_REFERENCE_3_3V);
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);
    EALLOW;
   // AnalogSubsysRegs.ANAREFCTL.bit.ANAREF2P5SEL=0;
 //   AnalogSubsysRegs.ANAREFCTL.bit.ANAREFSEL=0;
    AdcaRegs.ADCCTL2.bit.PRESCALE = 4; //set ADCCLK divider to /3
  //  AdcSetMode(ADC_ADCA, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);

    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1;      //power up the ADC
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1;
  //  AdcaRegs.ADCPPB1OFFCAL.bit.OFFCAL=1;
    AdccRegs.ADCCTL2.bit.PRESCALE = 4; //set ADCCLK divider to /4
  //  AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;      //power up the ADC
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1;


    ////////////////////////////////Sin Positive and cos Positive/////////////////////////////////////////////////////
    AdcaRegs.ADCSOC0CTL.bit.TRIGSEL= 0    ;   //trigger on software
    AdcaRegs.ADCSOC0CTL.bit.CHSEL = 1    ;       // A1 cospos
    AdcaRegs.ADCSOC0CTL.bit.ACQPS = 20   ;       //

    AdccRegs.ADCSOC0CTL.bit.TRIGSEL=0;    // trigger on software
    AdccRegs.ADCSOC0CTL.bit.CHSEL=1;  //cosneg
    AdccRegs.ADCSOC0CTL.bit.ACQPS=20;


    AdcaRegs.ADCINTSEL1N2.bit.INT1SEL=0; // End of Soc0 will set INT flag
    AdcaRegs.ADCINTSEL1N2.bit.INT1E=1;
    AdcaRegs.ADCINTFLGCLR.bit.ADCINT1=1;  // clear int
////////////////Sin Cos Negative////////////////////
        AdccRegs.ADCSOC1CTL.bit.TRIGSEL=0;    // trigger on  0 software, 11 H1 E4,5 H2 E1,
        AdccRegs.ADCSOC1CTL.bit.CHSEL=11;  //channel sellect sin positive
        AdccRegs.ADCSOC1CTL.bit.ACQPS=20;

        AdcaRegs.ADCSOC1CTL.bit.TRIGSEL= 0    ;   //trigger on software
        AdcaRegs.ADCSOC1CTL.bit.CHSEL = 7    ;       // A12 cos Neg
        AdcaRegs.ADCSOC1CTL.bit.ACQPS = 20   ;       //

        AdccRegs.ADCINTSEL1N2.bit.INT1SEL=1; // End of Soc1 will set INT flag
        AdccRegs.ADCINTSEL1N2.bit.INT1E=1;
        AdccRegs.ADCINTFLGCLR.bit.ADCINT1=1;  // clear int
 //////////////Voltage-Current Sensor///////////////////


//////////////////////////////////////////////////////////
  //  AdcaRegs.ADCSOC1CTL.bit.TRIGSEL= 0    ;   //trigger on software
  //  AdcaRegs.ADCSOC1CTL.bit.CHSEL = 16    ;       // A16
 //   AdcaRegs.ADCSOC1CTL.bit.ACQPS = 20   ;       //

        AdcaRegs.ADCSOC2CTL.bit.TRIGSEL= 0    ;   //trigger on software
        AdcaRegs.ADCSOC2CTL.bit.CHSEL = 20    ;       // A20  Advance
        AdcaRegs.ADCSOC2CTL.bit.ACQPS = 20   ;       //

        ////////////Agpio



        AdcaRegs.ADCSOC4CTL.bit.TRIGSEL= 0    ;   //trigger on software
        AdcaRegs.ADCSOC4CTL.bit.CHSEL = 5    ;       // A20
        AdcaRegs.ADCSOC4CTL.bit.ACQPS = 20   ;       //


        AdcaRegs.ADCSOC5CTL.bit.TRIGSEL= 0    ;   //trigger on software
        AdcaRegs.ADCSOC5CTL.bit.CHSEL = 0    ;       // A0
        AdcaRegs.ADCSOC5CTL.bit.ACQPS = 20   ;       //

       AdcaRegs.ADCSOC6CTL.bit.TRIGSEL= 0    ;   //trigger on software
       AdcaRegs.ADCSOC6CTL.bit.CHSEL = 12   ;       // A12
       AdcaRegs.ADCSOC6CTL.bit.ACQPS = 20   ;       //

       AdcaRegs.ADCSOC7CTL.bit.TRIGSEL= 0    ;   //trigger on software
       AdcaRegs.ADCSOC7CTL.bit.CHSEL = 12    ;       // A7
       AdcaRegs.ADCSOC7CTL.bit.ACQPS = 20   ;       //

       AdcaRegs.ADCSOC8CTL.bit.TRIGSEL= 0    ;   //trigger on software
       AdcaRegs.ADCSOC8CTL.bit.CHSEL = 4    ;       // A4
       AdcaRegs.ADCSOC8CTL.bit.ACQPS = 20   ;       //

       AdccRegs.ADCSOC3CTL.bit.TRIGSEL= 0    ;   //trigger on software
       AdccRegs.ADCSOC3CTL.bit.CHSEL = 0    ;       // A16 throtle
       AdccRegs.ADCSOC3CTL.bit.ACQPS = 20   ;       //

 /*   GpioCtrlRegs.GPHAMSEL.bit.GPIO242=1;
    AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO242 = 1;*/

/*
    AdcaRegs.ADCSOC2CTL.bit.TRIGSEL= 0x0B    ;   //trigger on EPWM4A
    AdcaRegs.ADCSOC2CTL.bit.CHSEL = 4    ;       // A4
    AdcaRegs.ADCSOC2CTL.bit.ACQPS = 20   ;       //

    AdcaRegs.ADCSOC3CTL.bit.TRIGSEL= 0x0B    ;   //trigger on EPWM4A
    AdcaRegs.ADCSOC3CTL.bit.CHSEL = 14    ;       // A14
    AdcaRegs.ADCSOC3CTL.bit.ACQPS = 20   ;       //
////////////////////////////////////////////////////////////////////////////////////////

    AdccRegs.ADCSOC0CTL.bit.TRIGSEL=0x0B ;       //trigger on EPWM4A
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 2    ;       // C2
    AdccRegs.ADCSOC0CTL.bit.ACQPS = 20   ;       //

    AdccRegs.ADCSOC1CTL.bit.TRIGSEL=0x0B ;       //trigger on EPWM4A
    AdccRegs.ADCSOC1CTL.bit.CHSEL = 3    ;       // C3
    AdccRegs.ADCSOC1CTL.bit.ACQPS = 20   ;       //

    AdccRegs.ADCSOC2CTL.bit.TRIGSEL=0x0B ;       //trigger on EPWM4A
    AdccRegs.ADCSOC2CTL.bit.CHSEL = 4    ;       // C4
    AdccRegs.ADCSOC2CTL.bit.ACQPS = 20   ;       //trigger on EPWM4A*/
///////////////////////////////////////////////////////////////////////////////////////
    AdcaRegs.ADCINTFLGCLR.all = 0xf ;
    AdccRegs.ADCINTFLGCLR.all = 0xf ;

//    AdcaRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0  ;   //No priority all the channels are put in round robin mode.
//   AdccRegs.ADCSOCPRICTL.bit.SOCPRIORITY = 0  ;   //No priority all the channels are put in round robin mode.

    EDIS;
  //  DELAY_US(1000);     // delay to powerup ADCs
}





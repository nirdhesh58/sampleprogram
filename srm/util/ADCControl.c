#include "F28x_Project.h"
#include "ADCControl.h" // Assume this is the renamed header file for ADC configuration

void InitializeADC(void)
{
    ConfigureADCReferences();
    EnableADCs();
    ConfigureADCSOCs();
    ConfigureGPIOForADC();
    ClearADCInterruptFlags();
}

void ConfigureADCReferences(void)
{
    EALLOW;
    // Set reference voltages for ADC A and C to 3.3V
    SetVREF(ADC_ADCA, ADC_INTERNAL, ADC_VREF3P3);
    SetVREF(ADC_ADCC, ADC_INTERNAL, ADC_VREF3P3);
    EDIS;
}

void EnableADCs(void)
{
    EALLOW;
    // Enable and configure ADC A
    AdcaRegs.ADCCTL2.bit.PRESCALE = 4; // Set ADCCLK divider to /4 for ADC A
    AdcaRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADC A
    AdcaRegs.ADCCTL1.bit.INTPULSEPOS = 1; // Set interrupt pulse position to late
    
    // Enable and configure ADC C
    AdccRegs.ADCCTL2.bit.PRESCALE = 6; // Set ADCCLK divider to /6 for ADC C
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1; // Power up ADC C
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 1; // Set interrupt pulse position to late
    EDIS;
}

void ConfigureADCSOCs(void)
{
    EALLOW;
    // Configure SOC for ADC A and ADC C
    ConfigureSOC(&AdcaRegs, 0, 1, 20); // ADC A, SOC0, channel 1, acquisition period 20
    ConfigureSOC(&AdccRegs, 0, 1, 20); // ADC C, SOC0, channel 1, acquisition period 20

    // Additional SOC configurations as needed
    ConfigureSOC(&AdcaRegs, 1, 7, 20); // ADC A, SOC1, channel 7, acquisition period 20
    // Add more SOC configurations here

    EDIS;
}

void ConfigureSOC(volatile struct ADC_REGS* adcRegs, uint16_t socNumber, uint16_t channel, uint16_t acqPeriod)
{
    adcRegs->ADCSOC[socNumber].CTL.bit.TRIGSEL = 0; // Trigger on software
    adcRegs->ADCSOC[socNumber].CTL.bit.CHSEL = channel; // Set channel
    adcRegs->ADCSOC[socNumber].CTL.bit.ACQPS = acqPeriod; // Set acquisition period
}

void ConfigureGPIOForADC(void)
{
    EALLOW;
    // Example GPIO configuration for ADC
    GpioCtrlRegs.GPAAMSEL.bit.GPIO28 = 1; // Enable analog input on GPIO28
    AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO28 = 1; // Set GPIO28 as analog input
    EDIS;
}

void ClearADCInterruptFlags(void)
{
    EALLOW;
    AdcaRegs.ADCINTFLGCLR.all = 0xF; // Clear ADC A interrupt flags
    AdccRegs.ADCINTFLGCLR.all = 0xF; // Clear ADC C interrupt flags
    EDIS;
}

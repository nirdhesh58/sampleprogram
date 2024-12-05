
#include "PWMControl.h" // Assuming renamed header file for clarity
#include "F28x_Project.h"

#include <srm/Constants.h>
#include <srm/Globals.h>

// Initializes EPWM1 with default settings
void InitializeEPWM1(void) {
    ConfigureEPWMModule(&EPwm1Regs, PwmPeriod, 0);
}

// Initializes EPWM4 with default settings
void InitializeEPWM4(void) {
    ConfigureEPWMModule(&EPwm4Regs, PwmPeriod, 0);
}

// Initializes EPWM6 with custom settings
void InitializeEPWM6(void) {
    ConfigureEPWMModule(&EPwm6Regs, PwmPeriod, 1000);
    // Custom configurations for EPWM6 can be added here if needed
}

// Initializes EPWM2 with specific period and compare value
void InitializeEPWM2(void) {
    ConfigureEPWMModule(&EPwm2Regs, 7500, 1000);
}

// Initializes EPWM3 with specific period and compare value
void InitializeEPWM3(void) {
    ConfigureEPWMModule(&EPwm3Regs, 30000, 6000);
}

// General function to configure EPWM modules
void ConfigureEPWMModule(volatile struct EPWM_REGS *epwmReg, uint16_t period, uint16_t compareValue) {
    EALLOW;
    epwmReg->TBPRD = period; // Set timer period
    epwmReg->TBPHS.bit.TBPHS = 0; // Phase is 0
    epwmReg->TBCTR = 0; // Clear counter

    // Time base clock setup
    epwmReg->TBCTL.bit.FREE_SOFT = 3;
    epwmReg->TBCTL.bit.CTRMODE = TB_COUNT_UP;
    epwmReg->TBCTL.bit.PHSEN = TB_DISABLE;
    epwmReg->TBCTL.bit.PRDLD = TB_SHADOW;
    epwmReg->TBCTL.bit.HSPCLKDIV = TB_DIV1; // Clock ratio to SYSCLKOUT
    epwmReg->TBCTL.bit.CLKDIV = TB_DIV1;

    // Comparator setup
    epwmReg->CMPCTL.bit.SHDWAMODE = CC_SHADOW; // Load registers every ZERO
    epwmReg->CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    epwmReg->CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
    epwmReg->CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    epwmReg->CMPA.bit.CMPA = compareValue;

    // Action qualifier setup
    epwmReg->AQCTLA.bit.CAU = AQ_CLEAR; // Clear PWMxA on CAU
    epwmReg->AQCTLA.bit.ZRO = AQ_SET; // Set PWMxA on Zero
    epwmReg->AQCTLB.bit.CAU = AQ_SET; // Set PWMxB on CAU
    epwmReg->AQCTLB.bit.ZRO = AQ_CLEAR; // Clear PWMxB on Zero

    // Dead-Band Generator setup
    epwmReg->DBCTL.bit.OUT_MODE = DB_FULL_ENABLE; // DBM mode
    epwmReg->DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active High Complementary
    epwmReg->DBFED.bit.DBFED = 400; // Falling edge delay
    epwmReg->DBRED.bit.DBRED = 400; // Rising edge delay

    EDIS;
}

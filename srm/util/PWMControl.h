#ifndef PWM_CONTROL_H_
#define PWM_CONTROL_H_

#include "F28x_Project.h"

#define H1L1 (&EPwm4Regs)
#define H3L3 (&EPwm1Regs)
#define H2L2 (&EPwm6Regs)
#define H4L4 (&EPwm2Regs)

static inline void DisablePwm(volatile struct EPWM_REGS *epwmReg) {
    EALLOW;
    epwmReg->TZFRC.bit.OST = 1;  // One Shot Trip (OFF)
    EDIS;
}

static inline void SetPwmCmpA(volatile struct EPWM_REGS *epwmReg, uint16_t cmpValue) {
    epwmReg->CMPA.bit.CMPA = cmpValue;
}
static inline void SetPwmCmpB(volatile struct EPWM_REGS *epwmReg, uint16_t cmpValue) {
    epwmReg->CMPB.bit.CMPB = cmpValue;
}

static inline void ClearOneShot(volatile struct EPWM_REGS *epwmReg) {
    EALLOW;
    epwmReg->TZOSTCLR.bit.OST1 = 1;  // Clear One Shot for specific PWM
    epwmReg->TZCLR.bit.OST = 1;      // Clear One Shot Trip
    EDIS;
}

// Function declarations for initializing EPWM modules
void InitializeEPWM1(void);
void InitializeEPWM2(void);
void InitializeEPWM3(void);
void InitializeEPWM4(void);
void InitializeEPWM6(void);

// General function to configure any EPWM module
void ConfigureEPWMModule(volatile struct EPWM_REGS *epwmReg, uint16_t period, uint16_t compareValue);

#endif // PWM_CONTROL_H_

#ifndef SWITCH_CONFIGURATION_H
#define SWITCH_CONFIGURATION_H

#include "F28x_Project.h"// Include the necessary device headersS
#include "util/PWMControl.h"
#include "Globals.h"



// Define the specific type for the parameters
static inline void ControlHardwareLL(volatile struct EPWM_REGS *LPwm1, volatile struct EPWM_REGS *LPwm2,volatile struct EPWM_REGS *OffPwm1, volatile struct EPWM_REGS *OffPwm2) {
    DisablePwm(OffPwm1);
    DisablePwm(OffPwm2);
        SetPwmCmpA(LPwm1, 0);
        SetPwmCmpA(LPwm2, 0);
    SetPwmCmpB(LPwm1, PwmPeriod+1);
    SetPwmCmpB(LPwm2, PwmPeriod+1);
    
    ClearOneShot(LPwm1);
    ClearOneShot(LPwm2);
}

// Define the specific type for the parameters
static inline void ControlHardwareHLL(volatile struct EPWM_REGS *HPwm, volatile struct EPWM_REGS *LPwm1, volatile struct EPWM_REGS *LPwm2, volatile struct EPWM_REGS *OffPwm, uint16_t pwmDuty) {
    DisablePwm(OffPwm);
    
    SetPwmCmpA(LPwm1, 0);
    SetPwmCmpA(LPwm2, 0);
    SetPwmCmpA(HPwm, pwmDuty);
    SetPwmCmpB(HPwm, 0);
    SetPwmCmpB(LPwm1, PwmPeriod+1);
    SetPwmCmpB(LPwm2, PwmPeriod+1);




    ClearOneShot(LPwm1);
    ClearOneShot(LPwm2);
    ClearOneShot(HPwm);
}

// Define the specific type for the parameters
static inline void ControlHardwareHL(volatile struct EPWM_REGS *HPwm, volatile struct EPWM_REGS *LPwm1, volatile struct EPWM_REGS *OffPwm1, volatile struct EPWM_REGS *OffPwm2, uint16_t pwmDuty) {
    DisablePwm(OffPwm1);
    DisablePwm(OffPwm2);

    SetPwmCmpB(HPwm, 0);
    SetPwmCmpB(LPwm1, PwmPeriod+1);
    SetPwmCmpA(LPwm1,0);
    SetPwmCmpA(HPwm, pwmDuty);
    

    ClearOneShot(LPwm1);
    ClearOneShot(HPwm);
}




// State 0
static inline void H1L1_L2_L3_pwm1(void) {
   // ControlHardwareHLL(H1L1, H2L2, H3L3, H4L4, PwmDutyCycle1);
    ControlHardwareHL(H1L1, H2L2, H3L3, H4L4, PwmDutyCycle1);
}

// State 1
static inline void H1L1_L2_L3_pwm2(void) {
    ControlHardwareHLL(H1L1, H2L2, H3L3, H4L4, PwmDutyCycle2*0.9);
}

// State 2
static inline void H1L1_L2_L3_pwm3(void) {
    ControlHardwareHLL(H1L1, H2L2, H3L3, H4L4, PwmDutyCycle3);
}

// State 3
static inline void L1_L3(void) {
    ControlHardwareLL(H1L1, H3L3, H2L2, H4L4);
}

// State 4
static inline void H2L2_L3_pwm1(void) {
    ControlHardwareHL(H2L2, H3L3, H1L1, H4L4, PwmDutyCycle1);
}


// State 5
static inline void H2L2_L3_pwm2(void) {
    ControlHardwareHL(H2L2, H3L3, H1L1, H4L4, PwmDutyCycle2);
}

// State 6
static inline void H2L2_L3_pwm3(void) {
    ControlHardwareHL(H2L2, H3L3, H1L1, H4L4, PwmDutyCycle3);
}

// State 7
static inline void L2_L4(void) {
    ControlHardwareLL(H2L2, H4L4, H1L1, H3L3);
}

// State 8
static inline void H3L3_L4_pwm1(void) {
    ControlHardwareHL(H3L3, H4L4, H1L1, H2L2, PwmDutyCycle1);
}

// State 9
static inline void H3L3_L4_pwm2(void) {
    ControlHardwareHL(H3L3, H4L4, H1L1, H2L2, PwmDutyCycle2);
}

// State 10
static inline void H3L3_L4_pwm3(void) {
    ControlHardwareHL(H3L3, H4L4, H1L1, H2L2, PwmDutyCycle3);
}

// State 11
static inline void L3_L4(void) {
    ControlHardwareLL(H3L3, H4L4, H1L1, H2L2);
}
static inline void L1_L2(void) {
    ControlHardwareLL(H1L1, H2L2, H3L3, H4L4);
}

static inline void L2_L3(void) {
    ControlHardwareLL(H3L3, H2L2, H1L1, H4L4);
}

static inline void H1_L2_pwm2(void)
{
	 ControlHardwareHL(H1L1, H2L2, H3L3, H4L4, PwmDutyCycle2);
}
static inline void H1L1_L3_pwm1(void)
{
     ControlHardwareHL(H1L1, H3L3, H2L2, H4L4, PwmDutyCycle1);
}

static inline void H2L2_L4_pwm1(void)
{
     ControlHardwareHL(H2L2, H4L4, H1L1, H3L3, PwmDutyCycle1);
}

// All Turned off state
static void AllOff(void){
    DisablePwm(H1L1);
    DisablePwm(H2L2);
    DisablePwm(H3L3);
    DisablePwm(H4L4);
    DELAY_US(1);        // 2 microSeconds delay
}

#endif // SWITCH_CONFIGURATION_H

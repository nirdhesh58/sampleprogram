/*
 * SpeedRegulation.c
 *
 *  Created on: 25-May-2024
 *      Author: AATPL0003
 */
#include "SpeedRegulation.h"

void control_rpm(float SetRPM, float RPM) {
    float rpm_difference = SetRPM - RPM;
    float adjustment = OnePercentDuty * 0.1; // 0.1% of the duty cycle

    if (rpm_difference > DEADBAND) {
        // If actual RPM is less than SetRPM by more than the deadband
        PwmDutyCycle1 += adjustment;
    } else if (rpm_difference < -DEADBAND) {
        // If actual RPM is more than SetRPM by more than the deadband
        PwmDutyCycle1 -= adjustment;
    }

    // Ensure the duty cycle stays within valid bounds
    if (PwmDutyCycle1 > DutyLimit * PwmPeriod) PwmDutyCycle1 = DutyLimit * PwmPeriod;
    if (PwmDutyCycle1 < OnePercentDuty * 2) PwmDutyCycle1 = 0.0;

    // Start the timer for speed regulation
    startSpeedRegulation = 1;
    EALLOW;
    CpuTimer0Regs.TCR.bit.TSS = 1;    // stop timer
    CpuTimer0Regs.PRD.all = 180722892; // 0.5 sec period (modify value as needed)
    CpuTimer0Regs.TCR.bit.TRB = 1;    // reload with period
    CpuTimer0Regs.TCR.bit.TSS = 0;    // start timer
    EDIS;
}


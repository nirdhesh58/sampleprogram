/*
 * LockTest.h
 *
 *  Created on: 15-Jul-2024
 *      Author: AATPL0003
 */

#ifndef SRM_LOCKTEST_H_
#define SRM_LOCKTEST_H_

#include <srm/Constants.h>
#include <srm/SwitchStateMachine.h>
#include <srm/Globals.h>
#include "f28x_project.h"
#include <srm/AngleConversion.h>

void monitorAndRetryAngleMovement(double theta) {
    if (retryCount < 3) {
        if (loopCounter == 0) {
            initialAngle = theta;
        }
        loopCounter++;
        if (loopCounter >= LOOPS_PER_3_SEC)
        {
            angleMoved = theta - initialAngle;
            if (angleMoved >= degreesToRadians(40)) {
                // Angle moved sufficiently
                retryCount = 0;
                loopCounter = 0;
            } else {
                // Stop firing and retry after 3 second
                AllOff();
                       stateMachine.isFiringON = 0;
                       EALLOW;
                       CpuTimer0Regs.PRD.all=120722892;//360722892;    // period for 1 sec
                       CpuTimer0Regs.TCR.bit.TRB = 1;
                       CpuTimer0Regs.TCR.bit.TSS=0;
                       EDIS;
                retryCount++;
                loopCounter = 0;
              LockTimerON=1;
            }
        }
    } else {
        // Reset firingON after 5 unsuccessful attempts
        stateMachine.isFiringON = 0;
        AllOff();
        retryCount = 0;
        loopCounter = 0;
        ReadRemote=0;
    }
}

#endif /* SRM_LOCKTEST_H_ */

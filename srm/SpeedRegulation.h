/*
 * SpeedRegulation.h
 *
 *  Created on: 25-May-2024
 *      Author: AATPL0003
 */

#ifndef SRM_SPEEDREGULATION_H_
#define SRM_SPEEDREGULATION_H_

#include <srm/Constants.h>
#include <srm/Globals.h>
#include <srm/remote.h>


#define DEADBAND 3
#define SMALL_DIFF 4
#define SMALL_ADJUSTMENT 50.0
#define LARGE_ADJUSTMENT 100.0

void control_rpm(float SetRPM, float RPM);

#endif /* SRM_SPEEDREGULATION_H_ */

/*
 * remote.h
 *
 *  Created on: 26-Mar-2024
 *      Author: AATPL00MK
 */

#ifndef SRM_REMOTE_H_
#define SRM_REMOTE_H_
#include "f28x_project.h"

void RFsignalCalculate(void);
int RemoteControl(int code);
void GetDataFromRemote(void);


#endif /* SRM_REMOTE_H_ */

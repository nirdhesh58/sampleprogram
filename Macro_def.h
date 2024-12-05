/*
 * Macro_def.h
 *
 *  Created on: 04-Oct-2023
 *      Author: AATPL00MK
 */

#ifndef MACRO_DEF_H_
#define MACRO_DEF_H_

#define FW_VERSION                  0x0002

#define LOW                         0
#define HIGH                        1

#define EXTERNAL_DAC_ENABLE

#ifdef EXTERNAL_DAC_ENABLE
#define DISABLE_EPWM
#endif
//#define DEADBAND_SW_EMULATION

#ifdef DEADBAND_SW_EMULATION
#define DEAD_BAND               600       //3*8.33ns = 24ns
#endif

//sin and cos maximum analog swing; updated after offset calibration
#define COS_MAX_ANALOG_VOL         1.84f
#define COS_MIN_ANALOG_VOL         0.8f
#define SIN_MAX_ANALOG_VOL         1.8f
#define SIN_MIN_ANALOG_VOL          0.8f

#define ADC_AVG_COUNT               64

#define SENSOR_REF_VOL              3.3f
#define ADC_FULL_SCALE              4096

#define COS_MAX_DIGITAL_VAL         COS_MAX_ANALOG_VOL*ADC_FULL_SCALE/SENSOR_REF_VOL
#define COS_MIN_DIGITAL_VAL         COS_MIN_ANALOG_VOL*ADC_FULL_SCALE/SENSOR_REF_VOL
#define SIN_MAX_DIGITAL_VAL         SIN_MAX_ANALOG_VOL*ADC_FULL_SCALE/SENSOR_REF_VOL
#define SIN_MIN_DIGITAL_VAL         SIN_MIN_ANALOG_VOL*ADC_FULL_SCALE/SENSOR_REF_VOL

#define SINUSOID_MIN_VAL            -1
#define SINUSOID_MAX_VAL            1

#define COS_LIN_SLOPE               (SINUSOID_MAX_VAL-SINUSOID_MIN_VAL)/(COS_MAX_DIGITAL_VAL-COS_MIN_DIGITAL_VAL)
#define COS_LIN_INTERCEPT           COS_LIN_SLOPE*(-COS_MIN_DIGITAL_VAL) + SINUSOID_MIN_VAL
#define SIN_LIN_SLOPE               (SINUSOID_MAX_VAL-SINUSOID_MIN_VAL)/(SIN_MAX_DIGITAL_VAL-SIN_MIN_DIGITAL_VAL)
#define SIN_LIN_INTERCEPT           SIN_LIN_SLOPE*(-SIN_MIN_DIGITAL_VAL) + SINUSOID_MIN_VAL


#define MAX_TIMER_TASK_L1_COUNT             59          //60*5 = 300us
#define MAX_TIMER_TASK_L2_COUNT             3333        //3333*300 = 1000000us = 1 sec





#endif /* MACRO_DEF_H_ */

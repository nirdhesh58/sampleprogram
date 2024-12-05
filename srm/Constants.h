#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PI 3.14159//265358979323846

//////////for pwm///////////////////////////////////////////




//#define PWM_TimePeriod 1/PWM_Frequency
//#define PwmPeriod PWM_TimePeriod/0.0000000083  //6Khz=18000 20khz=6000    //period controls frequency
#define mechanicalOffset -2.79445//chromton-3.003439//2.90973 //-2.7048//m37/3=-2.90770//-2.761807 //M37.2/2,1000T -2.761807 //M37.2,1000T-2.9452  //1200T=-2.983499// -2.84145 // -2.80348//-2.89454
#define PWM_Frequency 20000    //in Hz update frequency for pwm signals here
#define SamplingTime 0.00004   //40us
//#define Pwm_period_Time 0.0001666667
#define SystemBaseClk 0.0000000083
#define DutyLimit  0.95   // 0 to 0.99----> 0% to 99%
//#define  OnePercentDuty PwmPeriod/100
#define DefaultDuty_percent 1 //1%
////////////for main/////////////////////////////
#define RotorPoles 28
#define RPM_THRESHOLD_Tracking_Off 1000
#define RPM_THRESHOLD_LOW_VIRTUAL 120
#define RPM_THRESHOLD_High 1000

//////////for Remote////////////////////
#define Duty_change  0.5 // 0.3 times 1% for remote each press

#define ConductionAngle1_Max_Limit 80  // degrees
#define ConductionAngle2_Max_Limit 80  // degrees
#define ConductionAngle1_Min_Limit 5  // degrees
#define ConductionAngle2_Min_Limit 5  // degrees
#define AdvanceAngle_Max_Limit 80 //degrees
#define AdvanceAngle_Min_Limit 80 //degrees
#define DegreeChange 0.5    //degrees
///////for 5 speed duty percentage/////////

#define speed_1_Duty_WithoutBlades 4.5
#define speed_2_Duty_WithoutBlades 6
#define speed_3_Duty_WithoutBlades 8.5
#define speed_4_Duty_WithoutBlades 10.5
#define speed_5_Duty_WithoutBlades 12.5


#define speed_1_Duty_WithBlades 22
#define speed_2_Duty_WithBlades 33.5
#define speed_3_Duty_WithBlades 49
#define speed_4_Duty_WithBlades 63.5
#define speed_5_Duty_WithBlades 81

///////////////states/////////////////
#define NUM_STATES 6
///for lock test
#define LOOPS_PER_3_SEC  75000 // 3 seconds / 40 microseconds per loop

// Co efficients for second order butterworth Filter
// Low Pass Cutoff Frequency: 800Hz
// Sampling Frequency: 40kHz
#define B0  0.008826  // 0.005129//0.003621679  //0.707 //0.0201    //0.8006  //0.003621679   // 0.863                   // for 10 poles 0.003621679  //3db 800Hz   sampling 40kHz
#define B1  0.017652 // 0.010258//0.007243359// 0.707 // // 1.6013   //0.007243359 //0.863                   // for 10 poles 0.007243359
#define B2  0.008826 //0.005129//0.003621679   // 0.8006   //0.003621679  //0.1311                    // for 10 poles 0.003621679  // uncomment for 2nd order
#define A1  -1.717 //-1.822693443//0.414// //1.5612   //-1.822693443  //0.727                   // for 10 poles -1.822693443
#define A2  0.752 //0.83718016    //0.6413   //0.83718016//0.2722                   // for 10 poles 0.83718016    // uncomment for second order


#define INITIAL_CROSSOVER 0.0  // Assuming an initial crossover target
#define N 1000.0  // Normalization constant


#define SAMPLING_INTERVAL 25
#define SAMPLING_INTERVAL_RECIPROCAL (1.0 / SAMPLING_INTERVAL)
#define VELOCITY_THRESHOLD 1.57e-07 // Radians per sample for 60 rpm 40 Khz sampling frequency


#endif // CONSTANTS_H

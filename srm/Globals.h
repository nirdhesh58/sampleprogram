#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include <stdbool.h>
#include <srm/SwitchStateMachine.h>

extern volatile uint16_t CosNegative, CosPositive, SinPositive, SinNegative;
extern volatile bool isSineSampleComplete, isCosineSampleComplete;

extern volatile double targetAngle;
extern volatile bool targetAngleSet;

// Manually Tuneable Params
extern volatile uint16_t PwmDutyCycle1, PwmDutyCycle2, PwmDutyCycle3;
extern volatile double Pwm1DutyPercent, Pwm2DutyPercent, Pwm3DutyPercent;
extern volatile double ConductionAngle, OverlapAngle, AdvanceAngle,ConductionAngle2;
extern volatile int PowerOn;
extern volatile int SwitchPressed;

extern volatile double stateBoudnaries[12];
extern StateMachine stateMachine;
//extern volatile double mechanicalOffset;
extern double RPM;
extern int isTimerInitialized;

extern volatile bool triggerAllowed;  // Flag to allow triggering when theta crosses zero
extern volatile bool wasNegative;     // Flag to track if the last angle was negative
extern int BuzzerOn;

extern volatile double angleOfInterest ;
extern volatile int currentBoundary;
extern volatile int VitualTimerStarted;
extern uint32_t count,count1;
extern double TestAngle,A,B,C,D,E,F;
extern volatile int StartVirtual;
extern volatile int sampleCounter ;
extern volatile int VirtualencoderStarted;
extern volatile double OnePercentDuty;
extern double PwmPeriod;
extern volatile int numSamplesToconsider;
///////////////////////////////////5speed//////////////////////////////////////
extern uint16_t SetSpeed,CurrentSpeed,SetRPM,CurrentRpm;
extern uint16_t SetPwmDuty1;
extern uint16_t StepSize_Duty1;
extern volatile int RemoteRegulation;
extern volatile int remote_RegulationStep;
extern volatile int startSpeedRegulation;
extern uint16_t SetPwmDutyCycle1;
extern volatile bool isWithoutBlades;
extern int retryCount ;
extern double initialAngle ;
extern double angleMoved ;
extern uint32_t loopCounter ;
extern int LockTimerON;
extern volatile int LockCount;
extern int ReadRemote;
#endif // GLOBALS_H

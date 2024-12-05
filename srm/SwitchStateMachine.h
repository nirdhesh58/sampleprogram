#ifndef SWITCH_CONTROL_STATE_MACHINE_H
#define SWITCH_CONTROL_STATE_MACHINE_H


#include "srm/Constants.h"

//#define NUM_STATES 6


/**
 * @tableofstates
 * | Start Angle        | Stop Angle         | Function Name        |
 * |--------------------|--------------------|----------------------|
 * | `ANGLE_0`          | `ANGLE_OA`         | `H1L1_L2_L3_pwm1`    |
 * | `ANGLE_OA`         | `ANGLE_OA_PLUS_CA` | `H1L1_L2_L3_pwm2`    |
 * | `ANGLE_OA_PLUS_CA` | `ANGLE_120_MINUS_OA`| `H1L1_L2_L3_pwm3`   |
 * | `ANGLE_120_MINUS_OA`| `ANGLE_120`        | `L1_L3`              |
 * | `ANGLE_120`        | `ANGLE_120_PLUS_OA`| `H2L2_L3_pwm1`       |
 * | `ANGLE_120_PLUS_OA`| `ANGLE_120_PLUS_OA_PLUS_CA`| `H2L2_L3_pwm2`|
 * | `ANGLE_120_PLUS_OA_PLUS_CA`| `ANGLE_240_MINUS_OA`| `H2L2_L3_pwm3`|
 * | `ANGLE_240_MINUS_OA`| `ANGLE_240`        | `L2_L4`              |
 * | `ANGLE_240`        | `ANGLE_240_PLUS_OA`| `H3L3_L4_pwm1`       |
 * | `ANGLE_240_PLUS_OA`| `ANGLE_240_PLUS_OA_PLUS_CA`| `H3L3_L4_pwm2`|
 * | `ANGLE_240_PLUS_OA_PLUS_CA`| `ANGLE_360_MINUS_OA`| `H3L3_L4_pwm3`|
 * | `ANGLE_360_MINUS_OA`| `ANGLE_360`          | `L3_L4`              |
 */


// State action function prototype
typedef void (*StateActionFunction)(void);

// State struct
typedef struct {
    double startAngle;
    double endAngle;
    StateActionFunction action;
} State;

// StateMachine struct
typedef struct {
    State states[NUM_STATES];
  State* currentState;
    int isFirstTargetSet;
    int isFiringON;
    int StartTimer;  // Variable to control the timer
} StateMachine;

// Public function declarations
void initStateFunctions( StateMachine* sm);
void updateStateBoundaries( StateMachine* sm, volatile double boundaries[NUM_STATES + 1]);
void transitionState(  StateMachine* sm, double angle);
void setCurrentStateByAngle( StateMachine* sm, double angle);
void executeCurrentStateAction( StateMachine* sm);
void computeBoundaries(double OA, double CA,double CA2,volatile double boundaries[NUM_STATES + 1]);
void setFiring(StateMachine* sm,int fire);
void simplifiedTransitionState(StateMachine* sm, double angle);
void checkRpmTriggerAtBoundary(double theta);
void findBoundary(double elecAngle, volatile double boundaries[]);
void updateAngleOfInterest(volatile double boundaries[]);
void simplifiedTransitionStateForStart(StateMachine* sm, float theta);
#endif // SWITCH_CONTROL_STATE_MACHINE_H

// SwitchControlStateMachine.c
#include "SwitchStateMachine.h"
#include <srm/Constants.h>
#include <stdio.h>
#include "SwitchConfiguration.h"
#include <srm/AngleConversion.h>
#include <srm/Globals.h>
// Define the number of states


/**
 * @tableofstates
 * | Start Angle        | Stop Angle         | Function Name        |
 * |--------------------|--------------------|----------------------|
 * | `ANGLE_0`          | `ANGLE_CA`         | `H1L1_L2_L3_pwm1`    |
 * | `ANGLE_CA`         | `ANGLE_120_MINUS_CA2` | `H1L1_L2_L3_pwm2`    |
 * | `ANGLE_120_MINUS_CA2` | `ANGLE_120`     | `L1_L2`   |
 * | `ANGLE_120`        | `ANGLE_120_PLUS_CA`| `H2L2_L3_pwm1`       |
 * | `ANGLE_120_PLUS_CA`| `ANGLE_240_MINUS_CA2`| `H2L2_L3_pwm2`|
 * | `ANGLE_240_MINUS_CA2`| `ANGLE_240`| `L2_L3`|
 * | `ANGLE_240`        | `ANGLE_240_PLUS_CA`| `H3L3_L4_pwm1`       |
 * | `ANGLE_240_PLUS_CA`| `ANGLE_360_MINUS_CA2`| `H3L3_L4_pwm2`|
 * | `ANGLE_360_MINUS_CA2`| `ANGLE_0`          | `L3_L4`              |
 */


// Initialize the function pointers for each state
void initStateFunctions( StateMachine* sm) {
    StateActionFunction actions[NUM_STATES] = {
        H1L1_L2_L3_pwm1, 
		//H1_L2_pwm2,
       // H1L1_L2_L3_pwm2,
        L1_L2,
    //    AllOff,
        H2L2_L3_pwm1,
       //H2L2_L3_pwm2,
        L2_L3,
     //   AllOff,
        H3L3_L4_pwm1,
      //  H3L3_L4_pwm2,
        L3_L4,
     //   AllOff
    };
      int i;
    for ( i = 0; i < NUM_STATES; i++) {
        sm->states[i].action = actions[i];
    }

    sm->isFirstTargetSet = 0;
    sm->isFiringON=0;
    sm->StartTimer = 0;  // Initialize StartTimer
}


// Update the state boundaries for each state
void updateStateBoundaries( StateMachine* sm, volatile double boundaries[NUM_STATES + 1]) {
    int i;
    for ( i = 0; i < NUM_STATES; i++) {
        sm->states[i].startAngle = boundaries[i];
        sm->states[i].endAngle = boundaries[i + 1];
    }
}


// Transitions to the next state based on the given angle
void transitionState( StateMachine* sm, double angle) {
  State* currentState = sm->currentState;
  State* nextState = currentState == &sm->states[NUM_STATES - 1] ? &sm->states[0] : currentState + 1;

  //  if ((currentState != &sm->states[NUM_STATES - 1] ? (angle >= nextState->startAngle): angle>=0 )&) {
        if ( (angle >= nextState->startAngle)&&(angle <= nextState->endAngle) ) {
        sm->currentState = nextState;
   //     sm->StartTimer = (nextState == &sm->states[0]) ? 1 : 0;  // Set StartTimer based on state transition
        if (nextState->action && sm->isFiringON==1) {
            //AllOff();
            nextState->action();
        }
    }
}

/**
 * Compute the boundary points based on OA and CA values.
 * 
 * @param OA Offset Angle in radians.
 * @param CA Central Angle in radians.
 * @param boundaries Array to store the computed boundary points.
 */
void computeBoundaries(double OA, double CA,double CA2,volatile double boundaries[NUM_STATES + 1]) {
    boundaries[0] = 0;
    boundaries[1] = CA;
  //  boundaries[2] = PI * 2 / 3 - CA2;  // 120 degrees minus CA2
    boundaries[2] = PI * 2 / 3;      // 120 degrees
    boundaries[3] = PI * 2 / 3 + CA; // 120 degrees plus CA
   // boundaries[5] = PI * 4 / 3 - CA2;      // 240 degrees minus CA2
    boundaries[4] = PI * 4 / 3;           // 240 degrees
    boundaries[5] = PI * 4 / 3 + CA;      // 240 degrees plus CA
   // boundaries[8] = PI * 2 - CA2;         // 360 degrees minus CA2
    boundaries[6] = 2 * PI;              // 360 degrees or 2Ï€
}

/**
 * @brief Sets the current state of the state machine based on the given angle.
 * 
 * This function determines which state the given angle falls into and sets
 * the state machine's current state to that state. The states are expected
 * to cover the full range of 0 to 2Ï€ radians. If the angle falls outside
 * this range, it will be normalized to fit within 0 to 2Ï€.
 *
 * @param sm Pointer to the state machine object.
 * @param angle The angle in radians, expected to be between 0 and 2Ï€.
 */
void setCurrentStateByAngle( StateMachine* sm, double angle) {
    // Normalize the angle to the range of 0 to 2Ï€
    angle = fmod(angle, 2 * PI);
int i;
    for ( i = 0; i < NUM_STATES; i++) {
        if (angle >= sm->states[i].startAngle && angle < sm->states[i].endAngle) {
            sm->currentState = &(sm->states[i]);
            sm->isFirstTargetSet = 1;
            return; // Exit once the correct state is found
        }
    }

    // Fallback to the first state if no state matches the angle
    sm->currentState = &(sm->states[0]);
    sm->isFirstTargetSet = 1;
}

/**
 * @brief Executes the action function of the current state in the state machine.
 * 
 * This function invokes the action associated with the current state of the
 * state machine. If the current state has a valid action function, it will be
 * called. If the current state's action function is NULL, no action will be taken.
 *
 * @param sm Pointer to the state machine object.
 */
void executeCurrentStateAction( StateMachine* sm) {

    if (sm->isFiringON==1 && sm->currentState != NULL && sm->currentState->action != NULL) {
        sm->currentState->action(); // Call the action function of the current state
    }
}
void setFiring(StateMachine* sm,int fire){
    sm->isFiringON = fire;
}

void simplifiedTransitionState(StateMachine* sm, double theta) {
    if (theta >= 0 && theta < (2 * PI / 3)) {  // 0 to 120 degrees
        H1L1_L2_L3_pwm1();  // Execute action for the first segment
    } else if (theta >= (2 * PI / 3) && theta < (4 * PI / 3)) {  // 120 to 240 degrees
        H2L2_L3_pwm1();  // Execute action for the second segment
    } else if (theta >= (4 * PI / 3) && theta <= 2 * PI) {  // 240 to 360 degrees
        H3L3_L4_pwm1();  // Execute action for the third segment
    }
}

void checkRpmTriggerAtBoundary(double theta) {
    double resetThreshold = 3.0;  // Define a threshold close to 2*pi to reset the trigger

    if ((theta >= 0)&&(theta <= 2.9) && (triggerAllowed)) {
        stateMachine.StartTimer = 1;  // Set StartTimer to trigger RPM calculation
        triggerAllowed = false;  // Prevent further triggers until reset
    }

    // Reset the trigger when theta is close to completing the cycle (near 2*pi)
    if (theta > resetThreshold) {
        triggerAllowed = true;
    }
}

void findBoundary(double elecAngle, volatile double boundaries[]) {
    int i;
    for ( i = 0; i < NUM_STATES; i++) {
        if (elecAngle >= boundaries[i] && elecAngle < boundaries[i + 1]) {
            currentBoundary = i;
            break;
        }
    }
}

void updateAngleOfInterest(volatile double boundaries[]) {

    if (currentBoundary < NUM_STATES) {
        angleOfInterest = boundaries[currentBoundary + 1];
    } else {
        currentBoundary = 0;
        angleOfInterest = boundaries[currentBoundary + 1];
    }
}
void simplifiedTransitionStateForStart(StateMachine* sm, float theta) {
    if (theta >= 0 && theta < (120 * M_PI / 180)) {  // 0 to 120 degrees
        H1L1_L2_L3_pwm1();  // Execute action for the first segment
    } else if (theta >= (120 * M_PI / 180) && theta < (140 * M_PI / 180)) {   // 120 to 140 degrees
        H1L1_L3_pwm1();
    } else if (theta >= (140 * M_PI / 180) && theta < (240 * M_PI / 180)) {  // 140 to 240 degrees
        H2L2_L3_pwm1();  // Execute action for the second segment
    } else if (theta >= (240 * M_PI / 180) && theta < (260 * M_PI / 180)) {  // 240 to 260 degrees
        H2L2_L4_pwm1();  // Execute action for the fourth segment
    } else if (theta >= (260 * M_PI / 180) && theta <= 2 * M_PI) {  // 260 to 360 degrees
        H3L3_L4_pwm1();  // Execute action for the fifth segment
    }
}

#include "SignalProcessing.h"
#include "srm/Globals.h"
// typedef SignalProcessorState;

void initializeSignalProcessor(SignalProcessorState *state) {
    state->trackingMin = state->trackingMax = state->crossoverTarget = INITIAL_CROSSOVER;
    state->min = -4095;
    state->max = 4095;
// Calculate and initialize midpoint and range
    state->midpoint = (state->min + state->max) / 2.0;
    state->range = state->max - state->min;
    state->lastValue = 0.0;
    state->cycleCount = 0;
    state->state = WAIT_FOR_ZERO_CROSSING;
    state->outerBandDelta = 100.0;
    int i;
    for ( i = 0; i < 3; i++) {
        state->x[i] = state->y[i] = 0;
        }
    }


void resetCycleData(SignalProcessorState *state) {
    state->trackingMax = state->trackingMin = state->crossoverTarget;
    state->cycleCount = 0;
}


double processSignal(SignalProcessorState *state, signed int newValue) {
    // Inline the Butterworth filter calculation for efficiency
    state->x[2] = state->x[1];
    state->x[1] = state->x[0];
    state->x[0] = newValue;
    state->y[2] = state->y[1];
    state->y[1] = state->y[0];
    state->y[0] = B0 * state->x[0] + B1 * state->x[1] + B2 * state->x[2] - A1 * state->y[1] - A2 * state->y[2];
//
// //state->y[0] = B0 * state->x[0] + B1 * state->x[1] + B2 * state->x[2] - A1 * state->y[1] - A2 * state->y[2];
//    state->y[0]=B0*state->x[0]+B1*state->x[1]+B2*state->x[2]-A1*state->y[1]-A2 * state->y[2];
   // float filteredValue=newValue;
       // Shift input history
//           state->x[1] = state->x[0];
//           state->x[0] = newValue;
//
//           // Compute new output
//           state->y[1] = state->y[0];
//           state->y[0] = B0 * state->x[0] + B1 * state->x[1] - A1 * state->y[1];

    if (RPM <= RPM_THRESHOLD_Tracking_Off) {
          trackOffset(state, state->y[0]);
      }
    else
    {
            state->midpoint = (state->lastMin + state->lastMax) / 2.0;
                state->range = state->lastMax - state->lastMin;
             //   state->cycleCount=0;
    }
        if (state->cycleCount == 4) {
                   // Process the full cycle, using the min and max from the previous cycle
            if (RPM <= RPM_THRESHOLD_Tracking_Off) {
                       state->min = state->trackingMin;
                       state->max = state->trackingMax;
                   } else {
                       // Use last tracked values
                       state->min = state->lastMin;
                       state->max = state->lastMax;
                   }
//                                   state->min = state->trackingMin;
//                                  state->max = state->trackingMax;
            state->midpoint = (state->min + state->max) / 2.0;
            state->range = state->max - state->min;
                   // Reset for the next cycle
            // Store the current cycle's min and max as lastMin and lastMax
                    state->lastMin = state->trackingMin;
                    state->lastMax = state->trackingMax;

            state->trackingMax = state->trackingMin = state->crossoverTarget;
                state->cycleCount = 0;
                   // Reset cycle count and state
                   state->state = WAIT_FOR_ZERO_CROSSING;
               }
    // Directly return the normalized value
  //  return ( newValue - state->midpoint) / state->range * 2 * N;
    return ( state->y[0] - state->midpoint) / state->range * 2 * N;
}



inline void trackOffset(SignalProcessorState *state, signed int newValue){
    // Update min/max regardless of state
    state->trackingMin = (newValue < state->trackingMin) ? newValue : state->trackingMin;
    state->trackingMax = (newValue > state->trackingMax) ? newValue : state->trackingMax;


    switch (state->state) {
        case WAIT_FOR_ZERO_CROSSING:
            if ((state->lastValue <= state->crossoverTarget && newValue > state->crossoverTarget) ||
                (state->lastValue >= state->crossoverTarget && newValue < state->crossoverTarget)) {
                // Zero crossing detected, decide which outer band to wait for
                state->state = (newValue > state->crossoverTarget) ? WAIT_FOR_OUTER_CROSSING_UP : WAIT_FOR_OUTER_CROSSING_DOWN;
            }
            break;
        case WAIT_FOR_OUTER_CROSSING_UP:
            if (newValue >= state->crossoverTarget + state->outerBandDelta) {
                // Successfully crossed the upper outer band, count the cycle
                state->cycleCount++;
                // Reset to wait for the next zero crossing
                state->state = WAIT_FOR_ZERO_CROSSING;
            }
            break;
        case WAIT_FOR_OUTER_CROSSING_DOWN:
            if (newValue <= state->crossoverTarget - state->outerBandDelta) {
                // Successfully crossed the lower outer band, count the cycle
                state->cycleCount++;
                // Reset to wait for the next zero crossing
                state->state = WAIT_FOR_ZERO_CROSSING;
            }
            break;
    }
    state->lastValue = newValue; // Update last value for next comparison
}
// Function to adjust the magnitude of the cosine signal to match the sine signal
// Function to adjust the magnitude of the cosine signal to match the sine signal
double adjustCosineMagnitude(SignalProcessorState *sineState, SignalProcessorState *cosineState) {
    double sineRange = sineState->max - sineState->min;
    double cosineRange = cosineState->max - cosineState->min;

    // Scale cosine signal to match sine signal range
    double scalingFactor = sineRange / cosineRange;

    // Apply scaling to the current output
    double adjustedCosine = cosineState->y[0] * scalingFactor;

    // Adjust the tracked min and max to reflect the scaling
//    cosineState->trackingMin *= scalingFactor;
//    cosineState->trackingMax *= scalingFactor;
//    cosineState->min *= scalingFactor;
//    cosineState->max *= scalingFactor;
//    cosineState->midpoint *= scalingFactor;
//    cosineState->range = sineRange; // Now cosine range matches sine range

    // Return the adjusted cosine value
    return adjustedCosine;

}

/*
inline void trackOffset2(SignalProcessorState *state, float newValue) {
    // Update min/max regardless of state
    state->trackingMin = (newValue < state->trackingMin) ? newValue : state->trackingMin;
    state->trackingMax = (newValue > state->trackingMax) ? newValue : state->trackingMax;

    // Define condition flags
    const int CROSSING_UP = 1 << 0;
    const int CROSSING_DOWN = 1 << 1;
    const int OUTER_UP_COMPLETE = 1 << 2;
    const int OUTER_DOWN_COMPLETE = 1 << 3;

    // Calculate the current condition
    int condition = 0;
    if (state->lastValue <= state->crossoverTarget && newValue > state->crossoverTarget) {
        condition |= CROSSING_UP;
    }
    if (state->lastValue >= state->crossoverTarget && newValue < state->crossoverTarget) {
        condition |= CROSSING_DOWN;
    }
    if (state->state == WAIT_FOR_OUTER_CROSSING_UP && newValue >= state->crossoverTarget + state->outerBandDelta) {
        condition |= OUTER_UP_COMPLETE;
    }
    if (state->state == WAIT_FOR_OUTER_CROSSING_DOWN && newValue <= state->crossoverTarget - state->outerBandDelta) {
        condition |= OUTER_DOWN_COMPLETE;
    }

    // Determine the next state using bitwise checks
    if (condition & CROSSING_UP) {
        state->state = WAIT_FOR_OUTER_CROSSING_UP;
    } else if (condition & CROSSING_DOWN) {
        state->state = WAIT_FOR_OUTER_CROSSING_DOWN;
    } else if (condition & OUTER_UP_COMPLETE) {
        state->cycleCount++;
        state->state = WAIT_FOR_ZERO_CROSSING;
    } else if (condition & OUTER_DOWN_COMPLETE) {
        state->cycleCount++;
        state->state = WAIT_FOR_ZERO_CROSSING;
    }

    state->lastValue = newValue; // Update last value for next comparison
}
*/

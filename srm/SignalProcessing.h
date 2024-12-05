#include "VirtualEncoder.h"
#ifndef SIGNAL_PROCESSING_H
#define SIGNAL_PROCESSING_H

#include <srm/Constants.h>


typedef enum {
    WAIT_FOR_ZERO_CROSSING,    // Initial state, waiting for a zero crossing
    WAIT_FOR_OUTER_CROSSING_UP,   // After zero crossing, waiting to cross the upper band
    WAIT_FOR_OUTER_CROSSING_DOWN // After zero crossing, waiting to cross the lower band
} CrossingState;


typedef struct {
    signed int trackingMin;
    signed int trackingMax;
    signed int min;
    signed int max;
    double midpoint;
    double range;
    double crossoverTarget;
    int cycleCount;
    CrossingState state;
    double outerBandDelta; // The delta for the outer band
    signed int x[3]; // Input buffer for the filter
    double y[3]; // Output buffer for the filter
    double lastValue;
    double lastMin;
    double lastMax;
} SignalProcessorState;



void resetCycleData(SignalProcessorState *state);
inline void trackOffset(SignalProcessorState *state, signed int newValue);
//float correctOffsetAndNormalize(SignalProcessorState *state, float newValue);
//float applyButterworthFilter(SignalProcessorState *state, float input);

double processSignal(SignalProcessorState *state, signed int newValue);
void initializeSignalProcessor(SignalProcessorState *state);
double adjustCosineMagnitude(SignalProcessorState *sineState, SignalProcessorState *cosineState);
#endif // SIGNAL_PROCESSING_H

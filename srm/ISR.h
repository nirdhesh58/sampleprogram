#ifndef INTERRUPT_SERVICE_ROUTINES_H
#define INTERRUPT_SERVICE_ROUTINES_H
#include <stdio.h>

__interrupt void CosineSamplingIsr(void);
__interrupt void SineSamplingIsr(void);
__interrupt void TriggerAdcSamplingIsr(void);
__interrupt void actuate(void);
__interrupt void Timer0ForRemote(void);
__interrupt void Timer1ForRPM(void);
__interrupt void Timer2ForVirtual(void);
#endif // INTERRUPT_SERVICE_ROUTINES_H

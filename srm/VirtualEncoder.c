#include "VirtualEncoder.h"
#include "f28x_project.h"

volatile double previousElecAngle1 = 0.0f;
volatile double previousElecAngle2 = 0.0f;
volatile double previousElecAngle3 = 0.0f;

volatile double difference = 0.0f;
volatile double timeInUs = 0.0f; // Time in microseconds
volatile double finalTimeInUs = 0.0f; // Time after subtracting additional time
volatile double additionalTimeInUs = 20.0f; // Example additional time to subtract in microseconds
volatile double nsCount=0;
volatile int samplingtimeinCount=481;
volatile int additionalTimeInCount=0;
volatile int FinalTimeToReachAOI=0;

//void virtualEncoder(float elecAngle) {
//    // Increment the sample counter
//    sampleCounter++;
//    float predictedAnglein2Samples=0;
//    if (sampleCounter == 1) {
//        // First task: Compute boundaries and find the initial boundary for elecAngle
//
//        computeBoundaries(OverlapAngle, ConductionAngle,ConductionAngle2, stateBoudnaries);
//        findBoundary(elecAngle, stateBoudnaries);
//        updateAngleOfInterest(stateBoudnaries);
//    } else if (sampleCounter >= 3) {
//        sampleCounter=4;
//        // Calculate the predicted angle in 2 samples
//        float deltaAngle1 = elecAngle - previousElecAngle1;
//        if (previousElecAngle1 > elecAngle) {
//                  deltaAngle1 += 2 * M_PI;
//              }
//        float deltaAngle2 = previousElecAngle1 - previousElecAngle2;
//           if (previousElecAngle2 > previousElecAngle1) {
//                    deltaAngle2 += 2 * M_PI;
//                }
//         predictedAnglein2Samples = elecAngle + deltaAngle1 + deltaAngle2;
//         TestAngle=         predictedAnglein2Samples;
//
//        // Compare predictedAnglein2Samples with angleOfInterest
//        if ((predictedAnglein2Samples >= angleOfInterest)&&(VitualTimerStarted==0))
//        {
//            // Angle of interest is lesser than or equal to the predicted angle, calculate the difference
//            difference = angleOfInterest - elecAngle;
//C=difference;
//            // Calculate angular velocity (rad/s)
//            float angularVelocity = (deltaAngle1 + deltaAngle2) / 80e-6; // 80 microseconds for two samples
//
//            // Calculate time in microseconds to reach angleOfInterest
//            timeInUs = (difference * angularVelocity); // Convert seconds to microseconds
//            A=timeInUs;
//            nsCount=timeInUs/8.3e-3;
//            count=nsCount;
//            additionalTimeInCount=EPwm5Regs.TBCTR;
//            FinalTimeToReachAOI= nsCount-additionalTimeInCount;
//           // B=FinalTimeToReachAOI;
//            // Subtract additional time
//            CpuTimer2Regs.PRD.all=FinalTimeToReachAOI; //10us//.5Sec period //
//            CpuTimer2Regs.TCR.bit.TRB = 1;  //reload the period
//            CpuTimer2Regs.TCR.bit.TSS=0; // toStart timer
//            VitualTimerStarted=1;
//
//            // Update to next angle of interest
//         //   currentBoundary++;
//
//            updateAngleOfInterest(stateBoudnaries);
//            if ((currentBoundary+1) > NUM_STATES)
//                       {
//                           currentBoundary=0;
//                       }
//        } else {
//            // Angle of interest is greater than the predicted angle, no action needed
//            difference = 0.0f;
//            timeInUs = 0.0f;
//            finalTimeInUs = 0.0f;
////             count1++;
////            if(count1<2)
////             {
////                 count1=0;
////                VitualTimerStarted=0;
////               }
//        }
//
//        // You can use predictedAnglein2Samples, difference, timeInUs, and finalTimeInUs as needed within this function
//    }
//
//    // Update the previous samples for the next iteration
//    previousElecAngle2 = previousElecAngle1;
//    previousElecAngle1 = elecAngle;
//}

void virtualEncoder(double elecAngle) {
    // Increment the sample counter
    VirtualencoderStarted=1;
    sampleCounter++;
    double predictedAnglein4Samples = 0;

    if (sampleCounter == 1) {
        // First task: Compute boundaries and find the initial boundary for elecAngle
        computeBoundaries(OverlapAngle, ConductionAngle, ConductionAngle2, stateBoudnaries);
        findBoundary(elecAngle, stateBoudnaries);
        updateAngleOfInterest(stateBoudnaries);
    } else if (sampleCounter >= 3) {
        sampleCounter = 4; // Maintain sample counter at 4 for stable prediction


        // Calculate the predicted angle in 2 samples
        double deltaAngle = previousElecAngle1 - previousElecAngle3;
        double AngleVariationin1Sample=2*PI/(numSamplesToconsider);

//        if (previousElecAngle3 > previousElecAngle1) {
//            deltaAngle += 2 * PI;
//        }

        predictedAnglein4Samples = previousElecAngle1 +( (AngleVariationin1Sample)*4);
//        if(predictedAnglein4Samples>(2*PI))
//        {
//            predictedAnglein4Samples-=2 * PI;
//            angleOfInterest=0;
//            currentBoundary=0;
//        }
        TestAngle = predictedAnglein4Samples; // For debugging
        A=previousElecAngle1;
        B=previousElecAngle2;
        C=previousElecAngle3;
            if(currentBoundary==0)
              {
                if ((previousElecAngle3 < angleOfInterest &&  previousElecAngle3>0)&& (previousElecAngle2 < angleOfInterest && previousElecAngle2> 0 ) &&( previousElecAngle1 < angleOfInterest && previousElecAngle1>0))
                {
                  StartVirtual=1;
                }else
                {
                     StartVirtual=0;
                }
              }
              else
              {
                  StartVirtual=1;
              }
           // StartVirtual=1;
        // Compare predictedAnglein2Samples with angleOfInterest
        if ((predictedAnglein4Samples >= angleOfInterest) && (VitualTimerStarted == 0)&&(StartVirtual==1)) {
            // Angle of interest is lesser than or equal to the predicted angle
            difference = angleOfInterest - previousElecAngle1;
            if (previousElecAngle1 > angleOfInterest) {
                difference += 2 * PI;
                    }
        //    A = difference; // For debugging

            // Calculate angular velocity (rad/s)
            double angularDelta= ((AngleVariationin1Sample)*4); // 80 microseconds for two samples
         //   B=angularDelta;
            // Calculate time in microseconds to reach angleOfInterest
            timeInUs = (difference / angularDelta)*160 ; // Convert seconds to microseconds
        //    C = timeInUs; // For debugging

            // Convert time to timer counts
            nsCount = timeInUs *120.48192;
            count=nsCount;
            additionalTimeInCount = EPwm5Regs.TBCTR;
            D=additionalTimeInCount;
            FinalTimeToReachAOI = nsCount - additionalTimeInCount-4819;
            E = FinalTimeToReachAOI;
            // Set up and start the timer
            if(FinalTimeToReachAOI>0)
            {
            CpuTimer2Regs.PRD.all = FinalTimeToReachAOI;
            CpuTimer2Regs.TCR.bit.TRB = 1;  // Reload the period
            CpuTimer2Regs.TCR.bit.TSS = 0; // Start the timer
          //   GpioDataRegs.GPATOGGLE.bit.GPIO16=1;

            VitualTimerStarted = 1;


            // Update to next angle of interest
                    currentBoundary++;
                         updateAngleOfInterest(stateBoudnaries);
//            if ((currentBoundary + 1) > NUM_STATES) {
//                currentBoundary = 0;
//            }
            }
        } else {
            // Angle of interest is greater than the predicted angle, no action needed
            difference = 0.0f;
            timeInUs = 0.0f;
            finalTimeInUs = 0.0f;
        }
    }

    // Update the previous samples for the next iteration
    previousElecAngle3 = previousElecAngle2;
    previousElecAngle2 = previousElecAngle1;
    previousElecAngle1 = elecAngle;
}

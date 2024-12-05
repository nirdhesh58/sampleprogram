#ifndef ANGLE_CONVERSION_H
#define ANGLE_CONVERSION_H

#include <math.h>
#include <srm/Constants.h>
#include <srm/Globals.h>

// Function to calculate the electrical angle based on the mechanical angle and an advance angle
static inline double mechanicalToElectricalRotation(double mechAngle, double advance) {
    double elecAngle = (RotorPoles*0.5) * mechAngle;  // Scale mechanical angle by 5 for the electrical rotation  poles divede by 2
//     double  DACelecAngle=0;
//    DACelecAngle = fmod(elecAngle, 2 * M_PI);
//    if (DACelecAngle < 0) {
//        DACelecAngle += 2 * M_PI;
//        }
    elecAngle=elecAngle+advance;

    // Normalize elecAngle to be within 0 to 2*pi
    elecAngle = fmod(elecAngle, 2 * PI);

    // Adjust if elecAngle is negative, to ensure it is within 0 to 2*pi
    if (elecAngle < 0) {
        elecAngle += 2 * PI;
    }
    //  Cmpss1Regs.DACLVALS.bit.DACVAL=DACelecAngle*500;
 //   return ((2 * M_PI)-elecAngle);
    return (elecAngle);
}

// Function to convert degrees to radians, normalized to 0-2pi
static inline double degreesToRadians(double degrees) {
    double radians = degrees * (PI / 180.0);

    // Normalize to 0-2pi
    radians = fmod(radians, 2 * PI);
    if (radians < 0) {
        radians += 2 * PI;
    }

    return radians;
}

// Function to convert radians to degrees, normalized to 0-360
static inline double radiansToDegrees(double radians) {
    double degrees = radians * (180.0 / PI);

    // Normalize to 0-360
    degrees = fmod(degrees, 360.0);
    if (degrees < 0) {
        degrees += 360.0;
    }

    return degrees;
}

#endif // ANGLE_CONVERSION_H

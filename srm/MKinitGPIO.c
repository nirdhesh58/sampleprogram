/*
 * MKinitGPIO.c
 *
 *  Created on: 30-Sep-2023
 *      Author: Manoj kumar parupalli
 */

#include "F28x_Project.h"
#include "f280013x_examples.h"
#include "MKpwm.h"

//void MKinitGPIO(void)
//{
//    EALLOW;
//
//        GpioCtrlRegs.GPALOCK.all = 0x00000000;
//        GpioCtrlRegs.GPBLOCK.all = 0x00000000;
//        GpioCtrlRegs.GPHLOCK.all = 0x00000000;
//
////////////////Pwm Signals gpio select////////////////////
////////////////////////////H1  4A
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO2=3;     // H1 pwm
//        GpioCtrlRegs.GPAMUX1.bit.GPIO2=3;   //configure as EPWM
//        GpioCtrlRegs.GPAPUD.bit.GPIO2=1;   //pullup disabled
////////////////////////////L1  4B
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO3=3;     // L1 pwm
//        GpioCtrlRegs.GPAMUX1.bit.GPIO3=3;   //configure as EPWM
//        GpioCtrlRegs.GPAPUD.bit.GPIO3=1;   //pullup disabled
//
//             //   GpioCtrlRegs.GPAGMUX1.bit.GPIO3=0;     // L1 Gpio
//               // GpioCtrlRegs.GPAMUX1.bit.GPIO3=0;   //configure as Gpio
//               // GpioCtrlRegs.GPADIR.bit.GPIO3=1;   //output
//               // GpioCtrlRegs.GPAPUD.bit.GPIO3=0;   //pullup enabled
//               // GpioDataRegs.GPADAT.bit.GPIO3=0;   //set as low
//
////////////////////////////L2  6B
//        GpioCtrlRegs.GPAGMUX2.bit.GPIO19=1;  //L2
//        GpioCtrlRegs.GPAMUX2.bit.GPIO19=1;   //configure as EPWM
//        GpioCtrlRegs.GPAPUD.bit.GPIO19=1;   //pullup disabled
//
////                       GpioCtrlRegs.GPAGMUX2.bit.GPIO19=0;  //L2
////                       GpioCtrlRegs.GPAMUX2.bit.GPIO19=0;   //configure as Gpio
////                       GpioCtrlRegs.GPADIR.bit.GPIO19=1;    // output
////                       GpioCtrlRegs.GPAPUD.bit.GPIO19=0;   //pullup enabled
////                       GpioDataRegs.GPADAT.bit.GPIO19=0;   // to make it low;
//
////////////////////////////H2  6A
//        GpioCtrlRegs.GPAGMUX2.bit.GPIO18=1;
//        GpioCtrlRegs.GPAMUX2.bit.GPIO18=1;   //configure as EPWM
//        GpioCtrlRegs.GPAPUD.bit.GPIO18=1;   //pullup disabled
//
////////////////////////////H3  1A
//        GpioCtrlRegs.GPHAMSEL.bit.GPIO224 = 0;   // 0 makes gpio
//        AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO224 = 1;
//
//        GpioCtrlRegs.GPHGMUX1.bit.GPIO224=2;
//        GpioCtrlRegs.GPHMUX1.bit.GPIO224=1; //configure as EPWM
//        GpioCtrlRegs.GPHPUD.bit.GPIO224=1;  //pullup disabled
////
////                       GpioCtrlRegs.GPHGMUX1.bit.GPIO224=0;   //L3
////                       GpioCtrlRegs.GPHMUX1.bit.GPIO224=0;  // configure as EPWM
////                       GpioCtrlRegs.GPHDIR.bit.GPIO224=1;   // output
////                       GpioCtrlRegs.GPHPUD.bit.GPIO224=0;  //pullup enabled
////                       GpioDataRegs.GPHDAT.bit.GPIO224=0;  // L3 low
////////////////////////////L3  1B
//        GpioCtrlRegs.GPHAMSEL.bit.GPIO226 = 0;      // asigned to gpio port
//        AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO226 = 1;
//
//       GpioCtrlRegs.GPHGMUX1.bit.GPIO226=2;
//        GpioCtrlRegs.GPHMUX1.bit.GPIO226=1;  // configure as EPWM
//        GpioCtrlRegs.GPHPUD.bit.GPIO226=1;  //pullup disabled
//
////                GpioCtrlRegs.GPHGMUX1.bit.GPIO226=0;   //L3
////                GpioCtrlRegs.GPHMUX1.bit.GPIO226=0;  // configure as EPWM
////                GpioCtrlRegs.GPHDIR.bit.GPIO226=1;   // output
////                GpioCtrlRegs.GPHPUD.bit.GPIO226=0;  //pullup enabled
////                GpioDataRegs.GPHDAT.bit.GPIO226=0;  // L3 low
//
////////////////////////////H4  2A
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO6=3;
//        GpioCtrlRegs.GPAMUX1.bit.GPIO6=3;  // configure as EPWM
//        GpioCtrlRegs.GPAPUD.bit.GPIO6=1;  //pullup disabled
//
////                GpioCtrlRegs.GPAGMUX1.bit.GPIO6=0;
////                GpioCtrlRegs.GPAMUX1.bit.GPIO6=0;  // configure as EPWM
////                GpioCtrlRegs.GPADIR.bit.GPIO6=1;   // output
////                GpioCtrlRegs.GPAPUD.bit.GPIO6=0;  //pullup enabled
//////////////////////////////L4  2B
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO7=3;
//        GpioCtrlRegs.GPAMUX1.bit.GPIO7=3;  // configure as EPWM
//        GpioCtrlRegs.GPAPUD.bit.GPIO7=1;  //pullup disabled
//
////                GpioCtrlRegs.GPAGMUX1.bit.GPIO7=0;
////                GpioCtrlRegs.GPAMUX1.bit.GPIO7=0;  // configure as gpio
////                GpioCtrlRegs.GPAPUD.bit.GPIO7=0;  //pullup enabled
////                GpioCtrlRegs.GPADIR.bit.GPIO7=1;   // output
////
////
////                GpioCtrlRegs.GPAGMUX1.bit.GPIO7=0;
////                GpioCtrlRegs.GPAMUX1.bit.GPIO7=0;  // configure as EPWM
////                GpioCtrlRegs.GPADIR.bit.GPIO7=1;   // output
////                GpioCtrlRegs.GPAPUD.bit.GPIO7=0;  //pullup enabled
////                GpioDataRegs.GPADAT.bit.GPIO7=0 ;  // L4 low
//
//////////////////Pwm pin config end /////////////////////////////////
////////////////SCI pin Config///////////////////////////////////////////
//
/////////////////////SCI C RX    pin 1
//       /* GpioCtrlRegs.GPAGMUX2.bit.GPIO29=2;
//        GpioCtrlRegs.GPAMUX2.bit.GPIO29=2; /// SCIC RX
//        GpioCtrlRegs.GPAPUD.bit.GPIO29=0;  //pullup enabled*/
//
//                GpioCtrlRegs.GPAGMUX2.bit.GPIO29=0;
//                GpioCtrlRegs.GPAMUX2.bit.GPIO29=0; /// as Gpio
//                GpioCtrlRegs.GPADIR.bit.GPIO29=0;  // as input
//                GpioCtrlRegs.GPAQSEL2.bit.GPIO29=2; // six samples
//                GpioCtrlRegs.GPAPUD.bit.GPIO29=0;  //pullup enabled
//
///////////////////   SCI C TX   pin 2
//        GpioCtrlRegs.GPAAMSEL.bit.GPIO28 = 1;
//        AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO28 = 1;
//
//   /*     GpioCtrlRegs.GPAGMUX2.bit.GPIO28=2;
//        GpioCtrlRegs.GPAMUX2.bit.GPIO28=2;  // configure as SCI
//        GpioCtrlRegs.GPAPUD.bit.GPIO28=0;  //pullup enabled*/
//
//
//
///////////////////   SCI A RX
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO0=0;
//        GpioCtrlRegs.GPAMUX1.bit.GPIO0=0;  // configure as SCI
//        GpioCtrlRegs.GPAPUD.bit.GPIO0=1;  //pullup enabled
//        GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;         // as digital input
//
///////////////////   SCI A TX  //
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO1=1;
//        GpioCtrlRegs.GPAMUX1.bit.GPIO1=1;  // configure as SCI
//        GpioCtrlRegs.GPAPUD.bit.GPIO1=0;  //pullup enabled
//
///////////////////SCI C RX launchpad
//        /*          GpioCtrlRegs.GPAGMUX2.bit.GPIO23=2;
//               GpioCtrlRegs.GPAMUX2.bit.GPIO23=0; /// SCIC RX
//               GpioCtrlRegs.GPAPUD.bit.GPIO23=0;  //pullup enabled*/
/////////////////// SCI PIN CONFIG END//////////////////////////////////////
//
/////////////////// I2C Pin Config //////////////////////////
//
//        GpioCtrlRegs.GPBGMUX1.bit.GPIO33 = 0;     // presenly configured as gpio in future if u use I2C configure this pins
//        GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;        // as GPIO
//        GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;         // as digital output
//        GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;         //pullup enabled
//
//        GpioCtrlRegs.GPBGMUX1.bit.GPIO32 = 0;     // presenly configured as gpio in future if u use I2C configure this pins
//        GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;        // as gpio
//        GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;         // as digital output
//        GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;         //pullup enabled
//
//////////////////////I2C pin Config end///////////////////////
//
//////////////Gpio pin config///////////////////////////////////
//        GpioCtrlRegs.GPHAMSEL.bit.GPIO242 = 0;   // 0 makes gpio
//        AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO242 = 1;
//
//        GpioCtrlRegs.GPHGMUX2.bit.GPIO242 = 0;     // presenly configured as gpio
//        GpioCtrlRegs.GPHMUX2.bit.GPIO242 = 0;        // as GPIO
//        GpioCtrlRegs.GPHDIR.bit.GPIO242 = 1;         // as digital output
//        GpioCtrlRegs.GPHPUD.bit.GPIO242 = 0;         //pullup enabled
//
//        GpioCtrlRegs.GPHAMSEL.bit.GPIO227 = 0;   // 0 makes gpio
//        AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO227 = 1;
//
//        GpioCtrlRegs.GPHGMUX1.bit.GPIO227 = 0;     // presenly configured as gpio
//        GpioCtrlRegs.GPHMUX1.bit.GPIO227 = 0;        // as GPIO
//        GpioCtrlRegs.GPHDIR.bit.GPIO227 = 1;         // as digital output
//        GpioCtrlRegs.GPHPUD.bit.GPIO227 = 0;         //pullup enabled
//
//        GpioCtrlRegs.GPHAMSEL.bit.GPIO230 = 0;   // 0 makes gpio
//        AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO230 = 1;
//
//        GpioCtrlRegs.GPHGMUX1.bit.GPIO230 = 0;     // presenly configured as gpio
//        GpioCtrlRegs.GPHMUX1.bit.GPIO230 = 0;        // as GPIO
//        GpioCtrlRegs.GPHDIR.bit.GPIO230 = 1;         // as digital output
//        GpioCtrlRegs.GPHPUD.bit.GPIO230 = 0;         //pullup enabled
//
//        GpioCtrlRegs.GPAAMSEL.bit.GPIO13 = 0;   // 0 makes gpio
//        AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO13 = 1;
//
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO13 = 0;     // presenly configured as gpio
//        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;        // as GPIO
//        GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;         // as digital output
//        GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;         //pullup enabled
//
///////////////////buzzer connected to this pin /////////////
//        GpioCtrlRegs.GPAAMSEL.bit.GPIO12 = 0;   // 0 makes gpio
//        AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO12 = 1;
//
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO12 = 0;     // presenly configured as gpio
//        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;        // as GPIO
//        GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;         // as digital output
//        GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;         //pullup enabled
///////////////////////////// Buzzer end ////////////////////
//////////////////////////not connected ////////////////
//        GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 0;     // presenly configured as gpio
//        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;        // as GPIO
//        GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;         // as digital output
//        GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;         //pullup enabled
//
//        GpioCtrlRegs.GPAGMUX2.bit.GPIO24 = 0;     // presenly configured as gpio
//        GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;        // as GPIO
//        GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;         // as digital output
//        GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;         //pullup enabled
//
//                GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 0;     // presenly configured as gpio
//                GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;        // as GPIO
//                GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;         // as digital output
//                GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;         //pullup enabled
//
//////////////////////////RED LED Connected/////////////////////////////////////
//
//        GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = 0;     // presenly configured as gpio
//        GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;        // as GPIO
//        GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;         // as digital output
//        GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;         //pullup enabled
//        GpioDataRegs.GPADAT.bit.GPIO4=0;          //output high
///////////////////////////Red Led config end//////////////////////////////////////
//
// ///////////////////////end pin config////////////
//
//
//        EDIS;
//    }
//
//void MKinitGPIOLaunchpad(void)
//{
//    EALLOW;
//            GpioCtrlRegs.GPALOCK.all = 0x00000000;
//            GpioCtrlRegs.GPBLOCK.all = 0x00000000;
//            GpioCtrlRegs.GPHLOCK.all = 0x00000000;
//    ///////////////J1 connecter//////
//    ///Gpio28/////
//          GpioCtrlRegs.GPAGMUX2.bit.GPIO28=0;
//           GpioCtrlRegs.GPAMUX2.bit.GPIO28=1;  // configure as SCIA RX
//           GpioCtrlRegs.GPAPUD.bit.GPIO28=0;  //pullup enabled
//     ///Gpio29//// Switch
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO29=0;
//           GpioCtrlRegs.GPAMUX2.bit.GPIO29=0; /// as Gpio
//           GpioCtrlRegs.GPADIR.bit.GPIO29=0;  // as input
//           GpioCtrlRegs.GPAQSEL2.bit.GPIO29=2; // six samples
//           GpioCtrlRegs.GPAPUD.bit.GPIO29=0;  //pullup enabled
//
//     ///Gpio9////
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO9 = 1;     //  configured as SpiA clk
//           GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 3;        //
//           GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;         //pullup enabled
//     ///Gpio24///
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO24 = 0;     // presenly configured as gpio
//           GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;        // as GPIO
//           GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;         // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;         //pullup enabled
//  //////////////// J1 connector end
//  ///////////////J5 connector ///////////////
//     ///Gpio18_X2
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 0;     // presenly configured as gpio
//           GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;        // as GPIO
//           GpioCtrlRegs.GPADIR.bit.GPIO18 = 1;         // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;         //pullup enabled
//     ///Gpio19_X1
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 0;     // presenly configured as gpio
//           GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;        // as GPIO
//             GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;         // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;         //pullup enabled
//     /////////////J5 connector end
//  //////////////J4 connector ////////
//        /*   GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0;     // presenly configured as Pwm1A
//           GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;        // as Pwm
//           GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;         //pullup enabled*/
//                      GpioCtrlRegs.GPAGMUX1.bit.GPIO0=0;             // RF input
//                      GpioCtrlRegs.GPAMUX1.bit.GPIO0=0; /// as Gpio
//                      GpioCtrlRegs.GPADIR.bit.GPIO0=0;  // as input
//                      GpioCtrlRegs.GPAQSEL1.bit.GPIO0=2; // six samples
//                      GpioCtrlRegs.GPAPUD.bit.GPIO0=0;  //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0;     // presenly configured as Pwm1B
//           GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;        // as Pwm
//           GpioCtrlRegs.GPADIR.bit.GPIO1=1;  // as output
//           GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = 0;     // presenly configured as Pwm2A     h4
//           GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;        // as Pwm
//           GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = 0;     // presenly configured as Pwm2B     L4
//           GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;        // as Pwm
//           GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO10 = 0;     // presenly configured as Pwm6A    h3
//           GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;        // as Pwm
//           GpioCtrlRegs.GPAPUD.bit.GPIO10 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO11 = 0;     // presenly configured as Pwm6B     l3
//           GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;        // as Pwm
//           GpioCtrlRegs.GPAPUD.bit.GPIO11 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPBGMUX1.bit.GPIO33=0;
//           GpioCtrlRegs.GPBMUX1.bit.GPIO33=0;  // configure as Gpio
//           GpioCtrlRegs.GPBDIR.bit.GPIO33=1;   // as digital output
//           GpioCtrlRegs.GPBPUD.bit.GPIO33=0;  //pullup enabled
//   ////////////////J4 connector end///////////////////
//
//     //////////////J8 connector /////////////////
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO12 = 0;     // presenly configured as Pwm7A
//           GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;        // as Pwm
//           GpioCtrlRegs.GPADIR.bit.GPIO12=1;   // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO13 = 0;     // presenly configured as Pwm7B
//           GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;        // as Pwm
//           GpioCtrlRegs.GPADIR.bit.GPIO13=1;   // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO6 = 0;     // presenly configured as Pwm4A  H1
//           GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;        // as Pwm
//           GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO7 = 0;     // presenly configured as Pwm4B  L1
//           GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;        // as Pwm
//           GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 0;     // presenly configured as Pwm5A
//           GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;        // as Pwm
//           GpioCtrlRegs.GPADIR.bit.GPIO16=1;   // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPBGMUX1.bit.GPIO35=2;       //// presenly configured as Pwm5B
//           GpioCtrlRegs.GPBMUX1.bit.GPIO35=2;         // as Pwm
//           GpioCtrlRegs.GPBDIR.bit.GPIO35=1;   // as digital output
//           GpioCtrlRegs.GPBPUD.bit.GPIO35 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO21 = 0;     // presenly configured as GPio
//           GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;        // as gpio
//           GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;         //pullup enabled
//           GpioCtrlRegs.GPADIR.bit.GPIO21=1;    // output direction
//
//           GpioCtrlRegs.GPBGMUX1.bit.GPIO41=0;
//           GpioCtrlRegs.GPBMUX1.bit.GPIO41=0;
//           GpioCtrlRegs.GPBDIR.bit.GPIO41=1;   // output direction
//           GpioCtrlRegs.GPBPUD.bit.GPIO41=0; //
//
//           GpioCtrlRegs.GPBGMUX1.bit.GPIO40=0;
//           GpioCtrlRegs.GPBMUX1.bit.GPIO40=0;
//           GpioCtrlRegs.GPBDIR.bit.GPIO40=1;   // output direction
//           GpioCtrlRegs.GPBPUD.bit.GPIO40=0; //
//    //////////////////J8 connector end/////////////
//
//   /////////////////J2 connector/////////////////////////
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 3;     // presenly configured as L2
//           GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;        // as GPIO
//         //  GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;         // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPBGMUX1.bit.GPIO32=0;
//           GpioCtrlRegs.GPBMUX1.bit.GPIO32=0;
//           GpioCtrlRegs.GPBDIR.bit.GPIO32=1;   // output direction
//           GpioCtrlRegs.GPBPUD.bit.GPIO32=0; //
//
//           GpioCtrlRegs.GPBGMUX1.bit.GPIO39=0;
//           GpioCtrlRegs.GPBMUX1.bit.GPIO39=0;
//           GpioCtrlRegs.GPBDIR.bit.GPIO39=1;   // output direction
//           GpioCtrlRegs.GPBPUD.bit.GPIO39=0; //
//
//           GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = 0;     // presenly configured as gpio
//           GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;        // as GPIO
//           GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;         // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO17 = 0;     // presenly configured as gpio
//           GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;        // as GPIO
//           GpioCtrlRegs.GPADIR.bit.GPIO17 = 1;         // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPBGMUX1.bit.GPIO37=0;
//           GpioCtrlRegs.GPBMUX1.bit.GPIO37=0;
//           GpioCtrlRegs.GPBDIR.bit.GPIO37=1;   // output direction
//           GpioCtrlRegs.GPBPUD.bit.GPIO37=0; //
//
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO22 = 0;     // presenly configured as gpio
//           GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;        // as GPIO
//           GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;         // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO22 = 0;         //pullup enabled
//
//           GpioCtrlRegs.GPAGMUX2.bit.GPIO23 = 0;     // presenly configured as gpio
//           GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;        // as GPIO
//           GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;         // as digital output
//           GpioCtrlRegs.GPAPUD.bit.GPIO23 = 0;         //pullup enabled
//
// //////////////////////////connector end J2////////////////
//
//  //////////////////////J6 connector///////////////////////
//
//            GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = 3;     // presenly configured as pwm   h2
//            GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 3;        // as GPIO
//          //  GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;         // as digital output
//            GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;         //pullup enabled
//
//            GpioCtrlRegs.GPAGMUX1.bit.GPIO8 = 0;     // presenly configured as gpio
//            GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 0;        // as GPIO
//            GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;         // as digital output
//            GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;         //pullup enabled
//
//            GpioCtrlRegs.GPAGMUX2.bit.GPIO20 = 0;     // presenly configured as gpio
//            GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;        // as GPIO
//            GpioCtrlRegs.GPADIR.bit.GPIO20 = 1;         // as digital output
//            GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;         //pullup enabled
//
//    ////////////////////////J6 connector end/////////////////////
//                       EDIS;
//}

void MKinitGPIO_CNDR(void)
{
    EALLOW;

        GpioCtrlRegs.GPALOCK.all = 0x00000000;
        GpioCtrlRegs.GPBLOCK.all = 0x00000000;
        GpioCtrlRegs.GPHLOCK.all = 0x00000000;

//////////////Pwm Signals gpio select////////////////////
//////////////////////////H1  4A
        GpioCtrlRegs.GPAGMUX1.bit.GPIO2=3;     // H1 pwm
        GpioCtrlRegs.GPAMUX1.bit.GPIO2=3;   //configure as EPWM
        GpioCtrlRegs.GPAPUD.bit.GPIO2=1;   //pullup disabled
//////////////////////////L1  4B
        GpioCtrlRegs.GPAGMUX1.bit.GPIO3=3;     // L1 pwm
        GpioCtrlRegs.GPAMUX1.bit.GPIO3=3;   //configure as EPWM
        GpioCtrlRegs.GPAPUD.bit.GPIO3=1;   //pullup disabled

             /*   GpioCtrlRegs.GPAGMUX1.bit.GPIO3=0;     // L1 Gpio
                GpioCtrlRegs.GPAMUX1.bit.GPIO3=0;   //configure as Gpio
                GpioCtrlRegs.GPADIR.bit.GPIO3=1;   //output
                GpioCtrlRegs.GPAPUD.bit.GPIO3=0;   //pullup enabled
                GpioDataRegs.GPADAT.bit.GPIO3=0;   //set as low */

//////////////////////////L2  6B
        GpioCtrlRegs.GPAGMUX2.bit.GPIO19=1;  //L2
        GpioCtrlRegs.GPAMUX2.bit.GPIO19=1;   //configure as EPWM
        GpioCtrlRegs.GPAPUD.bit.GPIO19=1;   //pullup disabled

//                       GpioCtrlRegs.GPAGMUX2.bit.GPIO19=0;  //L2
//                       GpioCtrlRegs.GPAMUX2.bit.GPIO19=0;   //configure as Gpio
//                       GpioCtrlRegs.GPADIR.bit.GPIO19=1;    // output
//                       GpioCtrlRegs.GPAPUD.bit.GPIO19=0;   //pullup enabled
//                       GpioDataRegs.GPADAT.bit.GPIO19=0;   // to make it low;

//////////////////////////H2  6A
        GpioCtrlRegs.GPAGMUX2.bit.GPIO18=1;
        GpioCtrlRegs.GPAMUX2.bit.GPIO18=1;   //configure as EPWM
        GpioCtrlRegs.GPAPUD.bit.GPIO18=1;   //pullup disabled

//                               GpioCtrlRegs.GPAGMUX2.bit.GPIO18=0;  //L2
//                               GpioCtrlRegs.GPAMUX2.bit.GPIO18=0;   //configure as Gpio
//                               GpioCtrlRegs.GPADIR.bit.GPIO18=1;    // output
//                               GpioCtrlRegs.GPAPUD.bit.GPIO18=0;   //pullup enabled
//                               GpioDataRegs.GPADAT.bit.GPIO18=1;   // to make it low;

//////////////////////////H3  1A
               GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = 3;     // presenly configured as pwm
               GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 3;        // as pwm
               GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;         //pullup enabled

//////////////////////////L3  1B

                               GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 3;     // presenly configured as pwm
                               GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 3;        // as pwm
                               GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;         //pullup enabled
//////////////////////////H4  2A
        GpioCtrlRegs.GPAGMUX1.bit.GPIO6=3;
        GpioCtrlRegs.GPAMUX1.bit.GPIO6=3;  // configure as EPWM
        GpioCtrlRegs.GPAPUD.bit.GPIO6=1;  //pullup disabled

          /*      GpioCtrlRegs.GPAGMUX1.bit.GPIO6=0;
                GpioCtrlRegs.GPAMUX1.bit.GPIO6=0;  // configure as EPWM
                GpioCtrlRegs.GPADIR.bit.GPIO6=1;   // output
                GpioCtrlRegs.GPAPUD.bit.GPIO6=0;  //pullup enabled*/
//////////////////////////L4  2B
        GpioCtrlRegs.GPAGMUX1.bit.GPIO7=3;
        GpioCtrlRegs.GPAMUX1.bit.GPIO7=3;  // configure as EPWM
        GpioCtrlRegs.GPAPUD.bit.GPIO7=1;  //pullup disabled

         /*       GpioCtrlRegs.GPAGMUX1.bit.GPIO7=0;
                GpioCtrlRegs.GPAMUX1.bit.GPIO7=0;  // configure as gpio
                GpioCtrlRegs.GPAPUD.bit.GPIO7=0;  //pullup enabled
                GpioCtrlRegs.GPADIR.bit.GPIO7=1;   // output*/


             /*   GpioCtrlRegs.GPAGMUX1.bit.GPIO7=0;
                GpioCtrlRegs.GPAMUX1.bit.GPIO7=0;  // configure as EPWM
                GpioCtrlRegs.GPADIR.bit.GPIO7=1;   // output
                GpioCtrlRegs.GPAPUD.bit.GPIO7=0;  //pullup enabled
                GpioDataRegs.GPADAT.bit.GPIO7=0 ;  // L4 low*/

////////////////Pwm pin config end /////////////////////////////////
//////////////SCI pin Config///////////////////////////////////////////

///////////////////SCI C RX    pin 1
       /* GpioCtrlRegs.GPAGMUX2.bit.GPIO29=2;
        GpioCtrlRegs.GPAMUX2.bit.GPIO29=2; /// SCIC RX
        GpioCtrlRegs.GPAPUD.bit.GPIO29=0;  //pullup enabled*/

                GpioCtrlRegs.GPAGMUX2.bit.GPIO29=0;
                GpioCtrlRegs.GPAMUX2.bit.GPIO29=0; /// as Gpio
                GpioCtrlRegs.GPADIR.bit.GPIO29=1;  // as output
                //GpioCtrlRegs.GPAQSEL2.bit.GPIO29=2; // six samples
                GpioCtrlRegs.GPAPUD.bit.GPIO29=0;  //pullup enabled

/////////////////   SCI C TX   pin 2
        GpioCtrlRegs.GPAAMSEL.bit.GPIO28 = 0;
        AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO28 = 1;

        GpioCtrlRegs.GPAGMUX2.bit.GPIO28=0;
        GpioCtrlRegs.GPAMUX2.bit.GPIO28=0;  // configure as SCI
        GpioCtrlRegs.GPADIR.bit.GPIO28=0;  // as input
                        GpioCtrlRegs.GPAQSEL2.bit.GPIO28=2; // six samples
                        GpioCtrlRegs.GPAPUD.bit.GPIO28=1;  //pullup enabled



/////////////////   SCI A RX
        GpioCtrlRegs.GPAGMUX1.bit.GPIO0=0;
        GpioCtrlRegs.GPAMUX1.bit.GPIO0=0;  // configure as SCI
        GpioCtrlRegs.GPAPUD.bit.GPIO0=1;  //pullup disbled
        GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;         // as digital input

/////////////////   SCI A TX  //
        GpioCtrlRegs.GPAGMUX1.bit.GPIO1=1;
        GpioCtrlRegs.GPAMUX1.bit.GPIO1=1;  // configure as SCI
        GpioCtrlRegs.GPAPUD.bit.GPIO1=0;  //pullup enabled

/////////////////SCI C RX launchpad
        /*          GpioCtrlRegs.GPAGMUX2.bit.GPIO23=2;
               GpioCtrlRegs.GPAMUX2.bit.GPIO23=0; /// SCIC RX
               GpioCtrlRegs.GPAPUD.bit.GPIO23=0;  //pullup enabled*/
///////////////// SCI PIN CONFIG END//////////////////////////////////////

///////////////// I2C Pin Config //////////////////////////

        GpioCtrlRegs.GPBGMUX1.bit.GPIO33 = 0;     // presenly configured as gpio in future if u use I2C configure this pins
        GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 0;        // as GPIO
        GpioCtrlRegs.GPBDIR.bit.GPIO33 = 1;         // as digital output
        GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;         //pullup enabled

        GpioCtrlRegs.GPBGMUX1.bit.GPIO32 = 0;     // presenly configured as gpio in future if u use I2C configure this pins
        GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;        // as gpio
        GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;         // as digital output
        GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;         //pullup enabled
        GpioDataRegs.GPBDAT.bit.GPIO32 = 1;         //pullup enabled

////////////////////I2C pin Config end///////////////////////

////////////Gpio pin config///////////////////////////////////
        GpioCtrlRegs.GPHAMSEL.bit.GPIO242 = 0;   // 0 makes gpio
        AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO242 = 1;

        GpioCtrlRegs.GPHGMUX2.bit.GPIO242 = 0;     // presenly configured as gpio
        GpioCtrlRegs.GPHMUX2.bit.GPIO242 = 0;        // as GPIO
        GpioCtrlRegs.GPHDIR.bit.GPIO242 = 1;         // as digital output
        GpioCtrlRegs.GPHPUD.bit.GPIO242 = 0;         //pullup enabled

        GpioCtrlRegs.GPHAMSEL.bit.GPIO227 = 0;   // 0 makes gpio
        AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO227 = 1;

        GpioCtrlRegs.GPHGMUX1.bit.GPIO227 = 0;     // presenly configured as gpio
        GpioCtrlRegs.GPHMUX1.bit.GPIO227 = 0;        // as GPIO
        GpioCtrlRegs.GPHDIR.bit.GPIO227 = 1;         // as digital output
        GpioCtrlRegs.GPHPUD.bit.GPIO227 = 0;         //pullup enabled

        GpioCtrlRegs.GPHAMSEL.bit.GPIO230 = 0;   // 0 makes gpio
        AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO230 = 1;

        GpioCtrlRegs.GPHGMUX1.bit.GPIO230 = 0;     // presenly configured as gpio
        GpioCtrlRegs.GPHMUX1.bit.GPIO230 = 0;        // as GPIO
        GpioCtrlRegs.GPHDIR.bit.GPIO230 = 1;         // as digital output
        GpioCtrlRegs.GPHPUD.bit.GPIO230 = 0;         //pullup enabled

        GpioCtrlRegs.GPAAMSEL.bit.GPIO13 = 0;   // 0 makes gpio
        AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO13 = 1;

        GpioCtrlRegs.GPAGMUX1.bit.GPIO13 = 0;     // presenly configured as gpio
        GpioCtrlRegs.GPAMUX1.bit.GPIO13 = 0;        // as GPIO
        GpioCtrlRegs.GPADIR.bit.GPIO13 = 1;         // as digital output
        GpioCtrlRegs.GPAPUD.bit.GPIO13 = 0;         //pullup enabled

/////////////////buzzer connected to this pin /////////////
        GpioCtrlRegs.GPAAMSEL.bit.GPIO12 = 0;   // 0 makes gpio
        AnalogSubsysRegs.AGPIOCTRLA.bit.GPIO12 = 1;

        GpioCtrlRegs.GPAGMUX1.bit.GPIO12 = 0;     // presenly configured as gpio
        GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;        // as GPIO
       // GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;         // as digital output
        GpioCtrlRegs.GPAPUD.bit.GPIO12 = 1;         //pullup enabled
/////////////////////////// Buzzer end ////////////////////
////////////////////////not connected ////////////////
        ////////////led//////////////
        GpioCtrlRegs.GPAGMUX2.bit.GPIO16 = 0;     // presenly configured as gpio
        GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;        // as GPIO
        GpioCtrlRegs.GPADIR.bit.GPIO16 = 1;         // as digital output
        GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;         //pullup enabled

        GpioCtrlRegs.GPAGMUX2.bit.GPIO24 = 0;     // presenly configured as gpio
        GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;        // as GPIO
        GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;         // as digital output
        GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;         //pullup enabled
        GpioDataRegs.GPADAT.bit.GPIO24=1;


////////////////////////RED LED Connected/////////////////////////////////////


/////////////////////////Red Led config end//////////////////////////////////////
        GpioCtrlRegs.GPHAMSEL.bit.GPIO224 = 0;   // 0 makes gpio
            AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO224 = 1;

            GpioCtrlRegs.GPHGMUX1.bit.GPIO224=0;
            GpioCtrlRegs.GPHMUX1.bit.GPIO224=0; //configure as gpio
            GpioCtrlRegs.GPHPUD.bit.GPIO224=1;  //pullup disabled
            GpioCtrlRegs.GPHDIR.bit.GPIO224=1;   //output

            GpioCtrlRegs.GPHAMSEL.bit.GPIO226 = 0;      // asigned to gpio port
                  AnalogSubsysRegs.AGPIOCTRLH.bit.GPIO226 = 1;

                 GpioCtrlRegs.GPHGMUX1.bit.GPIO226=0;
                  GpioCtrlRegs.GPHMUX1.bit.GPIO226=0;  // configure as EPWM
                  GpioCtrlRegs.GPHPUD.bit.GPIO226=1;  //pullup disabled
                  GpioCtrlRegs.GPHDIR.bit.GPIO226=1;  // output
 ///////////////////////end pin config////////////


        EDIS;
    }



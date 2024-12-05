/*
 * MKsci.c
 *
 *  Created on: 03-Oct-2023
 *      Author: Manoj kumar parupalli
 */

#include <srm/MKsci.h>
#include "F28x_Project.h"

void MKinitsciC(void)
{
              EALLOW;
              ScicRegs.SCICTL1.bit.SWRESET=0;
              ScicRegs.SCICTL1.bit.TXWAKE=1;
              ScicRegs.SCIHBAUD.bit.BAUD=0x0E;
              ScicRegs.SCILBAUD.bit.BAUD=0xA5;
              ScicRegs.SCICCR.bit.SCICHAR=7;
              // ScicRegs.SCICCR.bit.ADDRIDLE_MODE=1;
              ScicRegs.SCIPRI.bit.FREESOFT=2;
              ScicRegs.SCICCR.bit.PARITYENA=0;
              ScicRegs.SCICCR.bit.PARITY=0;
              ScicRegs.SCICCR.bit.STOPBITS=0;
              ScicRegs.SCIRXST.bit.RXWAKE =1;
              ScicRegs.SCICTL1.bit.TXENA=1;
              ScicRegs.SCICTL1.bit.RXENA=1;
              ScicRegs.SCICTL1.bit.SWRESET=1;
              ScicRegs.SCICTL2.bit.RXBKINTENA=1;
              ScicRegs.SCIFFTX.bit.SCIFFENA=1;
              ScicRegs.SCIFFRX.all = 0x0022;
              ScicRegs.SCIFFRX.bit.RXFFIENA=1;
              ScicRegs.SCICTL1.all = 0x0023;
              ScicRegs.SCIFFRX.bit.RXFIFORESET = 1;
              EDIS;
}

void MKinitsciA(void)
{
    EALLOW;
                 SciaRegs.SCICTL1.bit.SWRESET=0;
                 SciaRegs.SCICTL1.bit.TXWAKE=1;
                 SciaRegs.SCICCR.bit.LOOPBKENA=0;
                 SciaRegs.SCIHBAUD.bit.BAUD=0x05;
                 SciaRegs.SCILBAUD.bit.BAUD=0x15;
                 SciaRegs.SCICCR.bit.SCICHAR=7;
              // SciaRegs.SCICCR.bit.ADDRIDLE_MODE=1;
                 SciaRegs.SCIPRI.bit.FREESOFT=2;
                 SciaRegs.SCICCR.bit.PARITYENA=1;
                 SciaRegs.SCICCR.bit.PARITY=1;
                 SciaRegs.SCICCR.bit.STOPBITS=1;
                 SciaRegs.SCIRXST.bit.RXWAKE =1;
                 SciaRegs.SCICTL1.bit.TXENA=1;
                 SciaRegs.SCICTL1.bit.RXENA=1;
                 SciaRegs.SCICTL1.bit.SWRESET=1;
                 SciaRegs.SCICTL2.bit.RXBKINTENA=1;
                 SciaRegs.SCIFFTX.bit.SCIFFENA=1;
                 SciaRegs.SCIFFRX.all = 0x0022;
                 SciaRegs.SCIFFRX.bit.RXFFIENA=1;
                 SciaRegs.SCICTL1.all = 0x0023;
                 SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
              /*   SciaRegs.SCIFFTX.all = 0xE040;
                                      SciaRegs.SCIFFRX.all = 0x2044;
                                      SciaRegs.SCIFFCT.all = 0x0;
                                  SciaRegs.SCICTL1.all = 0x0023;*/
EDIS;
}

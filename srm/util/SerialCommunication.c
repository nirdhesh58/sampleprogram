/*
 * SerialCommunication.c
 *
 * Created on: 03-Oct-2023
 * Author: Manoj Kumar Parupalli
 */

#include "SerialCommunication.h" // Assuming this is the header file name
#include "F28x_Project.h"

// Initializes SCI module C with specific configurations
void InitializeSCIC(void)
{
    EALLOW; // Enable write access to protected registers

    // Reset SCI C, then configure
    ScicRegs.SCICTL1.bit.SWRESET = 0;

    // Basic configuration for baud rate and character length
    ScicRegs.SCIHBAUD.bit.BAUD = 0x0E; // High baud rate portion
    ScicRegs.SCILBAUD.bit.BAUD = 0xA5; // Low baud rate portion
    ScicRegs.SCICCR.bit.SCICHAR = 7;   // 8 data bits

    // Disabling parity bit
    ScicRegs.SCICCR.bit.PARITYENA = 0; // Parity disabled
    ScicRegs.SCICCR.bit.PARITY = 0;    // No parity

    // Configuration for stop bit, TX wake, and priority
    ScicRegs.SCICCR.bit.STOPBITS = 0; // 1 stop bit
    ScicRegs.SCICTL1.bit.TXWAKE = 1;  // Transmit wake-up enabled
    ScicRegs.SCIPRI.bit.FREESOFT = 2; // Continue operation on emulation suspend

    // Enabling receiver, transmitter and receive interrupt
    ScicRegs.SCICTL1.bit.RXENA = 1;
    ScicRegs.SCICTL1.bit.TXENA = 1;
    ScicRegs.SCICTL2.bit.RXBKINTENA = 1;

    // FIFO configuration
    ScicRegs.SCIFFTX.bit.SCIFFENA = 1; // FIFO enhancements are enabled
    ScicRegs.SCIFFRX.all = 0x0022;     // Configuration for the receive FIFO
    ScicRegs.SCIFFRX.bit.RXFFIENA = 1; // Interrupt based on RX FIFO level

    // Re-enable SCI module
    ScicRegs.SCICTL1.bit.SWRESET = 1;

    EDIS; // Disable write access to protected registers
}

// Initializes SCI module A with specific configurations
void InitializeSCIA(void)
{
    EALLOW; // Enable write access to protected registers

    // Reset SCI A, then configure
    SciaRegs.SCICTL1.bit.SWRESET = 0;

    // Basic configuration for baud rate and character length
    SciaRegs.SCIHBAUD.bit.BAUD = 0x05; // High baud rate portion
    SciaRegs.SCILBAUD.bit.BAUD = 0x15; // Low baud rate portion
    SciaRegs.SCICCR.bit.SCICHAR = 7;   // 8 data bits

    // Configuration for parity and stop bits
    SciaRegs.SCICCR.bit.PARITYENA = 1; // Parity enabled
    SciaRegs.SCICCR.bit.PARITY = 1;    // Odd parity
    SciaRegs.SCICCR.bit.STOPBITS = 1;  // 2 stop bits

    // TX wake and priority configuration
    SciaRegs.SCICTL1.bit.TXWAKE = 1;  // Transmit wake-up enabled
    SciaRegs.SCIPRI.bit.FREESOFT = 2; // Continue operation on emulation suspend

    // Enabling receiver, transmitter and receive interrupt
    SciaRegs.SCICTL1.bit.RXENA = 1;
    SciaRegs.SCICTL1.bit.TXENA = 1;
    SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

    // FIFO configuration
    SciaRegs.SCIFFTX.bit.SCIFFENA = 1; // FIFO enhancements are enabled
    SciaRegs.SCIFFRX.all = 0x0022;     // Configuration for the receive FIFO
    SciaRegs.SCIFFRX.bit.RXFFIENA = 1; // Interrupt based on RX FIFO level

    // Re-enable SCI module
    SciaRegs.SCICTL1.bit.SWRESET = 1;

    EDIS; // Disable write access to protected registers
}

/*
 * mkpwm.c
 *
 * created on 29-9-23
 * author Manoj Kumar Parupalli
 *
 *
 *
 *
 *
 */
#include "F28x_Project.h"
#include "MKpwm.h"
#include "Constants.h"
#include "Globals.h"

#define DeadBand  200//100=830ns   400 =3.2us
//#define DeadBand  400
void MKintItPwm1(void)  //H3,L3 gpio4,gpio5
{
    EALLOW;
    EPwm1Regs.TBPRD=PwmPeriod;             //set timer period
    EPwm1Regs.TBPHS.bit.TBPHS=0x0000;      // phase is 0
    EPwm1Regs.TBCTR = 0x0000;              // clear counter

    // Setup Time base clock
    EPwm1Regs.TBCTL.bit.FREE_SOFT=3;
    EPwm1Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
    EPwm1Regs.TBCTL.bit.PHSEN=TB_DISABLE;
    EPwm1Regs.TBCTL.bit.PRDLD=TB_SHADOW;
    //  EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through, Synchronization Output Select,
        EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

        EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
        EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

        // Setup compare
        EPwm1Regs.CMPA.bit.CMPA = 0;
        EPwm1Regs.CMPB.bit.CMPB = 0;

        // Set actions
        EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set PWM1A on CAU
        EPwm1Regs.AQCTLA.bit.ZRO=AQ_SET;   ///AQ_SET
       // EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;            // Clear PWM1A on CAD
        EPwm1Regs.AQCTLB.bit.CBU = AQ_CLEAR;           // Clear PWM1B on CAU
        EPwm1Regs.AQCTLB.bit.ZRO = AQ_SET;             // Set PWM1B on CAD

//        EPwm1Regs.DBCTL.bit.OUT_MODE=3;
//        EPwm1Regs.DBCTL.bit.POLSEL=2;
//        EPwm1Regs.DBFED.bit.DBFED=DeadBand;
//        EPwm1Regs.DBRED.bit.DBRED=DeadBand;

    //    EPwm1Regs.ETSEL.bit.INTEN = 1;
    //    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        //sampling at middle of period : up and down mode: symmetrical mode pwm
    //    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;

        // set up ADC trigger
   /*    EPwm1Regs.ETSEL.bit.SOCAEN   = 1;

       EPwm1Regs.ETSEL.bit.SOCASELCMP=1;
       EPwm1Regs.ETSEL.bit.SOCASEL  = ET_CTRU_CMPA;
       EPwm1Regs.ETPS.bit.SOCAPRD   = ET_1ST;
*/
    // Trip on nTZ3:
       EPwm1Regs.TZSEL.bit.OSHT1 = 1;
       EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;           // EPwm1A will go low
       EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPwm1B will go high
       EPwm1Regs.TZCLR.all = 0xFF;

    //   EPwm1Regs.TZEINT.bit.OST = 1;    // enable intr EPwm1 ISR to BUZZER
       EPwm1Regs.TBCTL.bit.FREE_SOFT = 3;   // free run
       EDIS;
    }

void MKintItPwm4(void)  //H1,L1 Gpio3,gpio2
{
    EALLOW;

    EPwm4Regs.TBPRD=PwmPeriod;             //set timer period
    EPwm4Regs.TBPHS.bit.TBPHS=0x0000;      // phase is 0
    EPwm4Regs.TBCTR = 0x0000;              // clear counter

    // Setup Time base clock
    EPwm4Regs.TBCTL.bit.FREE_SOFT=3;
    EPwm4Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
    EPwm4Regs.TBCTL.bit.PHSEN=TB_DISABLE;
    EPwm4Regs.TBCTL.bit.PRDLD=TB_SHADOW;
    //  EPwm4Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through, Synchronization Output Select,
        EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

        EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
        EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

        // Setup compare
        EPwm4Regs.CMPA.bit.CMPA = 0;
        EPwm4Regs.CMPB.bit.CMPB = 0;

        // Set actions
        EPwm4Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set PWM1A on CAU
        EPwm4Regs.AQCTLA.bit.ZRO=AQ_SET;
       // EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;            // Clear PWM1A on CAD
        EPwm4Regs.AQCTLB.bit.CBU = AQ_CLEAR;           // Clear PWM1B on CAU
        EPwm4Regs.AQCTLB.bit.ZRO = AQ_SET;             // Set PWM1B on CAD

//                       EPwm4Regs.DBCTL.bit.OUT_MODE=3;
//                       EPwm4Regs.DBCTL.bit.POLSEL=2;
//                       EPwm4Regs.DBFED.bit.DBFED=DeadBand;
//                       EPwm4Regs.DBRED.bit.DBRED=DeadBand;

    //    EPwm1Regs.ETSEL.bit.INTEN = 1;
    //    EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        //sampling at middle of period : up and down mode: symmetrical mode pwm
    //    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;
/*
        // set up ADC trigger
       EPwm4Regs.ETSEL.bit.SOCAEN   = 1;
       EPwm4Regs.ETSEL.bit.SOCASELCMP=1;
       EPwm4Regs.ETSEL.bit.SOCASEL  = ET_CTRU_CMPA;
       EPwm4Regs.ETPS.bit.SOCAPRD   = ET_1ST;
*/
    // Trip on nTZ3:
       EPwm4Regs.TZSEL.bit.OSHT4 = 1;
       EPwm4Regs.TZCTL.bit.TZA = TZ_FORCE_LO;           // EPwm1A will go low
       EPwm4Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPwm1B will go high
       EPwm4Regs.TZCLR.all = 0xFF;
    //   EPwm1Regs.TZEINT.bit.OST = 1;    // enable intr EPwm1 ISR to BUZZER
       EPwm4Regs.TBCTL.bit.FREE_SOFT = 3;   // free run
       EDIS;
    }

void MKintItPwm6(void) //H2,L2
{
    EALLOW;

    EPwm6Regs.TBPRD=PwmPeriod;             //set timer period
    EPwm6Regs.TBPHS.bit.TBPHS=0x0000;      // phase is 0
    EPwm6Regs.TBCTR = 0x0000;              // clear counter

    // Setup Time base clock
    EPwm6Regs.TBCTL.bit.FREE_SOFT=3;
    EPwm6Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
    EPwm6Regs.TBCTL.bit.PHSEN=TB_DISABLE;
    EPwm6Regs.TBCTL.bit.PRDLD=TB_SHADOW;
    //  EPwm6Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through, Synchronization Output Select,
        EPwm6Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm6Regs.TBCTL.bit.CLKDIV = TB_DIV1;

        EPwm6Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
        EPwm6Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwm6Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        EPwm6Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

        // Setup compare
        EPwm6Regs.CMPA.bit.CMPA = 0;
        EPwm6Regs.CMPB.bit.CMPB = 0;
        // Set actions
        EPwm6Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set PWM1A on CAU
        EPwm6Regs.AQCTLA.bit.ZRO=AQ_SET;
       // EPwm6Regs.AQCTLA.bit.CAD = AQ_SET;            // Clear PWM1A on CAD
        EPwm6Regs.AQCTLB.bit.CBU = AQ_CLEAR;           // Clear PWM1B on CAU
        EPwm6Regs.AQCTLB.bit.ZRO = AQ_SET;             // Set PWM1B on CAD

//                EPwm6Regs.DBCTL.bit.OUT_MODE=3;
//                EPwm6Regs.DBCTL.bit.POLSEL=2;
//                EPwm6Regs.DBFED.bit.DBFED=DeadBand;
//                EPwm6Regs.DBRED.bit.DBRED=DeadBand;



    //    EPwm6Regs.ETSEL.bit.INTEN = 1;
    //    EPwm6Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        //sampling at middle of period : up and down mode: symmetrical mode pwm
    //    EPwm6Regs.ETPS.bit.INTPRD = ET_1ST;
/*
        // set up ADC trigger
       EPwm6Regs.ETSEL.bit.SOCAEN   = 1;
       EPwm6Regs.ETSEL.bit.SOCASELCMP=1;
       EPwm6Regs.ETSEL.bit.SOCASEL  = ET_CTRU_CMPA;
       EPwm6Regs.ETPS.bit.SOCAPRD   = ET_1ST;
*/
    // Trip on nTZ3:
       EPwm6Regs.TZSEL.bit.OSHT6 = 1;
       EPwm6Regs.TZCTL.bit.TZA = TZ_FORCE_LO;           // EPwm1A will go low
       EPwm6Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPwm1B will go high
       EPwm6Regs.TZCLR.all = 0xFF;
      // EPwm6Regs.TZEINT.bit.OST = 1;    // enable intr EPwm1 ISR to BUZZER
       EPwm6Regs.TBCTL.bit.FREE_SOFT = 3;   // free run
       EDIS;
    }

void MKintItPwm2(void)  //H4,L4 gpio6,gpio7
{
    EALLOW;

    EPwm2Regs.TBPRD=PwmPeriod;             //set timer period
    EPwm2Regs.TBPHS.bit.TBPHS=0x0000;      // phase is 0
    EPwm2Regs.TBCTR = 0x0000;              // clear counter

    // Setup Time base clock
    EPwm2Regs.TBCTL.bit.FREE_SOFT=3;
    EPwm2Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
    EPwm2Regs.TBCTL.bit.PHSEN=TB_DISABLE;
    EPwm2Regs.TBCTL.bit.PRDLD=TB_SHADOW;
    //  EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through, Synchronization Output Select,
        EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

        EPwm2Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
        EPwm2Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

        // Setup compare
        EPwm2Regs.CMPA.bit.CMPA = 0;
        EPwm2Regs.CMPB.bit.CMPB = 0;
        // Set actions
        EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set PWM1A on CAU
        EPwm2Regs.AQCTLA.bit.ZRO=AQ_SET;
       // EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;            // Clear PWM1A on CAD
        EPwm2Regs.AQCTLB.bit.CBU = AQ_CLEAR;           // Clear PWM1B on CAU
        EPwm2Regs.AQCTLB.bit.ZRO = AQ_SET;             // Set PWM1B on CAD

//        EPwm2Regs.DBCTL.bit.OUT_MODE=3;
//        EPwm2Regs.DBCTL.bit.POLSEL=2;
//        EPwm2Regs.DBFED.bit.DBFED=DeadBand;
//        EPwm2Regs.DBRED.bit.DBRED=DeadBand;

    //    EPwm2Regs.ETSEL.bit.INTEN = 1;
    //    EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        //sampling at middle of period : up and down mode: symmetrical mode pwm
    //    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;
/*
        // set up ADC trigger
       EPwm2Regs.ETSEL.bit.SOCAEN   = 1;
       EPwm2Regs.ETSEL.bit.SOCASELCMP=1;
       EPwm2Regs.ETSEL.bit.SOCASEL  = ET_CTRU_CMPA;
       EPwm2Regs.ETPS.bit.SOCAPRD   = ET_1ST;
*/
    // Trip on nTZ3:
       EPwm2Regs.TZSEL.bit.OSHT2 = 1;
       EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;           // EPwm1A will go low
       EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPwm1B will go high
       EPwm2Regs.TZCLR.all = 0xFF;
      //   EPwm2Regs.TZEINT.bit.OST = 1;    // enable intr EPwm1 ISR to BUZZER
       EPwm2Regs.TBCTL.bit.FREE_SOFT = 3;   // free run
       EDIS;
    }

void MKintItPwm3(void)
{
    EALLOW;

    EPwm3Regs.TBPRD=30000;             //set timer period for 1khz
    EPwm3Regs.TBPHS.bit.TBPHS=0x0000;      // phase is 0
    EPwm3Regs.TBCTR = 0x0000;              // clear counter

    // Setup Time base clock
    EPwm3Regs.TBCTL.bit.FREE_SOFT=3;
    EPwm3Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
    EPwm3Regs.TBCTL.bit.PHSEN=TB_DISABLE;
    EPwm3Regs.TBCTL.bit.PRDLD=TB_SHADOW;
    //  EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through, Synchronization Output Select,
        EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV4;

        EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
        EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

        // Setup compare
        EPwm3Regs.CMPA.bit.CMPA = 10000;
        // Set actions
//        EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set PWM1A on CAU
//        EPwm3Regs.AQCTLA.bit.ZRO=AQ_SET;
//       // EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;            // Clear PWM1A on CAD
//        EPwm3Regs.AQCTLB.bit.CAU = AQ_SET;           // Clear PWM1B on CAU
//        EPwm3Regs.AQCTLB.bit.ZRO = AQ_CLEAR;             // Set PWM1B on CAD

   /*     EPwm2Regs.DBCTL.bit.OUT_MODE=3;
        EPwm2Regs.DBCTL.bit.POLSEL=2;
        EPwm2Regs.DBFED.bit.DBFED=400;
        EPwm2Regs.DBRED.bit.DBRED=400;*/

        EPwm3Regs.ETSEL.bit.INTEN = 1;
        EPwm3Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        //sampling at middle of period : up and down mode: symmetrical mode pwm
        EPwm3Regs.ETPS.bit.INTPRD = ET_1ST;

        // set up ADC trigger
    /*   EPwm3Regs.ETSEL.bit.SOCAEN   = 1;
       EPwm3Regs.ETSEL.bit.SOCASELCMP=1;
       EPwm3Regs.ETSEL.bit.SOCASEL  = ET_CTRU_CMPA;
       EPwm3Regs.ETPS.bit.SOCAPRD   = ET_1ST;
       */

    // Trip on nTZ3:
       EPwm3Regs.TZSEL.bit.OSHT3 = 1;
       EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO;           // EPwm1A will go low
       EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPwm1B will go high
       EPwm3Regs.TZCLR.all = 0xFF;
      //   EPwm2Regs.TZEINT.bit.OST = 1;    // enable intr EPwm1 ISR to BUZZER
       EPwm3Regs.TBCTL.bit.FREE_SOFT = 3;   // free run
       EDIS;
    }

void MKintItPwm5(void)
{
    EALLOW;

    EPwm5Regs.TBPRD=4800;             //set timer period for 40khz
    EPwm5Regs.TBPHS.bit.TBPHS=0x0000;      // phase is 0
    EPwm5Regs.TBCTR = 0x0000;              // clear counter

    // Setup Time base clock
    EPwm5Regs.TBCTL.bit.FREE_SOFT=3;
    EPwm5Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
    EPwm5Regs.TBCTL.bit.PHSEN=TB_DISABLE;
    EPwm5Regs.TBCTL.bit.PRDLD=TB_SHADOW;
    //  EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through, Synchronization Output Select,
        EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

        EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
        EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

        // Setup compare
        EPwm5Regs.CMPA.bit.CMPA = 1500;
        // Set actions
      /*  EPwm5Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set PWM1A on CAU
        EPwm5Regs.AQCTLA.bit.ZRO=AQ_SET;
       // EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;            // Clear PWM1A on CAD
        EPwm5Regs.AQCTLB.bit.CAU = AQ_SET;           // Clear PWM1B on CAU
        EPwm5Regs.AQCTLB.bit.ZRO = AQ_CLEAR;             // Set PWM1B on CAD
*/
   /*     EPwm2Regs.DBCTL.bit.OUT_MODE=3;
        EPwm2Regs.DBCTL.bit.POLSEL=2;
        EPwm2Regs.DBFED.bit.DBFED=400;
        EPwm2Regs.DBRED.bit.DBRED=400;*/

        EPwm5Regs.ETSEL.bit.INTEN = 1;
        EPwm5Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        //sampling at middle of period : up and down mode: symmetrical mode pwm
        EPwm5Regs.ETPS.bit.INTPRD = ET_1ST;

        // set up ADC trigger
    /*   EPwm3Regs.ETSEL.bit.SOCAEN   = 1;
       EPwm3Regs.ETSEL.bit.SOCASELCMP=1;
       EPwm3Regs.ETSEL.bit.SOCASEL  = ET_CTRU_CMPA;
       EPwm3Regs.ETPS.bit.SOCAPRD   = ET_1ST;
       */

    // Trip on nTZ3:
       EPwm5Regs.TZSEL.bit.OSHT3 = 1;
       EPwm5Regs.TZCTL.bit.TZA = TZ_FORCE_LO;           // EPwm1A will go low
       EPwm5Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPwm1B will go high
       EPwm5Regs.TZCLR.all = 0xFF;
      //   EPwm2Regs.TZEINT.bit.OST = 1;    // enable intr EPwm1 ISR to BUZZER
       EPwm5Regs.TBCTL.bit.FREE_SOFT = 3;   // free run
       EDIS;
    }

void MKintItPwm7(void)
{
    EALLOW;

    EPwm7Regs.TBPRD=43200;             //set timer period for 2.5khz for buzzer
    EPwm7Regs.TBPHS.bit.TBPHS=0x0000;      // phase is 0
    EPwm7Regs.TBCTR = 0x0000;              // clear counter

    // Setup Time base clock
    EPwm7Regs.TBCTL.bit.FREE_SOFT=3;
    EPwm7Regs.TBCTL.bit.CTRMODE=TB_COUNT_UP;
    EPwm7Regs.TBCTL.bit.PHSEN=TB_DISABLE;
    EPwm7Regs.TBCTL.bit.PRDLD=TB_SHADOW;
    //  EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // sync flow-through, Synchronization Output Select,
        EPwm7Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
        EPwm7Regs.TBCTL.bit.CLKDIV = TB_DIV1;

        EPwm7Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;    // Load registers every ZERO
        EPwm7Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
        EPwm7Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
        EPwm7Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

        // Setup compare
        EPwm7Regs.CMPA.bit.CMPA = 0;
        // Set actions
        EPwm7Regs.AQCTLA.bit.CAU = AQ_CLEAR;             // Set PWM1A on CAU
               EPwm7Regs.AQCTLA.bit.ZRO=AQ_SET;
              // EPwm1Regs.AQCTLA.bit.CAD = AQ_SET;            // Clear PWM1A on CAD
               EPwm7Regs.AQCTLB.bit.CAU = AQ_SET;           // Clear PWM1B on CAU
               EPwm7Regs.AQCTLB.bit.ZRO = AQ_CLEAR;             // Set PWM1B on CAD
//        EPwm7Regs.DBCTL.bit.OUT_MODE=3;
//        EPwm7Regs.DBCTL.bit.POLSEL=2;
//        EPwm7Regs.DBFED.bit.DBFED=DeadBand;
//        EPwm7Regs.DBRED.bit.DBRED=DeadBand;

     /*   EPwm7Regs.ETSEL.bit.INTEN = 1;
        EPwm7Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;        //sampling at middle of period : up and down mode: symmetrical mode pwm
        EPwm7Regs.ETPS.bit.INTPRD = ET_1ST;*/

        // set up ADC trigger
    /*   EPwm3Regs.ETSEL.bit.SOCAEN   = 1;
       EPwm3Regs.ETSEL.bit.SOCASELCMP=1;
       EPwm3Regs.ETSEL.bit.SOCASEL  = ET_CTRU_CMPA;
       EPwm3Regs.ETPS.bit.SOCAPRD   = ET_1ST;
       */

    // Trip on nTZ3:
       EPwm7Regs.TZSEL.bit.OSHT3 = 1;
       EPwm7Regs.TZCTL.bit.TZA = TZ_FORCE_LO;           // EPwm1A will go low
       EPwm7Regs.TZCTL.bit.TZB = TZ_FORCE_LO;           // EPwm1B will go high
       EPwm7Regs.TZCLR.all = 0xFF;
      //   EPwm2Regs.TZEINT.bit.OST = 1;    // enable intr EPwm1 ISR to BUZZER
       EPwm7Regs.TBCTL.bit.FREE_SOFT = 3;   // free run
       EDIS;
    }

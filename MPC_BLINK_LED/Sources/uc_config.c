/*
 * uc_config.c
 *
 *  Created on: Jul 10, 2020
 *      Author: Elton Junior
 */

#include "uc_config.h"

void sys_init_fnc(void)
{
	initModesAndClock();	
	initPeriClkGen();
	disableWatchdog();
	siu_ports_init_fnc();
}


void initModesAndClock(void) {
  ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */
                                  /* Initialize PLL before turning it on: */
/* Use 1 of the next 2 lines depending on crystal frequency: */
  CGM.FMPLL_CR.R = 0x02400100;    /* 8 MHz xtal: Set PLL0 to 64 MHz */  
  ME.RUN[0].R = 0x001F0074;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL */
  ME.RUNPC[1].R = 0x00000010; 	  /* Peri. Cfg. 1 settings: only run in RUN0 mode */
  
  //ME.PCTL[4].R = 0x01;            /* MPC56xxB/P/S DSPI0:  select ME.RUNPC[1] */	
  //ME.PCTL[5].R = 0x01;            /* MPC56xxB/P/S DSPI1:  select ME.RUNPC[1] */	
  //ME.PCTL[32].R = 0x01; 	      /* MPC56xxB/P/S ADC 0: select ME.RUNPC[1] */	
  //ME.PCTL[57].R = 0x01; 	      /* MPC56xxB CTUL: select ME.RUNPC[1] */
  ME.PCTL[68].R = 0x01;           /* MPC56xxB/S SIUL (GPIO):  select ME.RUNPC[0] */	
  //ME.PCTL[72].R = 0x01;           /* MPC56xxB/S EMIOS 0:  select ME.RUNPC[0] */
  //ME.PCTL[92].R = 0x01;           /* PIT, RTI: select ME_RUN_PC[1] */
  	
                                  /* Mode Transition to enter RUN0 mode: */
  ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
  ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
  while (ME.GS.B.S_MTRANS) {}     /* Wait for mode transition to complete */    
                                  /* Note: could wait here using timer and/or I_TC IRQ */
  while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}

void initPeriClkGen(void) {
  CGM.SC_DC0.R =0x80;    
	  /* Peripheral Set 1 Clock Divider Status: Enabled */
	  /* Peripheral Set 1 Clock Divider: 1 */
  CGM.SC_DC1.R =0x80;    
	  /* Peripheral Set 2 Clock Divider Status: Enabled */
	  /* Peripheral Set 2 Clock Divider: 1 */
  CGM.SC_DC2.R =0x80;    
	  /* Peripheral Set 3 Clock Divider Status: Enabled */
	  /* Peripheral Set 3 Clock Divider: 1 */
}

void disableWatchdog(void) {
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}  

/* ----------------------------------------------------------- */
/*                 SIU PORT E PAD Configuration                 */
/* ----------------------------------------------------------- */
void siu_ports_init_fnc(void)
{
	SIU.PCR[68].R = 0x0200;				/* Program the drive enable pin of LED1 (PE4) as output*/
	SIU.PCR[69].R = 0x0200;				/* Program the drive enable pin of LED2 (PE5) as output*/
	SIU.PCR[70].R = 0x0200;				/* Program the drive enable pin of LED3 (PE6) as output*/
	SIU.PCR[71].R = 0x0200;				/* Program the drive enable pin of LED4 (PE7) as output*/
}

/******************************************************************************
*   Function: GPIO_GetState
*
*   Description: Get state for an GPIO pin
*
******************************************************************************/
uint8_t GPIO_GetState (uint16_t ch)
{
    uint8_t result;

    result = (uint8_t)SIU.GPDI[ch].B.PDI;

    return(result);
}

/******************************************************************************
*   Function: GPIO_SetState
*
*   Description: Set state for an GPIO pin
*
******************************************************************************/
void GPIO_SetState (uint16_t ch, uint8_t value)
{
    SIU.GPDO[ch].B.PDO = value;
}

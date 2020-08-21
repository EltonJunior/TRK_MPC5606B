/*
 * main.c
 *
 *  Created on: Jul 10, 2020
 *      Author: Elton Junior
 */

#include "MPC5606B.h"
#include "uc_config.h"


int main(void) {
  volatile int i = 0, j = 0;

  /* ----------------------------------------------------------- */
  /*	             System Initialization Function              */
  /* ----------------------------------------------------------- */
     sys_init_fnc();

  /* Turn off LEDs */  
  GPIO_SetState(68, 1);
  GPIO_SetState(69, 1);
  GPIO_SetState(70, 1);
  GPIO_SetState(71, 1);
  
  while(1)
  {		
		GPIO_SetState(68, 0);
		GPIO_SetState(69, 0);
		GPIO_SetState(70, 0);
		GPIO_SetState(71, 0);
		for(i=0;i<250;i++){for(j=0;j<20000;j++){}}
		
		
		GPIO_SetState(68, 1);
		GPIO_SetState(69, 1);
		GPIO_SetState(70, 1);
		GPIO_SetState(71, 1);
		for(i=0;i<250;i++){for(j=0;j<20000;j++){}}
  }
}




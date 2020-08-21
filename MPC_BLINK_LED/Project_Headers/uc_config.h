/*
 * uc_config.h
 *
 *  Created on: Jul 10, 2020
 *      Author: Elton Junior
 */

#ifndef UC_CONFIG_H_
#define UC_CONFIG_H_

#include "typedefs.h"
#include "MPC5606B.h"

void sys_init_fnc(void);

void initModesAndClock(void);	
void initPeriClkGen(void);
void disableWatchdog(void);
void siu_ports_init_fnc(void);

uint8_t GPIO_GetState (uint16_t);			/* return: Current Value of GPIO Pin; paremter: Channel Number */
void GPIO_SetState (uint16_t, uint8_t); /* parameters: Channel Number, Value to set output */ 


#endif /* UC_CONFIG_H_ */

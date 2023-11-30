/*
 * gps.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Hesha
 */

#ifndef HAL_GPS_H_
#define HAL_GPS_H_


#include "std_types.h"

extern uint8 buf[100];
extern volatile uint8 	i,
flag,
stringReceived;

extern uint8 gpgga[];

extern uint8 latitude[12];
extern uint8 logitude[12];

void GPS_init(void);
//
void GPS_aaa(uint8 data);

void GPS_processData(void);

void GPS_readDataStream(void);

void GPS_readPosition(void);

#endif /* HAL_GPS_H_ */

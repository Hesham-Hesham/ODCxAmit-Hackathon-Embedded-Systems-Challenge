/*
 * icu.h
 *
 *  Created on: May 27, 2023
 *      Author: Hesham Hesham
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"


extern  uint16 ICU_CapturedValue;
extern  uint8 ICU_ISR_lastEdge;


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
	ICU_FALLING_EDGE,ICU_RISING_EDGE
}ICU_Edge_Type;

typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_Prescaler;


typedef struct
{
	ICU_Edge_Type edge_type;
	ICU_Prescaler prescaler;

}ICU_ConfigType;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void ICU_init(const ICU_ConfigType *Config_ptr);
void ICU_setCallBack(void(*a_ptr)(void));
void ICU_setEdgeDetectionType(const ICU_Edge_Type edge_type);
uint16 ICU_getInputCaptureValue(void);
void ICU_clearTimer(void);


#endif /* ICU_H_ */

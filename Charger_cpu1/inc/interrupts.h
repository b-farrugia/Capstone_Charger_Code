/*
 * interrupts.h
 *
 *  Created on: 24 Oct 2021
 *      Author: Bryce
 */

#ifndef INC_INTERRUPTS_H_
#define INC_INTERRUPTS_H_

#include "driverlib.h"

__interrupt void itr_sample(void);
__interrupt void itr_adcConversionComplete(void);
uint16_t ModDepth_to_ComparatorRef(float ModDepth);
#endif /* INC_INTERRUPTS_H_ */

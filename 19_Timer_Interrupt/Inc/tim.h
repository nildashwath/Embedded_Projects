/*
 * tim.h
 *
 *  Created on: Dec 14, 2025
 *      Author: sunbeam
 */

#ifndef TIM_H_
#define TIM_H_

void tim2_1hz_init(void);
void tim2_1hz_interrupt(void);

#define SR_UIF		(1U<<0)

#endif /* TIM_H_ */

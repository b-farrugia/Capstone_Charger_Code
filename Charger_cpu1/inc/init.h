#ifndef INC_INIT_H_
#define INC_INIT_H_

#include "device.h"
#include "driverlib.h"

void Init_Peripherals();
void Init_GPIO(void);
void Init_ADC(void);
void Init_PWM_Module(uint32_t, bool);
void GPIO_Config(uint32_t pin, uint32_t cfg, GPIO_Direction dir, uint32_t padCfd, GPIO_QualificationMode qual);

#endif /* INC_INIT_H_ */

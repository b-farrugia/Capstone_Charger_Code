#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#define CONFIG_ADC_SH_TIME 185

/*
 * Sets the falling edge delay on the EPWMs
 * Enter delay in uS
 */
#define CONFIG_PWM_FED_US 2.5

/*
 * Sets the rising edge delay on the EPWMs
 * Enter delay in uS
 */
#define CONFIG_PWM_RED_US CONFIG_PWM_FED_US

/******************************************/
/*--------------DO NOT EDIT---------------*/
/******************************************/

/*
 * Calculated FED based on set uS
 * Delay = FED * (1/200mhz)
 */
#define CONFIG_PWM_FED (uint16_t)(CONFIG_PWM_FED_US * 200)

/*
 * Calculated RED based on set uS
 */
#define CONFIG_PWM_RED (uint16_t)(CONFIG_PWM_RED_US * 200)

/*
 * Sets the PWM frequency
 */
#define CONFIG_EPWM_TBCTR 3333  // 30kHz

#endif

/*
 * interrupts.c
 *
 *  Created on: 24 Oct 2021
 *      Author: Bryce
 */

#include "interrupts.h"

#include "config.h"
#include "device.h"

typedef struct ADC_Measurement_t {
    uint16_t dc_bus_volts;
    uint16_t ac_igbt_temp;
    uint16_t ac_cur_p1;
    uint16_t p1_volts;
    uint16_t p3_volts;
    uint16_t amb_temp;
    uint16_t ac_cur_p2;
    int AC_P1_OC;
    int AC_P2_OC;
    int DAB_IN_OC;
    int DAB_OUT_OC;
    int PWRFAULT;
    int DC_LINK_OV;
    int BATT_OV;
    int HW_FAULT;
} ADC_Measurement_t;

static ADC_Measurement_t meas = {0};

__interrupt void itr_adcConversionComplete(void) {
    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);

    meas.dc_bus_volts = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
    meas.ac_igbt_temp = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);
    meas.ac_cur_p1 = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);
    meas.p1_volts = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER0);
    meas.p3_volts = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1);
    meas.amb_temp = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER2);
    meas.ac_cur_p2 = ADC_readResult(ADCDRESULT_BASE, ADC_SOC_NUMBER0);
    meas.AC_P1_OC = GPIO_readPin(DEVICE_GPIO_PIN_AC_P1_OC);
    meas.AC_P2_OC = GPIO_readPin(DEVICE_GPIO_PIN_AC_P2_OC);
    meas.DAB_IN_OC = GPIO_readPin(DEVICE_GPIO_PIN_DABIN_OC);
    meas.DAB_OUT_OC = GPIO_readPin(DEVICE_GPIO_PIN_DABO_OC);
    meas.PWRFAULT = GPIO_readPin(DEVICE_GPIO_PIN_P1H_FAULT);
    meas.DC_LINK_OV = GPIO_readPin(DEVICE_GPIO_PIN_DC_LINK_OV);
    meas.BATT_OV = GPIO_readPin(DEVICE_GPIO_PIN_BATT_OV);
    meas.HW_FAULT = GPIO_readPin(DEVICE_GPIO_PIN_HW_FLT);
    GPIO_writePin(DEVICE_GPIO_PIN_MCU_FLT, 1);

    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, ModDepth_to_ComparatorRef(0.25));
    EPWM_setCounterCompareValue(EPWM2_BASE, EPWM_COUNTER_COMPARE_A, ModDepth_to_ComparatorRef(0.25));
    EPWM_setCounterCompareValue(EPWM3_BASE, EPWM_COUNTER_COMPARE_A, ModDepth_to_ComparatorRef(0));
}

__interrupt void itr_sample(void) {
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

// Convert Modulation depth value to Comparator reference value
uint16_t ModDepth_to_ComparatorRef(float ModDepth) {
    return (uint16_t)((CONFIG_EPWM_TBCTR / 2) + (-(CONFIG_EPWM_TBCTR / 2) * ModDepth));
}

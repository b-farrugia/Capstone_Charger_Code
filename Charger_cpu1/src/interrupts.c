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
    int HW_FAULT;
    int P1H_fault;
    int P1L_fault;
    int P2H_fault;
    int P2L_fault;
    int P3H_fault;
    int P3L_fault;
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
    meas.HW_FAULT = GPIO_readPin(DEVICE_GPIO_PIN_HW_FLT);
    meas.P1H_fault = GPIO_readPin(DEVICE_GPIO_PIN_P1H_FAULT);
    meas.P1L_fault = GPIO_readPin(DEVICE_GPIO_PIN_P1L_FAULT);
    meas.P2H_fault = GPIO_readPin(DEVICE_GPIO_PIN_P2H_FAULT);
    meas.P2L_fault = GPIO_readPin(DEVICE_GPIO_PIN_P2L_FAULT);
    meas.P3H_fault = GPIO_readPin(DEVICE_GPIO_PIN_P3H_FAULT);
    meas.P3L_fault = GPIO_readPin(DEVICE_GPIO_PIN_P3L_FAULT);

    //    if (DEVICE_GPIO_PIN_HW_FLT_RESET == 0) {
    //        GPIO_writePin(DEVICE_GPIO_PIN_HW_FLT_RESET, 1);
    //        DEVICE_DELAY_US(1000000);
    //    } else {
    //        GPIO_writePin(DEVICE_GPIO_PIN_HW_FLT_RESET, 0);
    //        DEVICE_DELAY_US(1000000);
    //    }

    EPWM_setCounterCompareValue(EPWM1_BASE, EPWM_COUNTER_COMPARE_A, ModDepth_to_ComparatorRef(0.25));
    EPWM_setCounterCompareValue(EPWM2_BASE, EPWM_COUNTER_COMPARE_A, ModDepth_to_ComparatorRef(0.25));
    EPWM_setCounterCompareValue(EPWM3_BASE, EPWM_COUNTER_COMPARE_A, ModDepth_to_ComparatorRef(0.25));
}

__interrupt void itr_sample(void) {
    EPWM_clearEventTriggerInterruptFlag(EPWM1_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

// Convert Modulation depth value to Comparator reference value
uint16_t ModDepth_to_ComparatorRef(float ModDepth) {
    return (uint16_t)((CONFIG_EPWM_TBCTR / 2) + (-(CONFIG_EPWM_TBCTR / 2) * ModDepth));
}

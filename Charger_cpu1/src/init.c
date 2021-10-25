#include "init.h"

#include "config.h"
#include "interrupts.h"

void Init_Peripherals() {
    Interrupt_register(INT_EPWM1, &itr_sample);
    Interrupt_register(INT_ADCC1, &itr_adcConversionComplete);

    Init_GPIO();

    Init_ADC();

    Init_PWM_Module(EPWM1_BASE, true);
    Init_PWM_Module(EPWM2_BASE, false);
    Init_PWM_Module(EPWM3_BASE, false);

    GPIO_writePin(DEVICE_GPIO_PIN_HW_FLT_RESET, 1);
    DEVICE_DELAY_US(1000000);
    GPIO_writePin(DEVICE_GPIO_PIN_HW_FLT_RESET, 0);
    GPIO_writePin(DEVICE_GPIO_PIN_AR_EN, 1);

    Interrupt_enable(INT_EPWM1);
    Interrupt_enable(INT_ADCC1);

    // ENABLE ITRS
    EINT;
    ERTM;

    // Configure GPIO EPWM

    GPIO_Config(DEVICE_GPIO_PIN_AR_PWM_P1H, DEVICE_GPIO_CFG_AR_PWM_P1H, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_AR_PWM_P1L, DEVICE_GPIO_CFG_AR_PWM_P1L, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    GPIO_Config(DEVICE_GPIO_PIN_AR_PWM_P2H, DEVICE_GPIO_CFG_AR_PWM_P2H, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_AR_PWM_P2L, DEVICE_GPIO_CFG_AR_PWM_P2L, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    GPIO_Config(DEVICE_GPIO_PIN_AR_PWM_P3H, DEVICE_GPIO_CFG_AR_PWM_P3H, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_AR_PWM_P3L, DEVICE_GPIO_CFG_AR_PWM_P3L, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    DEVICE_DELAY_US(10000);

    EPWM_enableADCTrigger(EPWM1_BASE, EPWM_SOC_A);
}

void Init_GPIO() {
    // CAN-A
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANRXA);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_CANTXA);

    // GPIO assignment for Relays
    GPIO_Config(DEVICE_GPIO_PIN_P1RELAY, DEVICE_GPIO_CFG_P1RELAY, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_P2RELAY, DEVICE_GPIO_CFG_P2RELAY, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_P3RELAY, DEVICE_GPIO_CFG_P3RELAY, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_PRECHARGE, DEVICE_GPIO_CFG_PRECHARGE, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    // OUTPUT Relay Enable Pins
    GPIO_Config(DEVICE_GPIO_PIN_AIRP, DEVICE_GPIO_CFG_AIRP, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_AIRN, DEVICE_GPIO_CFG_AIRN, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    // GPIO assignment for Hardware Faults

    // MCU Fault
    GPIO_Config(DEVICE_GPIO_PIN_MCU_FLT, DEVICE_GPIO_CFG_MCU_FLT, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    // Hardware Fault
    GPIO_Config(DEVICE_GPIO_PIN_HW_FLT, DEVICE_GPIO_CFG_HW_FLT, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    // Hardware Fault Reset
    GPIO_Config(DEVICE_GPIO_PIN_HW_FLT_RESET, DEVICE_GPIO_CFG_HW_FLT_RESET, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    // AC Over Current
    GPIO_Config(DEVICE_GPIO_PIN_AC_P1_OC, DEVICE_GPIO_CFG_AC_P1_OC, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_AC_P2_OC, DEVICE_GPIO_CFG_AC_P2_OC, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    // DC Over Current
    GPIO_Config(DEVICE_GPIO_PIN_DABO_OC, DEVICE_GPIO_CFG_DABO_OC, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_DABIN_OC, DEVICE_GPIO_CFG_DABIN_OC, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    // DC Over Voltage
    GPIO_Config(DEVICE_GPIO_PIN_DC_LINK_OV, DEVICE_GPIO_CFG_DC_LINK_OV, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_BATT_OV, DEVICE_GPIO_CFG_BATT_OV, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);

    // Active Rectifier Gate Faults

    // P1
    GPIO_Config(DEVICE_GPIO_PIN_P1H_FAULT, DEVICE_GPIO_CFG_P1H_FAULT, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_P1L_FAULT, DEVICE_GPIO_CFG_P1L_FAULT, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    // P2
    GPIO_Config(DEVICE_GPIO_PIN_P1H_FAULT, DEVICE_GPIO_CFG_P2H_FAULT, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_P1L_FAULT, DEVICE_GPIO_CFG_P2L_FAULT, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    // P3
    GPIO_Config(DEVICE_GPIO_PIN_P3H_FAULT, DEVICE_GPIO_CFG_P3H_FAULT, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);
    GPIO_Config(DEVICE_GPIO_PIN_P3L_FAULT, DEVICE_GPIO_CFG_P3L_FAULT, GPIO_DIR_MODE_IN, GPIO_PIN_TYPE_STD,
                GPIO_QUAL_ASYNC);

    // AR Enable Pin
    GPIO_Config(DEVICE_GPIO_PIN_AR_EN, DEVICE_GPIO_CFG_AR_EN, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);
}

void Init_ADC() {
    /*
     * ADC  SOC     CH      COMMENT
     * A    0       4       DC_BUS_VOLT
     * A    1       1       AR_IGBT_TEMP
     *
     * B    0       3       AC_CUR_P1
     *
     * C    0       4       P1_VOLT
     * C    1       2       P3_VOLT
     * C    2       3       AMB_TEMP
     *
     * D    0       4       AC_CUR_P2
     *
     */

    // ADC A

    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN4, CONFIG_ADC_SH_TIME);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN1, CONFIG_ADC_SH_TIME);

    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(1000);

    // ADC B

    ADC_setPrescaler(ADCB_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCB_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    ADC_setupSOC(ADCB_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN3, CONFIG_ADC_SH_TIME);

    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(ADCB_BASE);
    DEVICE_DELAY_US(1000);

    // ADC C

    ADC_setPrescaler(ADCC_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCC_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN4, CONFIG_ADC_SH_TIME);
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN2, CONFIG_ADC_SH_TIME);
    ADC_setupSOC(ADCC_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN3, CONFIG_ADC_SH_TIME);

    //
    // Set SOC0 to set the interrupt 1 flag. Enable the interrupt and make
    // sure its flag is cleared.
    //
    ADC_setInterruptSource(ADCC_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER2);
    ADC_enableInterrupt(ADCC_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(ADCC_BASE, ADC_INT_NUMBER1);

    //
    // Set pulse positions to late
    //
    ADC_setInterruptPulseMode(ADCC_BASE, ADC_PULSE_END_OF_CONV);

    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(ADCC_BASE);
    DEVICE_DELAY_US(1000);

    // ADC D

    ADC_setPrescaler(ADCD_BASE, ADC_CLK_DIV_4_0);
    ADC_setMode(ADCD_BASE, ADC_RESOLUTION_12BIT, ADC_MODE_SINGLE_ENDED);

    ADC_setupSOC(ADCD_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_EPWM1_SOCA, ADC_CH_ADCIN4, CONFIG_ADC_SH_TIME);

    //
    // Power up the ADC and then delay for 1 ms
    //
    ADC_enableConverter(ADCD_BASE);
    DEVICE_DELAY_US(1000);
}

void Init_PWM_Module(uint32_t base, bool master) {
    //   TBCLK = EPWMCLK/(highSpeedPrescaler * pre-scaler)
    //
    //   Note: EPWMCLK is a scaled version of SYSCLK. At reset EPWMCLK is half
    //          SYSCLK.

    // TBCLK = 200Mhz

    SysCtl_setEPWMClockDivider(SYSCTL_EPWMCLK_DIV_1);

    // Set the time-base clock (TBCLK) relative to the ePWM clock (EPWMCLK)
    EPWM_setClockPrescaler(base, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    // EPWM_selectPeriodLoadEvent(base, EPWM_SHADOW_LOAD_MODE_COUNTER_ZERO);

    // TPWM = 1/(FPWM)
    // TPWM = 2 x TBPRD x TTBCLK

    // Configure the PWM time-base counter (TBCTR) frequency or period.
    EPWM_setTimeBasePeriod(base, CONFIG_EPWM_TBCTR);  // 30kHz @ 200Mhz EPWMCLK

    // Set to UP-DOWN counter mode for symmetrical PWM
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP_DOWN);

    EPWM_setTimeBaseCounter(base, 0U);

    // Configure the time-base phase relative to another ePWM module
    EPWM_setPhaseShift(base, 0);
    EPWM_disablePhaseShiftLoad(base);

    // Determine what happens when an emulator stops
    EPWM_setEmulationMode(base, EPWM_EMULATION_STOP_AFTER_FULL_CYCLE);

    // Configure AQ. Active High
    EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);
    EPWM_setActionQualifierAction(base, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    // Counter compare for Duty cycle
    EPWM_setCounterCompareShadowLoadMode(base, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);

    //
    // Configure the Deadband module
    //
    EPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
    EPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);

    // Set the RED and FED values
    EPWM_setFallingEdgeDelayCount(base, CONFIG_PWM_FED);
    EPWM_setRisingEdgeDelayCount(base, CONFIG_PWM_RED);

    // Set the Deadband module to create complementary Active High signals
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    EPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);

    // Use the delayed signals instead of the original signals
    EPWM_setDeadBandDelayMode(base, EPWM_DB_RED, true);
    EPWM_setDeadBandDelayMode(base, EPWM_DB_FED, true);

    // DO NOT Switch Output A with Output B
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_A, false);
    EPWM_setDeadBandOutputSwapMode(base, EPWM_DB_OUTPUT_B, false);

    //
    // Enable trip zone 1 & 2 - POWERFAULT and HW overcurrent
    //
    //    EPWM_enableTripZoneSignals(
    //        base, (EPWM_TZ_SIGNAL_OSHT1 | EPWM_TZ_SIGNAL_OSHT2 | EPWM_TZ_SIGNAL_DCAEVT1 | EPWM_TZ_SIGNAL_DCBEVT1));
    //    EPWM_setTripZoneAction(base, EPWM_TZ_ACTION_EVENT_TZA, EPWM_TZ_ACTION_LOW);
    //    EPWM_enableTripZoneInterrupt(base, EPWM_TZ_INTERRUPT_OST);

    if (master) {
        //
        // Configure the Zero and Period Interrupt
        //
        EPWM_setInterruptSource(base, EPWM_INT_TBCTR_ZERO_OR_PERIOD);
        EPWM_setInterruptEventCount(base, 1);

        //
        // Configure ADC trigger on zero or period
        //
        EPWM_disableADCTrigger(base, EPWM_SOC_A);
        EPWM_setADCTriggerSource(base, EPWM_SOC_A, EPWM_SOC_TBCTR_ZERO_OR_PERIOD);
        EPWM_setADCTriggerEventPrescale(base, EPWM_SOC_A, 1);

        //
        // Enabled EPWM interrupts
        //
        EPWM_enableInterrupt(base);
    }

    //    EPWM_forceTripZoneEvent(base, EPWM_TZ_FORCE_EVENT_DCAEVT1);

    //
    // Trigger event when DCBH is high
    //
    //    EPWM_setTripZoneDigitalCompareEventCondition(base, EPWM_TZ_DC_OUTPUT_B1, EPWM_TZ_EVENT_DCXH_HIGH);

    //
    // Configure DCBH to use TRIP4 as an input
    //
    //    EPWM_enableDigitalCompareTripCombinationInput(
    //        base, EPWM_DC_COMBINATIONAL_TRIPIN4 | EPWM_DC_COMBINATIONAL_TRIPIN5 | EPWM_DC_COMBINATIONAL_TRIPIN7,
    //        EPWM_DC_TYPE_DCBH);
}

void GPIO_Config(uint32_t pin, uint32_t cfg, GPIO_Direction dir, uint32_t padCfd, GPIO_QualificationMode qual) {
    // Fault pin setup
    GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
    GPIO_setPinConfig(cfg);
    GPIO_setDirectionMode(pin, dir);
    GPIO_setPadConfig(pin, padCfd);
    GPIO_setQualificationMode(pin, qual);
}

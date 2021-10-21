//#############################################################################
//
// FILE:   empty_driverlib_main_cpu1.c
//
// TITLE:  Empty Project
//
// CPU1 Empty Project Example
//
// This example is an empty project setup for Driverlib development for CPU1.
//
//#############################################################################
// $TI Release: F2837xD Support Library v3.12.00.00 $
// $Release Date: Fri Feb 12 19:03:23 IST 2021 $
// $Copyright:
// Copyright (C) 2013-2021 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"

//
// Main
//



void GPIO_Config(uint32_t pin, uint32_t cfg, GPIO_Direction dir, uint32_t padCfd, GPIO_QualificationMode qual)
{
    // Fault pin setup
    GPIO_setMasterCore(pin, GPIO_CORE_CPU1);
    GPIO_setPinConfig(cfg);
    GPIO_setDirectionMode(pin, dir);
    GPIO_setPadConfig(pin, padCfd);
    GPIO_setQualificationMode(pin, qual);
}


void main(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();

    GPIO_Config(88, GPIO_88_GPIO88, GPIO_DIR_MODE_OUT, GPIO_PIN_TYPE_STD, GPIO_QUAL_ASYNC);


    // ENABLE ITRS
    EINT;
    ERTM;

    while(1) {
        GPIO_writePin(88, 1);
        DEVICE_DELAY_US(1000000);
        GPIO_writePin(88, 0);
        DEVICE_DELAY_US(1000000);
    }

}

//
// End of File
//

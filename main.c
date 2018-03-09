#include <stdint.h>
#include <stdio.h>
#include "nrf52.h"
#include "core_cm4.h"
#include "nrf52832_peripherals.h"
#include "interrupts.h"
#include "configuration.h"
//#include "nrf_drv_pdm.h"
#include "SEGGER_RTT.h"  
#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "sdk_config.h"

//#define NRF_LOG_ENABLED 1
//#define NRF_LOG_LEVEL NRF_LOG_LEVEL_DEBUG
int main(){
	gpio_init();
	rtc_init();
	pdm_init();
	SEGGER_RTT_printf(0,"Program starts!\n");
	//uint32_t err;
	//err=NRF_LOG_INIT(NULL);
	//NRF_LOG_DEBUG("Program started\n");
	pdm_start();
	while(1){
		//led_toggle();
		//int i;
		//for(i=0; i<200000; i++);
	}
}


#include "nrf_gpio.h"
#include "nrf.h"
#include "interrupts.h"
#include "configuration.h"

void RTC0_IRQHandler(){
	if (NRF_RTC0->EVENTS_COMPARE[0] != 0){
		NRF_RTC0->EVENTS_COMPARE[0] = 0;
		led_toggle();
	}
}

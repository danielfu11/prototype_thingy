#include "nrf_gpio.h"
#include "nrf.h"
#include "nrf_clock.h"
#include "configuration.h"

void gpio_init(){
	nrf_gpio_cfg_output(2), // P0.02
	nrf_gpio_cfg_sense_input(11, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW); // button 
}

void led_toggle(){
	nrf_gpio_pin_toggle(2);
	//nrf_gpio_pin_set(2);
}

void rtc_init(){ // rtc uses LFCLK which is the lowest power consuming clock
	nrf_clock_lf_src_set(NRF_CLOCK_LF_SRC_RC);
	nrf_clock_task_trigger(NRF_CLOCK_TASK_LFCLKSTART);
	NRF_RTC0->PRESCALER = 0;
	NRF_RTC0->CC[0] = 32768; // 30 seconds 983040
	NRF_RTC0->INTENCLR |= 0xFFFFFFFF; // clear all interrupts
	NRF_RTC0->INTENSET |= RTC_INTENSET_COMPARE0_Set << RTC_INTENSET_COMPARE0_Pos; // enable interrupt
	NRF_RTC0->EVTENSET |= RTC_EVTENSET_COMPARE0_Set << RTC_EVTENSET_COMPARE0_Pos;
	NRF_RTC0->EVENTS_COMPARE[0] = 0;
	NRF_RTC0->TASKS_START = 1;
	NVIC_ClearPendingIRQ(RTC0_IRQn);
	NVIC_EnableIRQ(RTC0_IRQn);
}

#include "nrf_gpio.h"
#include "nrf.h"
#include "nrf_clock.h"
#include "configuration.h"

#define RAM_ADDRESS 0x20000000;

void gpio_init(){
	nrf_gpio_cfg_output(2), // P0.02
	nrf_gpio_cfg_sense_input(11, NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW); // button 
}

void rtc_init(){ // rtc uses LFCLK which is the lowest power consuming clock
	nrf_clock_lf_src_set(NRF_CLOCK_LFCLK_RC);
	nrf_clock_task_trigger(NRF_CLOCK_TASK_LFCLKSTART);
	NRF_RTC0->PRESCALER = 0;
	NRF_RTC0->CC[0] = 65536; // 30 seconds 983040
	NRF_RTC0->INTENCLR |= 0xFFFFFFFF; // clear all interrupts
	NRF_RTC0->INTENSET |= RTC_INTENSET_COMPARE0_Set << RTC_INTENSET_COMPARE0_Pos; // enable interrupt
	NRF_RTC0->EVTENSET |= RTC_EVTENSET_COMPARE0_Set << RTC_EVTENSET_COMPARE0_Pos;
	NRF_RTC0->EVENTS_COMPARE[0] = 0;
	NRF_RTC0->TASKS_START = 1;
	NVIC_ClearPendingIRQ(RTC0_IRQn);
	NVIC_EnableIRQ(RTC0_IRQn);
}

void pdm_init(){
	volatile int16_t * pdm_buffer = (volatile int16_t*)RAM_ADDRESS;
	// pin configuration
	nrf_gpio_cfg_output(26); // CLK pin
  nrf_gpio_pin_clear(26);
  nrf_gpio_cfg_input(25, NRF_GPIO_PIN_PULLDOWN); // DATA pin
  nrf_pdm_psel_connect(26, 25);
	// pdm configuration
	nrf_pdm_clock_set(NRF_PDM_FREQ_1032K);
	nrf_pdm_mode_set(NRF_PDM_MODE_MONO, NRF_PDM_EDGE_LEFTFALLING);
	nrf_pdm_buffer_set((uint32_t *)pdm_buffer, 256);
	//nrf_pdm_gain_set();
	nrf_pdm_int_enable(NRF_PDM_INT_STARTED | NRF_PDM_INT_END | NRF_PDM_INT_STOPPED);
	NVIC_ClearPendingIRQ(PDM_IRQn);
	NVIC_EnableIRQ(PDM_IRQn);
}

void pdm_uninit(){
	nrf_pdm_disable();
	nrf_pdm_psel_disconnect();
}

void pdm_start(){
	nrf_pdm_enable();
	nrf_pdm_event_clear(NRF_PDM_EVENT_STARTED);
  nrf_pdm_task_trigger(NRF_PDM_TASK_START);
}


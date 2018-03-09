#include "nrf_gpio.h"
#include "nrf_pdm.h"
#include "nrf.h"
#include "SEGGER_RTT.h"
#include "interrupts.h"
#include "nrf_log.h"

volatile uint8_t count = 0x0;

void led_toggle(){
	nrf_gpio_pin_toggle(2);
}


void RTC0_IRQHandler(){
	if (NRF_RTC0->EVENTS_COMPARE[0] != 0){
		count++;
		SEGGER_RTT_printf(0, "%x \n", count);
		//NRF_LOG_DEBUG("Time: %d\n",count);
		led_toggle();
		NRF_RTC0->EVENTS_COMPARE[0] = 0;
		NRF_RTC0->TASKS_CLEAR = 1;
	}
}

void PDM_IRQHandler(void)
{
    if (nrf_pdm_event_check(NRF_PDM_EVENT_END))
    {
        nrf_pdm_event_clear(NRF_PDM_EVENT_END);
				
    }
    else if (nrf_pdm_event_check(NRF_PDM_EVENT_STARTED))
    {
        nrf_pdm_event_clear(NRF_PDM_EVENT_STARTED);
    }
    else if (nrf_pdm_event_check(NRF_PDM_EVENT_STOPPED))
    {
        nrf_pdm_event_clear(NRF_PDM_EVENT_STOPPED);
        nrf_pdm_disable();
    }
}


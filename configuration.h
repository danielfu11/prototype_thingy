#ifndef CONFIGURATION_H__
#define CONFIGURATION_H__

#include "nrf_gpio.h"
#include "nrf_clock.h"
#include "nrf_pdm.h"
#include "nrf.h"

void gpio_init(void);

void rtc_init(void);

void pdm_init(void);

void pdm_uninit(void);

void pdm_start(void);
#endif /* CONFIGURATION_H__ */


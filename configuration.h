#ifndef CONFIGURATION_H__
#define CONFIGURATION_H__

#include "nrf_gpio.h"
#include "nrf_clock.h"
#include "nrf.h"

void gpio_init(void);

void led_toggle(void);

void rtc_init(void);

#endif /* CONFIGURATION_H__ */


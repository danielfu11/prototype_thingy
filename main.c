#include <stdint.h>
#include <stdio.h>
#include "nrf52.h"
#include "configuration.h"
#include "nrf52832_peripherals.h"
#include "interrupts.h"

int main(){
	gpio_init();
	rtc_init();
	
	while(1){
		//led_toggle();
		//int i;
		//for(i=0; i<200000; i++);
	}
}


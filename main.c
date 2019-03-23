//Librerias Necesarias
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

volatile int clk;

int main(void) {
	SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ | SYSCTL_SYSDIV_19 | SYSCTL_USE_PLL);
	while(1){
	clk = SysCtlClockGet();
	}
	}

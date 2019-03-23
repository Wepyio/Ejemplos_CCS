#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/adc.h"
#include "driverlib/interrupt.h"

//si 493.88, la 440, sol 392, fa 349.23, mi 329.63, re 293.66, do 261.63
short sw = 0;
uint8_t i;
uint8_t cont = 0;
uint32_t frecuencia[1] = {440};

void ConfLed(){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
}

void ConfPush(){
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	// Desbloquear PF0
	GPIO_PORTF_CR_R = 0x0f;
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

void ConfOut(){
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7);
}

int main(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	ConfLed();
	ConfPush();
	ConfOut();
	while(1){
		sw = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
		if(sw == 16 && cont < 14){
			cont += 2;
			SysCtlDelay(SysCtlClockGet()/30);
		}else if(sw == 16 && cont == 14){
			cont = 0;
			SysCtlDelay(SysCtlClockGet()/30);
		}else if(sw == 1){
			for(i = 0; i <= 100; i++){
 				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 128);
				SysCtlDelay(SysCtlClockGet()/(frecuencia[0]*6));
				GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);
				SysCtlDelay(SysCtlClockGet()/(frecuencia[0]*6));
			}
		}
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, cont);
	}
}

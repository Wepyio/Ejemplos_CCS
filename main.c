#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

volatile short sw;
short flag = 0;
uint32_t T = 1333333;
uint32_t F = 1;
uint32_t S;

int main(void){
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	// Desbloquear PF0
	GPIO_PORTF_CR_R = 0x0f;
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	
	S = (SysCtlClockGet()/12);

	while (1) {
		sw = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
		//if(sw == 16 && T > 3){
		//	T = T - 3;
		//}else if(sw == 1 && T < (SysCtlClockGet()/9)){
		//	T = T + 3;
		//}

		if(sw == 1 && F > 1){
			F = F - 1;
		}else if(sw == 16 && F < (SysCtlClockGet()/12)){
			F = F + 1;
		}

		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
		//SysCtlDelay(T/3);
		SysCtlDelay(S/F);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
		//SysCtlDelay(T/3);
		SysCtlDelay(S/F);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
		//SysCtlDelay(T/3);
		SysCtlDelay(S/F);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 12);
		//SysCtlDelay(T/3);
		SysCtlDelay(S/F);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
		//SysCtlDelay(T/3);
		SysCtlDelay(S/F);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 10);
		//SysCtlDelay(T/3);
		SysCtlDelay(S/F);

	}
}

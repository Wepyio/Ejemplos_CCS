#include "driverlib/interrupt.h"

short azul = 1;
short led = 0;
volatile short push;
int i = 8;
long b1,b3,b5, s, xor;

void ledi(void){
	s = s&0xFF;
	b1 = (s&0x02)>>1;
	b3 = (s&0x08)>>3;
	b5 = (s&0x32)>>5;
	xor = b1^b3^b5;
	s = s>>1;
	xor = xor<<7;
	s = s|xor;
	led = (b1<<1)|(b3<<2)|(b5<<3);
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, led);
}

int main(void){
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;	// Desbloquear PF0
	GPIO_PORTF_CR_R = 0x0f;

	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, 112000000 );  //(500 + 100 (9))ms
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	TimerEnable(TIMER0_BASE, TIMER_A);
	IntMasterEnable();

	IntPrioritySet(INT_TIMER0A, 0);

	while(1){
		push = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
		if(push == 16){
			i = 0;
			while(i < 8){//4 pulsos iniciales
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, 8*azul);
				SysCtlDelay(1666667);
				azul = azul^1;
				i++;
			}
			IntEnable(INT_TIMER0A);
			s = TimerValueGet(TIMER0_BASE, TIMER_A);
			}
	}}

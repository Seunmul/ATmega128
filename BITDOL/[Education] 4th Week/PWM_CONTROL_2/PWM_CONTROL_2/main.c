/*
 * PWM_CONTROL_2.c
 *
 * Created: 2022-01-28 오후 5:09:05
 * Author : Geonha
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int x;
void INIT_PORT(void) // PORT 초기화
{
	DDRB = 0xff; //PWM 출력
	PORTB = 0xff;
	
	DDRC = 0xff; // LED 출력
	PORTC = 0xff;
}

void INIT_TIMER0(void) // TIMER0 초기화
{
	TCCR0 = 
	((1<<WGM00)|(0<<WGM01)|(1<<COM01)|(0<<COM00) // Phase Correct PWM(1/0) up1 down0
	|(0<<CS02)|(1<<CS01)|(1<<CS00)); // 32 분주 (
	
	TCNT0= 0x00; // 카운터 = 256
	TIMSK= 0x01; // TIMER0 인터럽트 enable
}

ISR(TIMER0_OVF_vect) //타이머 인터럽트 0번으로 설정
{	
	x++;
	if(x>981) // 내부 클럭이 16MHz이고 이를 32분주 * 512(Phas Correct PWM 모드에서 상수)로 나누어 주면 주파수는 980hz가 된다
			  // 이를 980카운트 할 시 대략 1초 이므로 대략 1초마다 LED가 TURN-OFF / TURN-ON을 반복하게 됨.
	{
		PORTC = ~PORTC;
		x=0;	
	}
	
}

int main(void)
{
	INIT_TIMER0();
	//INIT_TIMER2();
	INIT_PORT();
	sei();
		
    /* Replace with your application code */
    while (1) 
    {
		OCR0 = 0;
		_delay_ms(1000);
		OCR0 = 64;
		_delay_ms(1000);
		OCR0 = 128;
		_delay_ms(1000);
		OCR0 = 192;
		_delay_ms(1000);
		OCR0 = 255;
		_delay_ms(1000);
    }
}




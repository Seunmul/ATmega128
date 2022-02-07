/*
 * PWM_CONTROL.c
 *
 * Created: 2022-01-28 오후 3:46:51
 * Author : Geonha
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

unsigned char buff =0xfe;
volatile int x;

void INIT_TIMER0(void) // TIMER0 초기화
{
	//TCCR0= ((1<<CS02)|(0<<CS01)|(0<<CS00)); // 1024 분주, NORMAL모드
	TCCR0= ((1<<WGM00)|(0<<WGM01)|(1<<COM00)|(0<<COM01) // Phase Correct PWM up1 down0
	|(1<<CS02)|(0<<CS01)|(0<<CS00)); // 256 분주, Phase Correct PWM
	TCNT0= 0x00; // 카운터 = 256
	OCR0 = 0b01000000;
	TIMSK= 0x01; // TIMER0 인터럽트 enable
}

void INIT_PORT(void) // PORT 초기화
{
	DDRC = 0xff;
	PORTC = 0xff;
}

void led_move(void)
{
	PORTC = buff;
	if(buff == 0x7f)
	buff =0xfe;
	else
	{
		buff <<=1;
		buff |=1;
	}
}

ISR(TIMER0_OVF_vect) //타이머 인터럽트 0번으로 설정
{	
	//TCNT0 = -250;
	x++;
	if(x>1000)
	{
		PORTC=~PORTC;
		x=0;
	}
}

int main(void)
{
	INIT_TIMER0();
	INIT_PORT();
	sei();
		
    /* Replace with your application code */
    while (1) 
    {
	
    }
}

/*
	PORTC = 0x00;
	_delay_ms(500);
	PORTC = 0xff;
	_delay_ms(500);
*/


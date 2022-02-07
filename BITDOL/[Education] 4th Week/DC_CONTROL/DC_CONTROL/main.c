/*
 * DC_CONTROL.c
 *
 * Created: 2022-01-29 오후 3:01:09
 * Author : Geonha
 */ 



#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//SERVO MOTER는 50hz에서
//high가 0.6-2.5ms만큼 각도 제어 (0에서 180)
// 5,6,7번 핀  각각 OC3A, OC3B, OC3C
// 0/1 신호 1/0 신호 입력으로 제어
volatile int x;
void INIT_PORT(void) // PORT 초기화
{
	DDRE = 0xff; // PWM 출력, SERVO 제어, 5,6,7번 핀
	PORTE = 0x00;
	
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

void INIT_TIMER3(void)
{
	TCCR3A = ((1<<COM3A1)|(0<<COM3A0)|(1<<COM3B1)|(0<<COM3B0)|(1<<WGM31)|(0<<WGM30)); 
	//OC3A,B,C 전부 phase correct PWM, 동작모드 역시 phase correct PWM:TOP->OCR3 모드 11
	TCCR3B = ((1<<WGM33)|(0<<WGM32)|(1<<CS32)|(0<<CS31)|(0<<CS30)); // 분주비 : 256
	
	ICR3H = 0x02;	ICR3L = 0x71;//TOP 설정 : 625
	//TCCR3A = 0b00100010; // 10bit 위상교정 PWN(모드3)
	//TCCR3B = 0x03; // 64
	
	OCR3AH = 0x00;	OCR3AL = 0x00; //0             
	OCR3BH = 0x00;  OCR3BL = 0x00; //초기 듀티비 0;
}

int main(void)
{
	INIT_PORT();
	INIT_TIMER0();
	INIT_TIMER3();
	sei();
	
	/* Replace with your application code */
	while (1)
	{
		/*OCR3BH = 0x00; OCR3BL =0x14; //듀티비 3% => 0.6ms high; 0도 19
		_delay_ms(2000);	
		OCR3BH = 0x00; OCR3BL =0x2D; //듀티비 7.7%..? => 90도 49
		_delay_ms(2000);
		OCR3BH = 0x00; OCR3BL =0x4A; //듀티비 12.5% => 2.5ms high; 180도 78
		_delay_ms(2000);
		OCR3BH = 0x00; OCR3BL =0x2D; //듀티비 7.7%..? => 90도 49
		_delay_ms(2000);*/
		
		
		/*OCR3BH = 0x01; OCR3BL =0x38; //듀티비 50%;
		_delay_ms(1000);*/
	
		//OCR3AH = 0x03;  OCR3AL = 0xFF; //듀티비 0%;
		//OCR3BH = 0x00;	OCR3BL = 0x00; // 듀티비 0%
		//_delay_ms(1000);
		
		//OCR3BH = 0x00;	OCR3BL = 0x00 ;// 듀티비 100%
		OCR3AH = 0x00;	OCR3AL = 0x00;// 듀티비 100%
		OCR3BH = 0x02;	OCR3BL = 0x71; // 듀티비 100%
		_delay_ms(3000);	
		OCR3AH = 0x02;	OCR3AL = 0x71;// 듀티비 100%
		OCR3BH = 0x00;	OCR3BL = 0x00; // 듀티비 100%
		_delay_ms(1000);
		
	}
}
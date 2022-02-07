/*
 * PWM.c
 *
 * Created: 2022-02-06 오전 2:05:30
 *  Author: Geonha
 */ 
#include <avr/io.h>
#include <stdio.h>


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
void INIT_TIMER3(void)
{
	TCCR3A = ((1<<COM3A1)|(0<<COM3A0)|(1<<COM3B1)|(0<<COM3B0)|(1<<WGM31)|(1<<WGM30));
	//OC3A,B,C 전부 phase correct PWM, 동작모드 역시 phase correct PWM:TOP->OCR3 모드 11
	TCCR3B = ((1<<WGM33)|(0<<WGM32)|(1<<CS32)|(0<<CS31)|(0<<CS30)); // 분주비 : 256
	
	//ICR3H = 0x02;	ICR3L = 0x71;//TOP 설정 : 625
	//TCCR3A = 0b00100010; // 10bit 위상교정 PWN(모드3)
	//TCCR3B = 0x03; // 64
	
	//OCR3AH = 0x01;	OCR3AL = 0x38; //0
	OCR3AH = 0x02;	OCR3AL = 0x71;//TOP 설정 : 625
	OCR3BH = 0x00;  OCR3BL = 0x00; //초기 듀티비 0;
}
/*
 * ADC_READ_TO_PWM.c
 *
 * Created: 2022-02-06 오전 1:51:52
 * Author : Geonha
 */ 
#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "UART1.h"
#include "PWM.h"

FILE OUTPUT  // OUTPUT 객체
	 = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT  // INPUT 객체
	 = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

volatile int x;
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

void ADC_init(unsigned char channel)
{
	ADMUX |= ((0 << REFS1)|(1 << REFS0)); // AVCC를 기준 전압으로 선택
	
	ADCSRA |= 0x07; // 분주비 설정
	ADCSRA |= (1 << ADEN); // ADC활성화
	ADCSRA |= (1 << ADFR); // 프리러닝 모드
	
	ADMUX = ((ADMUX & 0xE0) | channel); //채널 선택
	ADCSRA |= (1 << ADSC); // 변환시작	
}

int read_ADC(void)
{
	while(!(ADCSRA & (1 << ADIF))); // 변환 종료 대기
	return ADC; // 10비트 값 반환
}


int main(void)
{
	int read; //read값 선언
	int mode=0;
	char buffer[20]=""	; // 수신버퍼
	
	stdout = &OUTPUT; //stdout에 객체를 이어줌
	stdin = &INPUT; // stdin에 객체를 이어줌
	
	INIT_PORT();
	INIT_TIMER0();
	INIT_TIMER3();
	sei();
	
	UART1_init();
	ADC_init(0);
	
	while (1) 
    {
		read = read_ADC();
		int convert = read*0.61; // 1023 ->PWM TOP value로 변환
		char convert_H = ((0x00)|(convert>>8)); // 상위 8비트 입력
		char convert_L = ((0x00)|(convert)); // 하위 8비트 입력
		
		OCR3BH = ((0x00)|(convert_H)); 
		OCR3BL = ((0x00)|(convert_L)); //듀티비 50%;
		
		printf("현재 저항 값 : %d\r\n", read);
		printf("OCR3A : %x %x\r\n",OCR3AH,OCR3AL);
		printf("OCR3B : %x %x\r\n",OCR3BH,OCR3BL);
		printf("\r\n");
		/*printf("ADC to OCR3B %d\r\n",convert);
		printf("ADC to OCR3B %x\r\n",convert);
		printf("ADC to OCR3BH %x\r\n",convert_H);
		printf("ADC to OCR3BL %x\r\n",convert_L);
		*/
		
		_delay_ms(1000);
		/*
		printf("mode를 선택하세요 : ");
		scanf("%d",&mode);
		switch(mode)
		{
			case 0 : 
			{ 
				printf("atmega128에 보낼 문자를 입력하세요 : ");
				scanf("%s", buffer);
				printf("%s\r\n",buffer);
				break;
			}
			case 1 :
			{	
				int cnt=0;
				while(cnt<10){
					read = read_ADC();
					printf("현재 저항 값 : %d\r\n", read);
					_delay_ms(1000);
					cnt++;
				}
				break;
			}
			case 2:
			{
				ADC_init(0B11110);
				int cnt=0;
				while(cnt<10)
				{
					read = read_ADC();
					float AVCC = (1.23*1023)/read;
					printf("AVCC= %f\r\n", AVCC);
					_delay_ms(1000);	
					cnt++;
				}
				break;
			}
			default: break;
		}
		*/	
    }
}


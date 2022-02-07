/*
 * UART1.c
 *
 * Created: 2022-02-05 오후 4:37:56
 *  Author: Geonha
 */ 
#include <avr/io.h>
#include <stdio.h>


void UART1_init(void)
{
	UBRR1H = 0x00;
	UBRR1L = 207; //9600 보드레이트 설정 //103=>1배속
	/*
	UCSRnA는 UART 시리얼 통신의 상태를 확인하고 통신 과정을 제어하기 위한 레지스터
	U2Xn => UCSRnA의 1번 레지스터 비트, 활성화시 2배속 모드로 동작(비동기)
	*/
	UCSR1A |= _BV(U2X1); //_BV는 매크로 함수로 저장된 비트만을 1로하고 나머지를 0으로 하는 비트 마스크를 생성한다.
	
	UCSR1C |= (1<<UCSZ11)|(1<<UCSZ10); // UART 통신에서 데이터 형식 및 통신 방법을 결정하기 위해 사용.
	//비동기, 8비트 데이터, 패리티 없음, 1비트 정지모드
	
	UCSR1B |= _BV(RXEN1); //UCSRnB는 USART 데이터 송수신을 가능하도록 설정하기 위해 사용한다. 디폴트는 0
	UCSR1B |= _BV(TXEN1);
}

void UART1_transmit( char data)
{
	while( !(UCSR1A & (1<<UDRE1)) ); // 송신 기능 대기 //UDREn 비트는 데이터를 완전히 전송하고, UDRn 레지스터에 데이터가 없는 경우 1로 세트
	UDR1 = data; // 데이터 전송 // UDRn은 송수신된 데이터가 저장되는 버퍼 레지스터
}

unsigned char UART1_receive(void)
{
	while( !(UCSR1A & (1<<RXC1)) );// 데이터 수신 대기 //RXCn 비트는 데이터 수신 버퍼에 데이터가 도착했지만 읽지 않은 경우 1로 설정됨.
	return UDR1;
}

void UART1_print_string(char*str)
{
	for(int i=0;str[i];i++)
		UART1_transmit(str[i]);
}

void UART1_print_1_byte_number(uint8_t n)
{
	char numString[4]="0";
	sprintf(numString,"%d",n);
	UART1_print_string(numString);
}
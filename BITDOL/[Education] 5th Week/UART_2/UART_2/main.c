/*
 * UART_2.c
 *
 * Created: 2022-02-05 오후 3:47:13
 * Author : Geonha
 */ 
#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "UART1.h"

FILE OUTPUT  // OUTPUT 객체
	 = FDEV_SETUP_STREAM(UART1_transmit, NULL, _FDEV_SETUP_WRITE);
FILE INPUT  // INPUT 객체
	 = FDEV_SETUP_STREAM(NULL, UART1_receive, _FDEV_SETUP_READ);

int main(void)
{
	uint8_t counter=100; // 카운터
	char buffer[20]=""	; // 수신버퍼
	
	stdout = &OUTPUT; //stdout에 객체를 이어줌
	stdin = &INPUT; // stdin에 객체를 이어줌
	
	UART1_init();
	
	//printf("Current Counter Value : ");
	//printf("%d\r\n", counter);
	/*
	char str[]="TEST using UART1 Library";
	uint8_t num = 128;
	UART1_print_string(str);
	UART1_print_string("\n\r");
	
	UART1_print_1_byte_number(num);
	UART1_print_string("\n\r");
	*/
	
    /* Replace with your application code */
    while (1) 
    {
		/*
		scanf("%s", buffer);
		printf("%s\r\n",buffer);
		if(strcasecmp(buffer,"DOWN")==0){
			counter--; //카운터 감소
			
			printf("Current Counter Value : ");
			printf("%d\r\n", counter);
		}
		else if(strcasecmp(buffer,"UP")==0){
			counter++; // 카운터 증가
			
			printf("Current Counter Value : ");
			printf("%d\r\n", counter);
		}
		else{
			//printf("** Unkwon Command **\r\n");
		}*/
		UART1_transmit(UART1_receive());
    }
}


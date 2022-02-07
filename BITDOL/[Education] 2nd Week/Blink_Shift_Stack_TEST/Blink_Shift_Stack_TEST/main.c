/*
 * Blink_Shift_Stack_TEST.c
 *
 * Created: 2022-01-13 오후 3:16:09
 * 최종수정 : 2022-01-17 오후 12:06
 * Author : Geonha
 * 내용 : blink test, shift test, stack test
 * 최종수정 내용 : 코드 정리, 버그 수정, stack_1 stack_2 stack 함수 작성 및 디버깅
 */
#define F_CPU 16000000L
#define MSB_COUNT 8
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>

void stack(char* init,char*result,int*level,int*stack_case);
void stack_1(char* init, char* result, int* level);
void stack_2(char* init, char* result, int* level);
void blink();
char shift(char temp);

int main(void){
	
	DDRC = 0xff; // PORTC를 출력단자로 사용
	PORTC = 0x00; // PORTC를 시작할때 전부 ON
	
	char temp= 0x01; // for shift, char형으로 1byte, 8bit 크기 할당.
	char init = 0x01; // for stack
	char result = 0x00; // for stack
	int level = 1; // for stack
	int stack_case = 1; // for stack
	
	_delay_ms(1000);
	
	while (1)
	{
		blink();
		//temp = shift(temp);
		//stack(&init,&result,&level,&stack_case);
	}
	
	return 0;
}

void blink(){
	//LED BLINK TEST
	//풀업이라서 포트에 0을 면 LED가 켜지고, 1을 주면 LED가 꺼짐.
	//LED는 회로 기준으로 왼쪽부터 1번-8번, LED기준으로 8번-1번, 8번이 MSB가 나오게끔.
	//즉 1번 LED에 LSB인 35번 포트 연결, 우측->좌측으로 36,7,8,9,40,41,42(MSB)
	//그림으로 나타내면 42 41 40 39 38 37 36 35
	
	//0b 이진법 , 0x 16진법, MSB가 42번 포트, LSB가 35번 LED제어
	PORTC = 0xff;
	_delay_ms(1000);
	PORTC = 0x00;
	_delay_ms(1000);
	
	return;
};

char shift(char temp){
	//LED SHIFT TEST
	//8비트 크기 연산자 temp를 받아 이를 반환. 루프 속에서 계속 값을 계속 최신화
	
	PORTC= ~(temp);
	if(temp!=0 && temp<0xff){
		temp=temp<<1;
		_delay_ms(500);
	}
	else
	temp=0x01;
	return temp;
}

void stack(char* init,char*result,int*level,int*stack_case)
{
	switch(*stack_case)
	{
		case 1: {
			if((*result) == 0xff && (*level) != 1){(*stack_case)=2; (*init)=0x80; (*result)=0x00; (*level)=1; break; }
			stack_1(init,result,level);
			break;
		}
		case 2:	{
			if((*result) == 0xff && (*level) != 1){(*stack_case)=1; (*init)=0x01; (*result)=0x00; (*level)=1; break; }
			stack_2(init,result,level);
			break;
		}
		default: break;
	}
	return;
}


void stack_1(char* init, char* result, int* level){
	
	//최대반복횟수에서 -1을 하여 init에 해당 단계의 MSB만 1인 값 저장
	for(int i=0; i < (MSB_COUNT) - *level;i++ ){
		PORTC=~((*result) + (*init));
		_delay_ms(500);
		(*init)<<=1;
	}
	PORTC=~(*result + *init);
	(*result)+=(*init);
	(*init)=0x01;
	(*level)++;
	_delay_ms(500);
	return;
}

void stack_2(char* init, char* result, int* level){
	for(int i=0; i < (MSB_COUNT) - *level;i++ ){
		PORTC=~((*result) + (*init));
		_delay_ms(500);
		(*init)>>=1;
	}
	PORTC=~(*result + *init);
	(*result)+=(*init);
	(*init)=0x80;
	(*level)++;
	_delay_ms(500);
	return;
}

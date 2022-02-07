/*
 * Interrupt_Control.c
 *
 * Created: 2022-01-20 오후 10:52:56
 * Author : Geonha
 * 트리거 동작에 대해서 이해, 채터링 해결해보자.
 */ 

#define F_CPU 16000000UL
#define MSB_COUNT 8
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


volatile int stateA=1;
volatile int stateB=1;
char init = 0x01; // for stack
char result = 0x00; // for stack
int level = 1; // for stack
int stack_case = 1; // for stack

void stack(char* init, char* result, int* level){
		
		//최대반복횟수에서 -1을 하여 init에 해당 단계의 MSB만 1인 값 저장
		for(int i=0; i < (MSB_COUNT) - *level;i++ ){
			PORTC=~((*result) + (*init));
			_delay_ms(200);
			(*init)<<=1;
		}
		PORTC=~(*result + *init);
		(*result)+=(*init);
		(*init)=0x01;
		(*level)++;
		_delay_ms(200);
		/*if((*level)==MSB_COUNT)
		{
			(*init) =0x01;
			(*result)=0x00;
			(*level) =1;
		}*/
		return;
}

ISR(INT4_vect)
{
	stateA = (stateA+1) %2;	
}

void INIT_PORT(void)
{	
	DDRC = 0xff;
	PORTC = 0xff;
}

void INIT_INT4(void)
{
	EIMSK = 0x00; // 인터럽트 허용 직전 초기화
	EICRA = 0x00; //INT3-0 사용 X=>초깃값 할당
	EICRB = 0b00000010; //INT4 하강에지 인터럽트 설정
	//EICRB = 0b00000011; //INT4 상승에지 인터럽트 설정
	//EICRB = 0b00000001; //INT4 레벨 트리거 인터럽트 설정
	EIMSK = 0b00010000; // INT4 인터럽트 허용
	EIFR = 0xFF; //
	sei(); //status register 설정=>1 IF I bit of SREG is set, then ISR will be excuted.
	//cli() // set status register I bit => 0
	/* Replace with your application code */
}

int main(void)
{
	INIT_PORT();
	INIT_INT4();
	
	while (1) {
		/*
		if(stateA==1){
			PORTC = ~(result);
			} else {
			
			PORTC = 0xff;
			stack(&init,&result,&level);
			stateA=1;
			if((level)==MSB_COUNT+2){
					(init) =0x01;
					(result)=0x00;
					(level) =1;
				}
			}
		*/
		if(stateA==1){
			PORTC = 0xff;
			} else {
			PORTC = 0x00;
		}
	}
	return 0;
}

/*
		ISR(INT4_vect)
		{
			stateA = (stateA+1) %2;
		}
		if(stateA==1){
			PORTC = 0xff;
			} else {
			PORTC = 0x00;
		}
*/

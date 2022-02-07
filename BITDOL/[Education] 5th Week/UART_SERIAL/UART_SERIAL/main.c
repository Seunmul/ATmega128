/*
 * UART_SERIAL.c
 *
 * Created: 2022-02-03 오후 8:32:20
 * Author : Geonha
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "usart.h"

void USART_init(unsigned char ch, unsigned int ubrr_baud)
{
	if( ch == USART0){
		UCSR0B |= 1<<RXEN0 | 1<<TXEN0 | 1<<RXC0;
		UBRR0H = ubrr_baud >> 8;
		UBRR0L = ubrr_baud;
	}else if(ch == USART1){
		UCSR1B |= 1<<RXEN1 | 1<<TXEN1 | 1<<RXC1;
		UBRR0H = ubrr_baud >> 8;
		UBRR0L = ubrr_baud;
	}
}
int USART1_send(char data,FILE*stream)
{
	while(!(UCSR1A & (1<<UDRE1)) );
	UDR1 = data;
	return data;
}
int USART1_receive(FILE*stream)
{
	while(!(UCSR1A & (1<<RXC1))  );
	return UDR1;
}
/*
int USART1_send(char data,FILE*stream)
{
	while((tx1_head+1)==tx1_tail)||((tx1_head==LENGTH_TX_BUFFER-1)&&(tx1_tail==0)));
	tx1_buffer[tx1_head] = data;
	tx1_head =(tx1_head==LENGTH_TX_BUFFER-1)?0:tx1_head+1;
	UCSR1B = UCSR1B | 1<<UDRIE1;
	
	return data;
}
ISR(USART1_UDRE_vect)
{
	UDR1 = tx1_buffer[tx1_tail];
	tx_tail = (tx1_tail == LENGTH_TX_BUFFER-1)?0:tx1_tail+1;
	
	if(tx1_tail==tx1_head)
	UCSR1B = UCSR1B & ~(1<<UDRIE1);
}	

int USART_receive(FILE*stream)
{
	unsigned char data;
	
	while( rx1_head == rx1_tail);
	
	data = rx1_buffer[rx1_tail];
	rx1_tail = (rx1_tail == LENGTH_RX_BUFFER-1)?0:rx1_tail +1;
	
	return data;
}
ISR(USART1_RX_vect)
{
	volatile unsigned char data;
	if((rx1_head+1==rx1_tail)||(rx1_head==LENGTH_RX_BUFFER-1)&&(rx1_tail ==0))){
		data=UDR1;
	}else{
		rx1_buffer[rx1_head] = UDR1;
		rx1_head = (rx1_head==LENGTH_RX_BUFFER-1)?0:rx1_head+1;
	}
}

static FILE usart1_stdio = FDEV_SETUP_STREAM(USART1_send, USART1_receive,_FDEV_SETUP_RW);
*/
int main(void)
{
	USART_init(USART1, 103); //USART1 보오레이트 :38400(UBRR=12)
    //stdin = stdout =stderr =&usart1_stdio;
	
	/* Replace with your application code */
    while (1) 
    {
		
    }
}


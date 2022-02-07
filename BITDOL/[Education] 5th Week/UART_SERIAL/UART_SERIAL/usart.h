/*
 * usart.h
 *
 * Created: 2022-02-03 오후 9:18:59
 *  Author: Geonha
 */ 

#ifndef __USART_H___
#define __USART_H__
#include <stdio.h>

#define USART0 ((unsigned char)0)
#define USART1 ((unsigned char)1)

extern void USART_init(unsigned char ch, unsigned int ubrr_baud);
extern int USART1_send(char data,FILE*stream);
extern int USART1_receive(FILE*stream);

#endif
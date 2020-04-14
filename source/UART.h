#ifndef UART_H_
#define UART_H_

#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"
#include "stdarg.h"

#include "MKL25Z4.h"
#include "LED.h"
#include "buffer.h"
#include "mode.h"

extern volatile circular_buffer_state circularbuffRx;
extern volatile circular_buffer_state circularbuffTx;
extern volatile bool Txbuffer_isfull;


extern UART0_Type *uartstate;

UART0_Type* UARTinitialize(void *buffmem, const size_t numBytes, uint32_t sysclck, uint32_t baud);

//Function to check whether the Receiver is available
//to accept a new character for transmission
bool isUART_RxAvailable(UART0_Type* state);

//Function to check whether the transmitter is available
//to accept a new character for transmission
bool isUART_TxAvailable(UART0_Type* state);

//Function to receive a character assuming receiver
//is available
uint8_t UART_getchar(UART0_Type* state);

//Function to transmit a character assuming transmitter
//is available
void UART_putchar(UART0_Type* state, uint8_t c);

//enable the transfer interrupt
void UART_enable_TxInterrupt(UART0_Type* state);

//disable the transfer interrupt
void UART_disable_TxInterrupt(UART0_Type* state);

//add character to transfer circular buffer
void UART_addchar(UART0_Type* state, char c);

//add string to transfer circular buffer
void UART_addstring(UART0_Type* state, char* string);

//http://www.firmcodes.com/write-printf-function-c/
void UART_Myprintf(UART0_Type* state, const char* format,...);

//http://www.firmcodes.com/write-printf-function-c/
char *convert(unsigned int num, int base);

//is Data Transfer complete
bool UART_isTxDone(UART0_Type* state);


#endif //UART_H_

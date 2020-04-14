#include "UART.h"
#include "buffer.h"

volatile circular_buffer_state circularbuffRx;
volatile circular_buffer_state circularbuffTx;
volatile bool Txbuffer_isfull= false;

UART0_Type *uartstate = NULL;

//function for UART hardware initialization
//including baud rate and serial message format
//(parity/start/stop bits)

UART0_Type* UARTinitialize(void *buffmem, const size_t numBytes, uint32_t sysclk, uint32_t baud)
{
	uint16_t sbr; //system baud rate
	uint8_t buffer;

	if(numBytes<sizeof(UART0_Type))
	{
		return(NULL);
	}

	uartstate = (UART0_Type*)buffmem;
	UART0_Type *uart = (UART0_Type *)uartstate;

	//TX and RX disabled to init UART
	uart->C2 &= ~(UART_C2_TE_MASK
			      | UART_C2_RE_MASK );

	//configure UART 8-bit no parity
	uart->C1 = 0;

	//setup baud rate
	 sbr = (uint16_t)((sysclk*1000)/baud*16);

	 //save current value of uartx_BDH high with exception of sbr high
	 buffer = uart->BDH &~ (UART_BDH_SBR(0x1F));
	 uart->BDH = buffer | UART_BDH_SBR(((sbr & 0x1F00) >> 8));
	 uart->BDL = (uint8_t)(sbr & UART_BDL_SBR_MASK);

	 //Enable TX and TX
	 uart->C2 |= (UART_C2_TE_MASK
			 | UART_C2_RE_MASK );

	 circularbuffRx = malloc(sizeof(circular_buffer_param));
	 circular_buffer_init((void*)circularbuffRx, sizeof(circular_buffer_param), 4);

	 circularbuffTx = malloc(sizeof(circular_buffer_param));
	 circular_buffer_init((void*)circularbuffTx, sizeof(circular_buffer_param), 4);



#ifdef INTERRUPT
	 //enable Interrupt
	 Enable_Int;
	 NVIC_EnableIRQ(UART0_IRQn);
	 uart->C2 |= UART_C2_RIE_MASK;
#endif

	 return(uartstate);
}

//http://www.firmcodes.com/write-printf-function-c/
void UART_Myprintf(UART0_Type* state, const char* format,...)
{
	UART0_Type *uart = (UART0_Type *)state;
	char *traverse;
	unsigned int i;
	char *s;

	//Module 1: Initializing Myprintf's arguments
	va_list arg;
	va_start(arg, format);

	for(traverse = format; *traverse != '\0'; traverse++)
	{
		while( *traverse != '%' && *traverse != '\0')
		{
			UART_addchar(state, (*traverse));
			traverse++;
		}

		if((*traverse) == '\0')
			break;
		//va_end(arg)

		traverse++;

		//Module 2: Fetching and executing arguments
		switch(*traverse)
		{
			case 'c' :
				i = va_arg(arg, int);		//Fetch char argument
				UART_addchar(state,i);
				break;

			case 'd' :
				i = va_arg(arg,int); 		//Fetch Decimal/Integer argument
				if(i<0)
				{
					i = -i;
					UART_addchar(state,i);
				}
				UART_addstring(uart, (convert(i,10)));
				break;

			case 'o':
				i = va_arg(arg,unsigned int); //Fetch Octal representation
				UART_addstring(uart, (convert(i,8)));
				break;

			case 's':
				s = va_arg(arg,char *); 		//Fetch string
				UART_addstring(uart,s);
				break;

			case 'x':
				i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
				UART_addstring(uart, (convert(i,16)));
				break;
		}
	}

	//Module 3: Closing argument list to necessary clean-up
	va_end(arg);
}



//Function to check whether the Receiver is available
//to accept a new character for transmission
bool isUART_RxAvailable(UART0_Type* state)
{
	UART0_Type *uart = (UART0_Type *)state;

	if(uart->S1 & UART_S1_TDRE_MASK)
	{
		return true;
	}
	else
	{
		return false;
	}

}


//Function to check whether the transmitter is available
//to accept a new character for transmission
bool isUART_TxAvailable(UART0_Type* state)
{
	UART0_Type *uart = (UART0_Type *)state;
	if(uart->S1 & UART_S1_TDRE_MASK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Function to receive a character assuming receiver
//is available
uint8_t UART_getchar(UART0_Type* state)
{
	UART0_Type *uart = (UART0_Type *)state;

	LED_cycleblue_On();
	delay2();
	LED_off();

#ifndef INTERRUPT
	while(!isUART_RxAvailable(uart));
#endif
	return uart->D;
}


//Function to transmit a character assuming transmitter
//is available
void UART_putchar(UART0_Type* state, uint8_t c)
{
	UART0_Type *uart = (UART0_Type *)state;

	LED_cyclegreen_On();
	delay2();
	LED_off();

#ifndef INTERRUPT
	while(!isUART_TxAvailable(uart));
#endif
	uart->D = (uint8_t)c;
}


//enable the transfer interrupt
void UART_enable_TxInterrupt(UART0_Type* state)
{
	UART0_Type *uart = (UART0_Type *)state;
	uart->C2 |= UART_C2_TIE_MASK;
}

//disable the transfer interrupt
void UART_disable_TxInterrupt(UART0_Type* state)
{
	UART0_Type *uart = (UART0_Type *)state;
	uart->C2 &= ~UART_C2_TIE_MASK;
}

//add character to transfer circular buffer
void UART_addchar(UART0_Type* state, char c)
{
	if(circulcar_buffer_addnewdata(circularbuffTx, c) == error_buffer_full)
	{
		Txbuffer_isfull = true;
	}

#ifdef INTERRUPT
	UART_enable_TxInterrupt(state);
#endif
}

//add string to transfer circular buffer
void UART_addstring(UART0_Type* state, char* string)
{
	int i=0;
	while(string[i] != '\0')
	{
		UART_addchar(state, string[i++]);
	}
}


//http://www.firmcodes.com/write-printf-function-c/
char *convert(unsigned int num, int base)
{
	static char Representation[]= "0123456789ABCDEF";
	static char buffer[50];
	char *ptr;

	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = Representation[num%base];
		num /= base;
	}while(num != 0);

	return(ptr);
}

//is Data Transfer complete
bool UART_isTxDone(UART0_Type* state)
{
	UART0_Type *uart = (UART0_Type *)state;
	return uart->S1 & UART0_S1_TC_MASK;
}

volatile uint8_t nxtByte;
volatile bool nxtData = false;

#ifdef INTERRUPT
void UART0_IRQstate(void)
{
	Disable_Int;


	UART0_Type *state = (UART0_Type *)UART0_BASE;
	UART0_Type *uart = (UART0_Type *)state;

	if(uart->S1 & UART_S1_RDRF_MASK && uart->C2 & UART_C2_RIE_MASK)
	{
		//ECHO MODE
	#ifdef ECHO
			nxtByte = UART_getchar(uart);
			nxtData = true;
	#endif
		//APPLICATION MODE
	#ifdef APPLICATION
			circulcar_buffer_addnewdata(circularbuffRx, UART_getchar(uart));
			nxtData = true;
	#endif
	}
	if(uart->S1 & UART_S1_TDRE_MASK && uart->C2 & UART_C2_TIE_MASK)
	{
	#ifdef ECHO
			if(nxtData)
			{
				UART_putchar(uart, nxtData);
				nxtData=false;
			}
	#endif
	#ifdef APPLICATION
			if(!circular_buffer_isempty(circularbuffTx))
			{
				UART_putchar(uart, circular_buffer_check(circularbuffTx));
				while(!UART_isTxDone(uart));
				circular_buffer_remove(circularbuffTx);
			}
			//Disable Tx ready Int
			uart->C2 &= ~UART_C2_TIE_MASK;
	#endif
	}
	Enable_Int
}
#endif



//Function using (TXavailable) and (TXcharacter if available)
//to wait (block) for TX to be available and then once available
//transmit a character and return

//same for receive

//an echo function that uses above functions to echo received characters
//one at a time back to the PC-based sender



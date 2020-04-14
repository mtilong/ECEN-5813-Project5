

#include "Project5turnin.h"

/*!
 * @brief Main function
 */

loggerstate logger;
UART0_Type* uart;


uint32_t count[128] = {0};


int main(void)
{

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    //PRINTF("hello world.\r\n");
    KL25Z_RGB_Flasher();

#ifndef TEST
    SysTick_Config(4800000); //10hz
    uart = malloc(sizeof(UART0_Type));
    uart = UARTinitialize((void *)UART0_BASE, sizeof(UART0_Type), 24000, 115200);

    logger = malloc(sizeof(loggerparam));

    logger = Log_function((void*)logger, sizeof(loggerparam), uart);
    Log_statusenable(logger);
    Log_datastring(logger, "Program Started", "main", log_status);

#endif

 //Test MODE
#ifdef TEST
    test_circular_buffer();
    exit(0);
#endif

    //PRINTF("hello world.\r\n");


//ECHO MODE
#ifdef ECHO
#ifndef INTERRUPT
		Log_datastring(logger, "ECHO MODE WITH POLLING", "main", log_status);
		while(1)
		{
			UART_putchar(uart, UART_getchar(uart));
		}
#else
		Log_datastring(logger,"ECHO MODE WITH INTERRUPTS", "main", log_status);

		while(1)
		{
		}
#endif
#endif


//Application Mode
#ifdef APPLICATION
#ifdef INTERRUPT
		Log_datastring(logger, "APPLICAITON MODE WITH INTERRUPTS", "main", log_status);

	#else
	Log_datastring(logger, "APPLICATION MODE WITH POLLING", "main", log_status);
	#endif

	while(1)
	{
		#ifndef INTERRUPT
		if(circulcar_buffer_addnewdata(circularbuffRx, UART_getchar(uart))== error_buffer_full)
		{
			#ifdef RESIZE_BUFFER
			Log_datastring(logger, "RESIZE THE BUFFER IF BUFFER IS TOO FULL", "main", log_status);
			#endif
		}
		#endif
	}

	//buffer not empty
		if(!circular_buffer_isempty(circularbuffRx))
		{
			uint8_t data = circular_buffer_check(circularbuffRx);
			if(isalnum(data)||ispunc(data))
			{
				count[data]++;
			}
			else if(data == CHARACTER_LEFTOUT)
			{
				Log_datastring(logger, "REPORT INITIAL STATUS", "main", log_status);
				for(int i=0; i<128; i++)
				{
					if(count[i]>0)
					{
						UART_Myprintf(uart, "[%c-d]", (char)i, count[i]);
					}
				}
				UART_Myprintf(uart, "\n\r");
				Log_datastring(logger, "REPORT STATUS COMPLETE", "main", log_status);
			}
			circular_buffer_remove(circularbuffRx);
		}

		if(!circular_buffer_isempty(circularbuffTx))
		{
			LED_cyclered_On();
			delay2();
			LED_off();

			#ifdef INTERRUPT
			UART_enable_TxInterrupt(uart);
			#else
			UART_putchar(uart, circular_buffer_check(circularbuffTx));
			circular_buffer_remove(circularbuffTx);
            #endif
		}
		else
		{
			LED_cyclegreen_On();
			delay2();
			LED_off();
		}
		if(Txbuffer_isfull)
		{
			Txbuffer_isfull = false;
			#ifdef RESIZE_BUFFER
			Log_datastring(logger, "RESIZE TRANSMIT BUFFER", "main", log_status);

			//UART_Myprintf(uart, "New size of buffer: %d Bytes\n\r\", circular_buffer_size(circularbuffTx));
			#endif
		}
#endif
}


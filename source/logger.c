#include "logger.h"

loggerstate Log_function(void *buffmem, const size_t numbytes, UART0_Type* uart)
{
	loggerstate state;
	loggerparam *param;

	/*if(numbytes<sizeof(UART0_Type))
		{
			return(NULL);
		}*/

	state = (loggerstate)buffmem;
	param =(loggerparam *)state;
	param->status = logger_disable;
	param->uart = uart;

	return state;
}

void Log_statusenable(loggerstate state)
{
	loggerparam *param = (loggerparam *)state;
	 param->status = logger_enable;
}


void Log_statusdisable(loggerstate state)
{
	loggerparam *param = (loggerparam *)state;
	 param->status = logger_disable;
}

void Log_status(loggerstate state)
{
	loggerparam *param = (loggerparam *)state;
	 param->status;
}


void Log_data(loggerstate state, uint8_t* place, size_t len, const char* func, logger_case level)
{
	loggerparam *param = (loggerparam *)state;
	if (param->status == logger_enable)
	{
		for(int i = 0; i<len; i++)
		{
			UART_Myprintf(param->uart, "Test \n\r");
			log_timer(state);
			UART_Myprintf(param->uart, "In func %s()\n\r", func);
			UART_Myprintf(param->uart, "%s: %s\n\r", log_testcase(level), place[i]);
		}

		UART_Myprintf(param->uart, "\n\r");
	}

}


void Log_datastring(loggerstate state, const char* string, const char* func, logger_case level)
{
	loggerparam *param = (loggerparam *)state;
	if (param->status == logger_enable)
	{
		UART_Myprintf(param->uart, "Test \n\r");
		log_timer(state);
		UART_Myprintf(param->uart, "In func %s()\n\r", func);
		UART_Myprintf(param->uart, "%s: %s\n\r", log_testcase(level), string);
	}

}

void log_timer(loggerstate state)
{
	loggerparam *param = (loggerparam *)state;
	if(param->status == logger_enable)
	{
		UART_Myprintf(param->uart, "%d:%d:%d.%d\n\r", time.hours, time.minutes,time.seconds,time.tenth_sec);
	}

}

const char* log_testcase(logger_case test_case)
{
  switch(test_case)
  {
	  case log_test:
	  {
		  return "TEST\0";
		  break;
	  }
	  case log_debug:
	  {
		  return "DEBUG\0";
		  break;
	  }
	  case log_status:
	  {
		  return "STATUS\0";
		  break;
	  }
  }
}

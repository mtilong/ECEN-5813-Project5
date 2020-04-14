#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "MKL25Z4.h"

#include "LED.h"
#include "buffer.h"
#include "UART.h"
#include "timestamp.h"
#include "unit_testing.h"
#include "mode.h"

#ifndef LOGGER_H_
#define LOGGER_H_

typedef enum
{
	logger_enable,
	logger_disable
}logger_status;

typedef enum
{
	log_test,
	log_debug,
	log_status
}logger_case;

typedef struct logger_param
{
	logger_status status;
	UART0_Type* uart;

}loggerparam;

typedef struct logger_param *loggerstate;

loggerstate Log_function(void *buffmem, const size_t numbytes, UART0_Type* uart);

void Log_statusenable(loggerstate state);

void Log_statusdisable(loggerstate state);

void Log_status(loggerstate state);

void Log_data(loggerstate state, uint8_t* place, size_t len, const char* func, logger_case level);

void log_timer(loggerstate state);

const char* log_testcase(logger_case test_case);

void Log_datastring(loggerstate state, const char* string, const char* func, logger_case level);


#endif //LOGGER_H_

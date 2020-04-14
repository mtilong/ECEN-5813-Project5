#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "Stdio.h"


#include "pin_mux.h"
#include "LED.h"
#include "buffer.h"
#include "UART.h"
#include "timestamp.h"
#include "unit_testing.h"
#include "logger.h"
#include "mode.h"

extern loggerstate state;
extern UART0_Type* uart;
#define CHARACTER_LEFTOUT 27



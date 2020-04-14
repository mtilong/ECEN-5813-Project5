#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "buffer.h"
#include "MKL25Z4.h"



typedef struct timestamp
{
	uint32_t hours;
	uint32_t minutes;
	uint32_t seconds;
	uint32_t tenth_sec;

}timestamp;

extern volatile timestamp time;

extern uint32_t microsec;

void clock(volatile timestamp* timer);

#endif //TIME_H_

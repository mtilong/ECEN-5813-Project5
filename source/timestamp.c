#include "timestamp.h"


volatile timestamp time =
{
		.tenth_sec = 0,
		.seconds = 0,
		.minutes = 0,
		.hours = 0
};


void clock(volatile timestamp* timer)
{
	timer->tenth_sec++;
	if(timer->tenth_sec>10)
	{
		timer->tenth_sec = 0;
		timer->seconds++;
		if(timer->seconds>60)
		{
			timer->seconds = 0;
			timer->minutes++;

			if(timer->minutes >60)
			{
				timer->minutes = 0;
				timer->hours++;

			}
		}
	}

}


void SysTick_Handler(){
	clock(&time);
}



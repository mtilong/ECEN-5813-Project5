#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"

#include <string.h>
#include "MKL25Z4.h"
#include "mode.h"

//#define ECHO
//#define INTERRUPT
//#define APPLICATION


#ifndef CIRCULARBUFF_H_
#define CIRCULARBUFF_H_


//circular buffer enum errors
typedef enum
{
	error_buffer_full,
	error_buffer_empty,
	no_error,
}error_buffer;



//circular buffer structure
typedef struct circular_buffer
{
	uint8_t *buffer_pointer;
	uint8_t *head;
	uint8_t *tail;
	uint32_t len;
	uint32_t count;
	bool isinit;
}circular_buffer_param;


typedef struct circular_buffer *circular_buffer_state;

//initialize new buffer
circular_buffer_state

/*
 * buffmem: pointer to buffer memory
 */

circular_buffer_init(void *buffmem, const size_t numbyte, const size_t buff_t);

//add new item to buffer and return error_buffer_full if buffer is full.
error_buffer
circulcar_buffer_addnewdata(circular_buffer_state state, uint8_t data);

//remove oldest byte from buffer, return error if buffer is empty
error_buffer
circular_buffer_remove(circular_buffer_state state);

//check if buffer is full
bool circular_buffer_isfull(circular_buffer_state state);

//check if buffer is empty
bool circular_buffer_isempty(circular_buffer_state state);

//Return error if buffer is empty.
uint8_t
circular_buffer_check(circular_buffer_state state);

//check if buffer initialize
bool circular_buffer_isinit(circular_buffer_state state);

//check buffer size
size_t
circular_buffer_size(circular_buffer_state state);

//destroy buffer
void circular_buffer_destroy(circular_buffer_state state);


#endif /*CIRCULARBUFF_H*/

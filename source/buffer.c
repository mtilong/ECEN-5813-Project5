#include "buffer.h"


//initialize new buffer
circular_buffer_state
circular_buffer_init(void *buffmem, const size_t numbyte, const size_t buff_t)
{
	circular_buffer_state state;
	circular_buffer_param *param;

	if(numbyte < sizeof(circular_buffer_param))
	{
		return((circular_buffer_state)NULL);
	}
	state = (circular_buffer_state)buffmem; //circular buffer pointer to memory
	param = (circular_buffer_param*)state;

	param->buffer_pointer = (uint8_t*)malloc(buff_t);
	param->count = 0;
	param->head = state->buffer_pointer;
	param->tail =state->buffer_pointer;
	param->len = buff_t;
	param->isinit = true;

	return state;
}

//check buffer size
size_t
circular_buffer_size(circular_buffer_state state)
{
	circular_buffer_param *param = 	(circular_buffer_param *)state;

	return param->len;
}

//add new byte to buffer and return error_buffer_full if buffer is full.
error_buffer
circulcar_buffer_addnewdata(circular_buffer_state state, uint8_t data)
{
	circular_buffer_param *param = (circular_buffer_param *)state;
	if(!circular_buffer_isfull(state))
	{
		START_CRITICAL;
		*(param->head) = data;
		param->head++;
		if(param->head>=param->len+param->buffer_pointer)
		{
			param->head=param->buffer_pointer;
		}
		param->count++;
		END_CRITICAL
		return no_error;
	}
	else
	{
		START_CRITICAL
		//when tails is equal to head there is an overflow
		size_t tailoverflow = param->tail-param->buffer_pointer;
		//readjust buffer
		size_t headoverflow = tailoverflow+param->len;
		//realloc memory for new buffer size
		uint8_t* newbuff = realloc(param->buffer_pointer, param->len);
		param->buffer_pointer = newbuff;

		//new circular buffer per the offset.
		param->head = param->buffer_pointer + headoverflow;
		param->tail = param->buffer_pointer + tailoverflow;
		memcpy((param->len+param->buffer_pointer), param->buffer_pointer, tailoverflow);

		*(param->head) = data;
		param->head++;
		if(param->head>=param->len+param->buffer_pointer)
		{
			param->head=param->buffer_pointer;
		}
		param->count++;
		END_CRITICAL
		return error_buffer_full;
	}
}

//remove oldest byte from buffer, return error if buffer is empty
error_buffer
circular_buffer_remove(circular_buffer_state state)
{
	circular_buffer_param *param = (circular_buffer_param *)state;
	if(!circular_buffer_isempty(state))
	{
		START_CRITICAL;
		param->tail++;
		if(param->tail >= (param->len+param->buffer_pointer))
		{
			param->tail = param->buffer_pointer;
		}
		param->count--;

		END_CRITICAL
		return no_error;
	}
	else
	{
		return error_buffer_empty;
	}


}

//check if buffer is full
bool circular_buffer_isfull(circular_buffer_state state)
{
	circular_buffer_param *param = 	(circular_buffer_param *)state;
	if(param->count >= param->len)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//check if buffer is empty
bool circular_buffer_isempty(circular_buffer_state state)
{
	circular_buffer_param *param = (circular_buffer_param *)state;
	if(param->count>=param->len)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Return error if buffer is empty.
uint8_t
circular_buffer_check(circular_buffer_state state)
{
	circular_buffer_param *param = (circular_buffer_param *)state;
	if(!circular_buffer_isempty(state))
	{
		return *(param->tail);
		return no_error;
	}
	else
	{
		return error_buffer_empty;
	}
}

//check if buffer initialize
bool circular_buffer_isinit(circular_buffer_state state)
{
	circular_buffer_param *param = (circular_buffer_param *)state;
	return param->isinit;
}


//destroy buffer
void circular_buffer_destroy(circular_buffer_state state)
{
	circular_buffer_param *param = 	(circular_buffer_param *)state;


	param->isinit = false;
	free(param->buffer_pointer);
}


#include "unit_testing.h"
#include "buffer.h"
#include "mode.h"
//#include "Project5turnin.h"

#ifdef TEST
circular_buffer_state test_circularbuff;
#endif

void test_circular_buffer(void)
{
#ifdef TEST

	UCUNIT_TestcaseBegin("Testing Circular Buffer Functionality");

	test_circularbuff = malloc(sizeof(circular_buffer_param));

	circular_buffer_init((void*)test_circularbuff, sizeof(circular_buffer_param), 3);

	UCUNIT_CheckIsEqual(true,circular_buffer_isempty(test_circularbuff));

	UCUNIT_CheckIsEqual(error_buffer_empty,circular_buffer_remove(test_circularbuff));

	UCUNIT_CheckIsEqual(error_buffer_empty,circular_buffer_check(test_circularbuff));

	for(int i = 0; i < 5; i++)
	{
		UCUNIT_CheckIsEqual(circulcar_buffer_addnewdata(test_circularbuff, i),no_error);

		UCUNIT_CheckIsEqual(circular_buffer_check(test_circularbuff),i);

		UCUNIT_CheckIsEqual(circular_buffer_remove(test_circularbuff),no_error);
	}

	UCUNIT_CheckIsEqual(circular_buffer_remove(test_circularbuff),error_buffer_empty);

	for(int i = 0; i < 3; i++)
	{
		UCUNIT_CheckIsEqual(circulcar_buffer_addnewdata(test_circularbuff, i),no_error);
	}

	UCUNIT_CheckIsEqual(circulcar_buffer_addnewdata(test_circularbuff, 3),error_buffer_full);
	UCUNIT_CheckIsEqual(circulcar_buffer_addnewdata(test_circularbuff, 4),no_error);

	for(int i = 0; i < 5; i++)
	{
		UCUNIT_CheckIsEqual(circular_buffer_check(test_circularbuff),i);
		UCUNIT_CheckIsEqual(circular_buffer_remove(test_circularbuff),no_error);
	}

	UCUNIT_CheckIsEqual(circular_buffer_remove(test_circularbuff),error_buffer_empty);

	for(int i = 0; i < 20; i++)
	{
		circulcar_buffer_addnewdata(test_circularbuff, i);
	}
	for(int i = 0; i < 20; i++)
	{
		UCUNIT_CheckIsEqual(circular_buffer_check(test_circularbuff),i);
		circular_buffer_remove(test_circularbuff);
	}


	UCUNIT_TestcaseEnd();
#endif
}




#include "unity.h" // Single Unity Test Framework include
#include <stdio.h>

#include "c_period_callbacks.h"

// Mock the UART2 C header API
#include "Mockc_uart2.h"
#include "Mockio.h"
void setUp(void) {
	//char send_data= '0';
}
void tearDown(void) {
}

void test_C_period_init(void) {
	uart2_init_IgnoreAndReturn(true);
  TEST_ASSERT_TRUE(C_period_init());
}

void test_C_period_1Hz(void) {
	//char send_data='A';
	C_LED_Display_Ignore();
	uart2_getchar_IgnoreAndReturn(true);
	//uart2_putChar_ExpectAnyArgsAndReturn(true);
    //TEST_ASSERT_GREATER_THAN(47,C_period_1Hz(0));
//	TEST_ASSERT_LESS_THAN(59,C_period_1Hz(0));
	//uart2_getchar_ExpectAndReturn(NULL, 0, false);
    //uart2_getchar_IgnoreArg_byte();
    C_period_1Hz(0);
}

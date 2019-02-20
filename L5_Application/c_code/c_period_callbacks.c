/**
 * @file
 *
 * The purpose of this "C" callbacks is to provide the code to be able
 * to call pure C functions and unit-test it in C test framework
 */
#include <stdint.h>
#include <stdbool.h>
#include "c_uart2.h"
#include "c_uart3.h"
#include<stdio.h>
#include "io.h"
//#include "printf_lib.h"

//--------------------------------Sender-----------------------------------------//
bool C_period_init(void)
{
    return uart2_init(9600,5,5);
    //return uart2_init(9600,5,5);
    
}
bool C_period_reg_tlm(void) {
    return true;
}

void C_period_1Hz(uint32_t count)
{
/*    (void) count;

 static char send_data= '0';
    uart2_putChar(send_data, 0);

   if(send_data=='9')
   {send_data='0';}
   else
   {
       send_data++;
   }*/

   (void) count;
      char receive_data;
      uint8_t var;
      if(uart2_getchar(&receive_data, 0))
      {
          var =receive_data;
          var= (var-48)*10; //converting ascii to decimal and scaling up.
          C_LED_Display(var);
      }



 }

void C_period_10Hz(uint32_t count)
{

  (void) count;
}

void C_period_100Hz(uint32_t count) {
    (void) count;
}

void C_period_1000Hz(uint32_t count) {
    (void) count;
}

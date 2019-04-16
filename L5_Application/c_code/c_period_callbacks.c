/**
 * @file
 *
 * The purpose of this "C" callbacks is to provide the code to be able
 * to call pure C functions and unit-test it in C test framework
 */
#include <stdint.h>
#include <stdbool.h>
//#include "c_uart2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "can.h"
#include "BLE_CAN_Transmit.h"
//--------------------------------Sender-----------------------------------------//
bool C_period_init(void)
{
     uart2_init(9600,5,5);
     init_CAN();
     return true;
}
bool C_period_reg_tlm(void)
{
    return true;
}

void C_period_1Hz(uint32_t count)
{
    check_for_Bussoff();

}
void C_period_10Hz(uint32_t count)
{
  /*(void) count;
  if(count % 5==0)
  {
      BLE_heartbeat();
  }

  can_msg_t msge={0};
  START_STOP_t stsp={0};
  get_BLE_Message();
  send_start_stop_on_CAN(&msge,&stsp);
  //BLE_send();*/
}



   //can_msg_t msge = {0};



void C_period_100Hz(uint32_t count)
{
    (void) count;
      if(count % 50==0)
      {
          BLE_heartbeat();
      }

      can_msg_t msge={0};
      START_STOP_t stsp={0};
      get_BLE_Message();
      send_start_stop_on_CAN(&msge,&stsp);
      //BLE_send();
}

void C_period_1000Hz(uint32_t count)
{
    (void) count;
}










/*
static l=0;
char arr[6]={'\0'};
static char receive;
send_board_to_BLE();
uart2_getchar(&receive,0);
// printf("%c",receive);
if(l<5)
{
    arr[l]=receive;
    printf("%c",arr[l]);
     l++;
}
if(l==5)
{

    l=0;
}
*/

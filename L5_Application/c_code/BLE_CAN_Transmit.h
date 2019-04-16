#ifndef BLE_CAN_TRANSMIT_H_
#define BLE_CAN_TRANSMIT_H_

//---------------
#define PACK_START  '~'
#define LAT_START   '@'
#define LONG_START  '!'
#define PACK_END    '#'
#define TRUE 1
#define FALSE 0
//-----------

#ifdef __cplusplus
extern "C" {
#endif

#include "c_uart2.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "can.h"
#include "_can_dbc/generated_can.h"



typedef  struct{
    char recieve_data;
    char char_arr[30];
    int  char_arr_ptr;
    int valid;
}rx_data_helper_t;

typedef struct
{
    uint8_t start_stop;
    uint8_t prev_strt_stop;
    float BLE_latitude;
    float BLE_longitude;
} mobile_data_t;


void get_BLE_Message(void);
bool init_CAN(void);
void check_for_Bussoff(void);
void BLE_send();
void parse_and_send_data(char* arr,int size);
void send_board_to_BLE();
void send_start_stop_on_CAN(can_msg_t *msge_container, START_STOP_t *sendstsp);
void BLE_heartbeat();


#endif
#ifdef __cplusplus
}
#endif

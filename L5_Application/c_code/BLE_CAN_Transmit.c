#include "BLE_CAN_Transmit.h"
#include <string.h>


mobile_data_t rx_data={0};
rx_data_helper_t helper_data ={0};

void send_start_stop_on_CAN(can_msg_t *msge_container, START_STOP_t *sendstsp)
{
    if(rx_data.prev_strt_stop!=rx_data.start_stop){
    sendstsp->BRIDGE_START_STOP= rx_data.start_stop;
    //printf("%d\n",rx_data.start_stop);
    dbc_msg_hdr_t msge_hdr = dbc_encode_START_STOP(msge_container->data.bytes, sendstsp);
    msge_container->msg_id = msge_hdr.mid;
    msge_container->frame_fields.data_len = msge_hdr.dlc;
    CAN_tx(can1, msge_container, 0);
    }
    rx_data.prev_strt_stop=rx_data.start_stop;
}

void BLE_heartbeat()
{
    can_msg_t msge_container = {0};
    APP_HEARTBEAT_t sendHB={0};
    sendHB.APP_HEARTBEAT_signal= 0xAA;
    dbc_msg_hdr_t msge_hdr = dbc_encode_APP_HEARTBEAT(msge_container.data.bytes,&sendHB);
    msge_container.msg_id = msge_hdr.mid;
    msge_container.frame_fields.data_len = msge_hdr.dlc;
    CAN_tx(can1, &msge_container, 0);
}
void get_BLE_Message(){

    uart2_getchar(&(helper_data.recieve_data),0);

    if(helper_data.recieve_data ==PACK_START ){
        helper_data.valid=TRUE;
    }
    if(helper_data.recieve_data==PACK_END && helper_data.valid)
    {
        helper_data.char_arr[(helper_data.char_arr_ptr)++]=helper_data.recieve_data;
        helper_data.char_arr[helper_data.char_arr_ptr]='\0';
        helper_data.char_arr_ptr=0;
        helper_data.valid=FALSE;
        parse_and_send_data(helper_data.char_arr,(helper_data.char_arr_ptr)-1);

    }
    if(helper_data.valid){
        helper_data.char_arr[(helper_data.char_arr_ptr)++]=helper_data.recieve_data;
    }
}




bool init_CAN(void)
{
    CAN_init(can1, 100, 0, 6, 0, 0);
    CAN_bypass_filter_accept_all_msgs();
    CAN_reset_bus(can1);
    return 1;
}
void check_for_Bussoff(void)
{
    if (CAN_is_bus_off(can1))
    {
        CAN_reset_bus(can1);
    }
}

//can_msg_t *msge_container, BLUETOOTH_LAT_LONG_t *sender
void BLE_send()
{
    can_msg_t msge = {0};
    BLUETOOTH_LAT_LONG_t send={0};
    send.GPS_Latitude = rx_data.BLE_latitude;
    send.GPS_Longitude = rx_data.BLE_longitude;
    dbc_msg_hdr_t msge_hdr = dbc_encode_BLUETOOTH_LAT_LONG(msge.data.bytes,&send);
    msge.msg_id = msge_hdr.mid;
    msge.frame_fields.data_len = msge_hdr.dlc;
    printf("%f\n",rx_data.BLE_latitude);
    CAN_tx(can1, &msge, 0);
}


void parse_and_send_data(char* arr,int size)
{


    //START-data
    char *str_strt_ptr=strchr(arr,PACK_START);
    char *str_end_ptr=strchr(arr,LAT_START);
    int start_bit_size=str_end_ptr - str_strt_ptr;
    char start_stop_data[start_bit_size+1];
    for(char *i=str_strt_ptr+1;i<=str_end_ptr;i++){
        if(i<str_end_ptr){
            start_stop_data[i-(str_strt_ptr+1)]=*i;
        }
        else{
            start_stop_data[i-(str_strt_ptr+1)]='\0';
        }

    }
    rx_data.start_stop=atoi(start_stop_data);
    //Latitude-data
    char *lat_strt_ptr=strchr(arr,LAT_START);
    char *lat_end_ptr=strchr(arr,LONG_START);
    int lat_size=lat_end_ptr-lat_strt_ptr;
    char lat_data[lat_size+1];
    for(char *i=lat_strt_ptr+1;i<=lat_end_ptr;i++){
        if(i<lat_end_ptr){
            lat_data[i-(lat_strt_ptr+1)]=*i;
        }
        else{
            lat_data[i-(lat_strt_ptr+1)]='\0';
        }

    }
    rx_data.BLE_latitude=atof(lat_data);


    //Longitude-Data
    char *long_strt_ptr=strchr(arr,LONG_START);
    char *long_end_ptr=strchr(arr,PACK_END);
    int long_size=long_end_ptr - long_strt_ptr;
    char long_data[long_size+1];
    for(char *i=long_strt_ptr+1;i<=long_end_ptr;i++){
        if(i<long_end_ptr){
            long_data[i-(long_strt_ptr+1)]=*i;
        }
        else{
            long_data[i-(long_strt_ptr+1)]='\0';
        }

    }

    rx_data.BLE_longitude=atof(long_data);
    //  printf("star :%d lat: %f long: %f\n",rx_data.start_stop,rx_data.BLE_latitude,rx_data.BLE_longitude);

}





void send_board_to_BLE()
{
    float received_long=0;
    float received_lat=0;
    can_msg_t msge_container={0};
    GEO_CURRENT_COORD_t receive={0};
    if (CAN_rx(can1, &msge_container, 0))
    {
        dbc_msg_hdr_t msg_hdr;
        msg_hdr.dlc = msge_container.frame_fields.data_len;
        msg_hdr.mid = msge_container.msg_id;
        if(msg_hdr.mid == 214)
        {
            dbc_decode_GEO_CURRENT_COORD(&receive, msge_container.data.bytes, &msg_hdr);
            printf("%f",receive.GEO_CURRENT_COORD_LONG);
            printf("%f",receive.GEO_CURRENT_COORD_LAT);
            received_long = receive.GEO_CURRENT_COORD_LONG;
            received_lat = receive.GEO_CURRENT_COORD_LAT;
        }

    }
    char out_string[30];
    sprintf(out_string, "%f + %f",received_long,received_lat);
    int length = strlen(out_string);
    for(int i =0;i<length;i++)
    {
        uart2_putChar(out_string[i],0);
    }
}


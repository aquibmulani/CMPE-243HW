#include "c_uart2.h"
#include "uart2.hpp"

// Assuming UART2 is already initialized
// You may want to also add uart2_init() in C
bool uart2_init(unsigned int baudRate, int rxQSize=32, int txQSize=64)
{
    Uart2::getInstance().init( baudRate, rxQSize=32, txQSize=64);
return true;
}
bool uart2_getchar(char *byte, uint32_t timeout_ms)
{
    Uart2::getInstance().getChar(byte, timeout_ms);
return true;
}
bool uart2_putChar(char byte, uint32_t timeout_ms)
{
    Uart2::getInstance().putChar(byte, timeout_ms);
return true;
}
/*
bool uart3_getchar(char *byte, uint32_t timeout_ms)
{
    Uart3::getInstance().getChar(byte, timeout_ms);

}
bool uart3_putChar(char byte, uint32_t timeout_ms)
{
    Uart3::getInstance().putChar(byte, timeout_ms);

}
*/



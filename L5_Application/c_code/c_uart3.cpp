#include "c_uart3.h"
#include "uart3.hpp"

// Assuming UART2 is already initialized
// You may want to also add uart2_init() in C
bool uart3_init(unsigned int baudRate, int rxQSize=32, int txQSize=64)
{
    Uart3::getInstance().init( baudRate, rxQSize=32, txQSize=64);
return true;
}
bool uart3_getChar(char *byte, uint32_t timeout_ms)
{
    Uart3::getInstance().getChar(byte, timeout_ms);
    return true;
}
bool uart3_putChar(char byte, uint32_t timeout_ms)
{
    Uart3::getInstance().putChar(byte, timeout_ms);
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



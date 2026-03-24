#ifndef UART_H
#define UART_H

void UART_Init(unsigned int ubrr);
void UART_SendChar(char c);
void UART_SendString(const char *str);

#endif
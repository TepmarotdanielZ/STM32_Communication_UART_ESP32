

#include <Arduino.h>

#define UART_TX_PIN 1  /* TX PIN (NOT USED FOR RECEIVING) */ 
#define UART_RX_PIN 3  /* RX PIN */ 
#define UART_NUM Serial  /* UART INTERFACE */ 

void init_RS232()
{
    UART_NUM.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);  /* INITIALIZE UART */ 
}

void setup()
{
    Serial.begin(115200);  /* INITIALIZE THE DEBUG SERIAL INTERFACE */ 
    Serial.println("RECEIVE DATA:");
    init_RS232(); /* INITIALIZE UART FOR RS232 */ 
}

void loop()
{
    while (UART_NUM.available() > 0)  /* CHECK FOR INCOMING DATA */ 
    {
        char rx_data[128] = {0};  /* BUFFER TO STORE RECEIVED DATA */ 
        int length = UART_NUM.readBytesUntil('\n', rx_data, sizeof(rx_data) - 1);  /* READ UNTIL NEWLINE OR BUFFER FULL */
        if (length > 0)
        {
            rx_data[length] = '\0';  /* NULL-TERMINATE THE STRING */
            Serial.printf("RECEIVED DATA: %s\n", rx_data);  /* PRINT RECEIVED DATA */ 
        }
    }
}



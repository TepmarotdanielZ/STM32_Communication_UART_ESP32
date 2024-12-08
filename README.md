## I. STM32 F01 Communication UART To ESP32

## 1. UART:

## 2. STM32 F401:

  * CONFIGURATION RCC: 

    ![STM32 Communication UART To ESP32](https://github.com/user-attachments/assets/978e0ffc-b4d7-4351-862e-826e1c37dc96)

  * CONFIGURATION SYS:

    ![STM32 Communication UART To ESP32 (1)](https://github.com/user-attachments/assets/c6c4f7ea-2eb9-4e8f-806b-dbe9326c5e38)

  * CONFIGURATION CLOCK:

    ![STM32 Communication UART To ESP32 (2)](https://github.com/user-attachments/assets/e8fc5964-a783-4aec-97bc-7b7c13d53cac)

  * CONFIGURATION UART:

    ![STM32 Communication UART To ESP32 (3)](https://github.com/user-attachments/assets/8a571a04-1c7e-4c0a-aa6a-af57f08068eb)

## 3. CODE STM32:

 * **VARIABLE DECLARATOINS:** 

```cpp
char tx_data[] = "Message from STM32F401 ... \r\n";  
uint32_t previousMillis = 0; /* STORE LAST TRANSMISSION TIME */  
const int interval = 100;    /* INTERVAL FOR SENDING DATA 1 SECOND */
```

 1. **`char tx_data[]`**: This character array holds the string that will be transmitted via UART. The string includes a newline character (`\r\n`) at the end, which is common in serial communication to indicate the end of a message.
 2. **`uint32_t previousMillis`**: This variable is used to store the last time data was transmitted. It is initialized to 0.
 3. **`const int interval`**: This constant defines the time interval (in milliseconds) for sending data. It is set to 100 milliseconds. This means the message will be sent every 100 milliseconds.

 * **MAIN LOOP:**
   * The following code is part of the infinite loop (`while (1)`) that continuously runs after the microcontroller is initialized:

```cpp
while (1)  
{  
    /* USER CODE END WHILE */  

    /* USER CODE BEGIN 3 */  

    /* GET THE CURRENT TICK COUNT */  
    uint32_t currentMillis = HAL_GetTick();
```

   * The `while (1)` loop ensures that the code inside it runs indefinitely. This is typical for embedded systems, where the main function keeps executing to maintain the operation of the device.
   * **`HAL_GetTick()`**: This function retrieves the current tick count in milliseconds since the microcontroller started running. The tick count is usually incremented by a timer interrupt, providing a way to measure elapsed time.

 * **TIME CHECK AND DATA TRANSMISSION:**

   
```cpp
/* CHECK IF IT'S TIME TO SEND DATA */  
if (currentMillis - previousMillis >= interval) {  
    previousMillis = currentMillis; /* SAVE THE LAST TIME WE SEND DATA */  

    /* TRANSMIT THE DATA */  
    if (HAL_UART_Transmit(&huart1, (uint8_t*)tx_data, sizeof(tx_data) - 1, HAL_MAX_DELAY) != HAL_OK) {  
        // Handle error if needed  
    }  
}
```

 **1. TIME CHECK:**
  * The `if (currentMillis - previousMillis >= interval)` condition checks if the time elapsed since the last transmission is greater than or equal to the defined interval (100 milliseconds).
  * If true, it means it's time to send the data again.

 **2. UPDATE **`previousMillis`**:**
  * The line `previousMillis = currentMillis;` updates previousMillis to the current tick count. This ensures that the next time the loop runs, the elapsed time can be calculated correctly.

 **3. TRANSMIT DATA:**
  * HAL_UART_Transmit(): This function is called to transmit the data over UART.
    * **Parameters:**
      * `&huart1`: This is a pointer to the UART handle, which contains the configuration for UART1. It was initialized earlier in the code.
      * `(uint8_t*)tx_data`: This casts the tx_data string to a `uint8_t*` type, which is required by the function.
      * `sizeof(tx_data) - 1`: This specifies the number of bytes to send. The -1 is used to exclude the null terminator (`\0`) at the end of the string, ensuring only the actual message is sent.
      * `HAL_MAX_DELAY`: This parameter tells the function to wait indefinitely for the transmission to complete.

 **4. ERROR HANDLING:**
  * The code checks if `HAL_UART_Transmit()` returns a value other than `HAL_OK`, indicating that there was an error during transmission. Although the error handling is not implemented in this snippet, you could add code here to handle transmission errors (e.g., logging the error, retrying the transmission, etc.).

>[!SUMMARY:]
> In summary, this code snippet is designed to transmit a predefined message over UART every 100 milliseconds. It uses the `HAL_GetTick()` function to track elapsed time and ensure that the message is sent at regular intervals. The use of `HAL_UART_Transmit()` allows for the actual transmission of the message, while basic error checking is in place to catch any transmission issues.

   ![STM32 Communication UART To ESP32 (4)](https://github.com/user-attachments/assets/7f73faf4-990f-4a3f-b805-a679fbbe8686)

## 4. CODE ESP32:

 **1. INCLUDES AND DEFINITIONS:**

 ```cpp
#include <Arduino.h>  

#define UART_TX_PIN 1  /* TX PIN (NOT USED FOR RECEIVING) */   
#define UART_RX_PIN 3  /* RX PIN */   
#define UART_NUM Serial  /* UART INTERFACE */
```

* **`#include <Arduino.h>`**: This line includes the Arduino core library, which is necessary for using the Arduino functions and objects like `Serial`.
* **PIN DEFINITIONS:**
  * `#define UART_TX_PIN 1`: Assigns pin 1 as the TX (transmit) pin, though it is not used for receiving data in this particular code.
  * `#define UART_RX_PIN 3`: Assigns pin 3 as the RX (receive) pin. This pin will be used to receive incoming data.
  * `#define UART_NUM Serial`: This line defines `UART_NUM` as the Serial object, which refers to the main serial interface on most Arduino boards (usually Serial1 on boards with multiple serial ports).


**2. UART INITIALIZATION FUNCTION:**

 ```cpp
void init_RS232()  
{  
    UART_NUM.begin(115200, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);  /* INITIALIZE UART */   
}
```

* `void init_RS232()`: A function that initializes the UART interface.
* `UART_NUM.begin(...)`: This method is called to configure the UART interface with the following parameters:
  * `115200`: The baud rate for communication. This means the data transmission will occur at 115200 bits per second, a common speed for serial communication.
  * `SERIAL_8N1`: This specifies the serial data format, which is 8 data bits, no parity bit, and 1 stop bit.
  * `UART_RX_PIN` and `UART_TX_PIN`: These are the pins used for receiving and transmitting data, respectively.


**3. SETUP FUNCTION:**

 ```cpp
void setup()  
{  
    Serial.begin(115200);  /* INITIALIZE THE DEBUG SERIAL INTERFACE */   
    Serial.println("RECEIVE DATA:");  
    init_RS232(); /* INITIALIZE UART FOR RS232 */   
}
```

* **`void setup()`**: This function is called once when the Arduino board is powered on or reset, and it sets up the initial state.
* **`Serial.begin(115200)`**: Initializes the default debug serial interface (commonly used for debugging) at a baud rate of 115200.
* **`Serial.println("RECEIVE DATA:")`**: Sends a message to the debug console indicating that the program is ready to receive data.
* **`init_RS232()`**: Calls the earlier defined function to initialize the RS232 UART interface.


**4. LOOP FUNCTION:**

 ```cpp
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
```

* **`void loop()`**: This function runs indefinitely after the `setup()` function and contains the main logic for the Arduino program.
* **`while (UART_NUM.available() > 0)`**: This loop checks if there is any incoming data available to read from the UART interface. `UART_NUM.available()` returns the number of bytes available to read.
* **`char rx_data[128] = {0}`**: Declares a character array (buffer) of size 128 to store incoming data. It is initialized to 0 to ensure that all characters are null characters initially.
* **`int length = UART_NUM.readBytesUntil('\n', rx_data, sizeof(rx_data) - 1)`**:
  * This function reads bytes from the `UART_NUM` until it encounters a newline character `('\n')` or until the buffer is full (minus one space for the null terminator).
  * The number of bytes read is stored in the variable `length`.
* **`if (length > 0)`**: Checks if any data was actually read. If `length` is greater than 0, it means some data has been received.
* **`rx_data[length] = '\0'`**: This line null-terminates the string, making it a proper C-string that can be printed or manipulated as needed.
* **`Serial.printf("RECEIVED DATA: %s\n", rx_data)`**:
  * This uses the `printf` function to format and print the received data to the debug serial interface.
  * The `%s` format specifier is used to insert the received string into the output.


>[!SUMMARY:]
> This code snippet is effectively setting up an Arduino program that listens for incoming data via a UART interface configured for RS232 communication. When it receives data, it reads it until a newline is detected or until the buffer fills up, null-terminates the string, and prints the received data to the debug console.

**KEY POINTS:**

* **UART Communication:** Understanding how to set up and use UART for communication is crucial for many embedded projects.
* **Buffer Management:** The use of a buffer to read incoming data is common when working with serial data to ensure the program does not miss any incoming messages.
* **Debugging:** The serial monitor is a valuable tool for debugging and monitoring the output from the Arduino.


   ![STM32 Communication UART To ESP32 (5)](https://github.com/user-attachments/assets/d258b5b6-5927-48fc-95c0-3611d4d72613)

## 5. RESULT UART COMMUNICATION STM32 TO ESP32:

![STM32 Communication UART To ESP32 (6)](https://github.com/user-attachments/assets/10ab11be-b972-4658-b3a2-055b3f8a90c7)


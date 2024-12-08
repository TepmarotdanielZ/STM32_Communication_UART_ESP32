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

 * **Variable Declarations:**

```cpp
char tx_data[] = "Message from STM32F401 ... \r\n";  
uint32_t previousMillis = 0; /* STORE LAST TRANSMISSION TIME */  
const int interval = 100;    /* INTERVAL FOR SENDING DATA 1 SECOND */
```

   ![STM32 Communication UART To ESP32 (4)](https://github.com/user-attachments/assets/7f73faf4-990f-4a3f-b805-a679fbbe8686)

## 4. CODE ESP32:

   ![STM32 Communication UART To ESP32 (5)](https://github.com/user-attachments/assets/d258b5b6-5927-48fc-95c0-3611d4d72613)

## 5. RESULT UART COMMUNICATION STM32 TO ESP32:

![STM32 Communication UART To ESP32 (6)](https://github.com/user-attachments/assets/10ab11be-b972-4658-b3a2-055b3f8a90c7)


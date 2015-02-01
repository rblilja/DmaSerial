# DmaSerial
Serial library utilising DMA on the SAM3X8E MCU (Arduino Due).  

If used with the Arduino IDE, find variant.h and comment out the USARTClass and/or UARTClass objects that you want to replace with DmaSerial objects.

For an instance my variant.h looks like this:

// ----------------------------------------------------------------------------
/*
 * USART objects
 */

//RingBuffer rx_buffer2;
//RingBuffer rx_buffer3;
//RingBuffer rx_buffer4;

//USARTClass Serial1(USART0, USART0_IRQn, ID_USART0, &rx_buffer2);
void serialEvent1() __attribute__((weak));
void serialEvent1() { }
//USARTClass Serial2(USART1, USART1_IRQn, ID_USART1, &rx_buffer3);
void serialEvent2() __attribute__((weak));
void serialEvent2() { }
//USARTClass Serial3(USART3, USART3_IRQn, ID_USART3, &rx_buffer4);
void serialEvent3() __attribute__((weak));
void serialEvent3() { }

// IT handlers
void USART0_Handler(void)
{
  //Serial1.IrqHandler();
}

void USART1_Handler(void)
{
  //Serial2.IrqHandler();
}

void USART3_Handler(void)
{
  //Serial3.IrqHandler();
}

// ----------------------------------------------------------------------------

void serialEventRun(void)
{
  /*
  if (Serial.available()) serialEvent();
  if (Serial1.available()) serialEvent1();
  if (Serial2.available()) serialEvent2();
  if (Serial3.available()) serialEvent3();
  */
}

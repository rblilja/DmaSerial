# DmaSerial
Serial library utilising DMA on the SAM3X8E MCU (Arduino Due).  

If used with the Arduino environment, find the file variant.h and comment out the USARTClass and/or UARTClass objects that you want to replace with DmaSerial objects.

For an instance, if replacing Serial1, you shall comment out the lines containing:

RingBuffer rx_buffer2;

USARTClass Serial1(USART0, USART0_IRQn, ID_USART0, &rx_buffer2);

Serial1.IrqHandler();

if (Serial1.available()) serialEvent1();

Serial1.IrqHandler();

Then you simply instansiate (in the top of your sketch) a DmaSerial object as:

DmaSerial dma_serial1  = DmaSerial((Uart*)USART0, ID_USART0);

Use the put() and get() members to send/retreive data, don't forget to call begin() in the setup.

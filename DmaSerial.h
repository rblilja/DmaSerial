/**
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <robin.lilja@gmail.com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Robin Lilja
 *
 * @see page 519 in ATMEL SAM3X/A datasheet/manual for Peripheral DMA Controller (PDC) usage.  
 *
 * @file DmaSerial.h
 * @author Robin Lilja
 * @date 18 Jan 2015
 */

#ifndef _DMA_SERIAL_H_
#define _DMA_SERIAL_H_

#include "sam.h"				/**< Used for register mapping */

#define MCLK		    (SystemCoreClock)	/**< Used for baud rate calculation */

#define DMA_SERIAL_RX_BUFFER_LENGTH	(128)	/**< Receiver buffer length */
#define DMA_SERIAL_TX_BUFFER_LENGTH 	(128)	/**< Transmit buffer length */

/**
 * DMA based serial communication class.
 */
class DmaSerial {

public:

	/**
	 * Constructor.
	 * @code
	 * DmaSerial((Uart*)USART0, ID_USART0);
	 * @endcode
	 * @param uart pointer to U(S)ART.
	 * @param uart_id id of U(S)ART.
	 */
	DmaSerial(Uart* uart, uint32_t uart_id);

	/**
	 * Initiates the the U(S)ART for DMA.
	 * @todo add support for other than 8N1 setups.
	 * @param baud serial baud rate.
	 */
	void begin(const uint32_t baud);
	
	/**
	 * Check if there are available bytes in the receiver buffer.
	 * @return the number of available bytes.
	 */
	uint8_t available();
	
	/**
	 * Gets bytes from DMA receiving buffer.
	 * @param bytes pointer to beginning of buffer for retrieval. 
	 * @param length number of bytes to be read to retrieval buffer. 
	 * @return the number of retrieved bytes. 
	 */
	uint8_t get(uint8_t* bytes, uint8_t length);
	
	/**
	 * Puts bytes in the DMA transmit buffer.
	 * @param bytes pointer to beginning of buffer containing data to be transmitted.
	 * @param length number of bytes to be transmitted.
	 * @return the number of bytes added to to transmit buffer.
	 */
	uint8_t put(uint8_t* bytes, uint8_t length);
	
	/**
	 * Enable communication.
	 */
	void disable() { uart->UART_PTCR = UART_PTCR_TXTDIS; uart->UART_PTCR = UART_PTCR_RXTDIS; };
	
	/**
	 * Disable communication.
	 */
	void enable() { uart->UART_PTCR = UART_PTCR_TXTEN; uart->UART_PTCR = UART_PTCR_RXTEN; };

private:

	Uart* uart;		/**< Pointer to U(S)ART */
	uint32_t uart_id;	/**< U(SART) id */

	uint8_t tx_buffer[DMA_SERIAL_TX_BUFFER_LENGTH];	/**< Transmit ring buffer */
	
	uint8_t tx_head;	/**< Position were the DMA reads from the ring buffer */
	uint8_t tx_tail;	/**< Position were the user writes to the ring buffer */
	uint8_t tx_count;	/**< Number of bytes stored in the buffer */

	uint8_t rx_buffer[DMA_SERIAL_RX_BUFFER_LENGTH];	/**< Receiver ring buffer */
	
	uint8_t rx_head;	/**< Position were the user reads from the ring buffer */
	uint8_t rx_tail;	/**< Position were the DMA writes to the ring buffer */
	uint8_t rx_count;	/**< Number of available bytes in buffer */
};

#endif /* _DMA_SERIAL_H_ */

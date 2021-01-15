#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL02Z4.h"
#include "fsl_debug_console.h"


#include "sdk_hal_uart0.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */
/*
 * @brief   Application entry point.
 */
int main(void) {
	SIM->SCGC5|=1<<10;// activa señal de reloj
	  	int t=0;
	  	int s=10000000;//control velocidad de colores


    //LED AZUL PIN 10
	PORTB->PCR[10] |= 1 << 8; //activa puertob pin como gpio
	GPIOB->PDDR |= 1 << 10; //configura pin 10 como salida
	GPIOB->PCOR |= 0 << 10; //cambia el valor en el pin
	GPIOB->PTOR |= 1 << 10;

	//LED ROJO PIN 6
	PORTB->PCR[6] |= 1 << 8; //activa puertob pin como gpio
	GPIOB->PDDR |= 1 << 6; //configura pin 10 como salida
	GPIOB->PCOR |= 0 << 6; //cambia el valor en el pin
	GPIOB->PTOR |= 1 << 6;

	//LED VERDE PIN 7
	PORTB->PCR[7] |= 1 << 8; //activa puertob pin como gpio
	GPIOB->PDDR |= 1 << 7; //configura pin 10 como salida
	GPIOB->PCOR |= 0 << 7; //cambia el valor en el pin
	GPIOB->PTOR |= 1 << 7;

	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    (void)uart0Inicializar(115200);

    while(1) {
    	status_t status;
    	uint8_t nuevo_byte;

    	if(uart0NuevosDatosEnBuffer()>0){
    		status=uart0LeerByteDesdeBufferCircular(&nuevo_byte);
    		if(status==kStatus_Success){
    			printf("dato:%c\r\n",nuevo_byte);
				// led rojo PTOR niega el valor actual del pin 6 del puerto B
				if (nuevo_byte == 'R') {
					GPIOB->PTOR = 1 << 6;
				}
				if (nuevo_byte == 'r') {
					GPIOB->PTOR = 1 << 6;
				}
				// led verde PTOR niega el valor actual del pin 7 del puerto B
				if (nuevo_byte == 'G') {
					GPIOB->PTOR = 1 << 7;
				}
				if (nuevo_byte == 'g') {
					GPIOB->PTOR = 1 << 7;
				}
				// led azul PTOR niega el valor actual del pin 10 del puerto B
				if (nuevo_byte == 'B') {
					GPIOB->PTOR = 1 << 10;
				}
				if (nuevo_byte == 'b') {
					GPIOB->PTOR = 1 << 10;
				}

    		}else{
    			printf("error\r\n");
    		}
    	}
    }
    return 0 ;
}

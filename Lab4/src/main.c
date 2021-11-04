#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define BUFFER_SIZE 4 
#define GPIO_PA0_U0RX           0x00000001
#define GPIO_PA1_U0TX           0x00000401
uint8_t buffer[BUFFER_SIZE];
uint8_t buffer_position;
uint8_t lastposition;

void UART_Interruption_Handler(void){
  buffer[buffer_position%BUFFER_SIZE] = (uint8_t)UARTCharGetNonBlocking(UART0_BASE);
  buffer_position++;
  UARTIntClear(UART0_BASE,UARTIntStatus(UART0_BASE,true));
}

int main()
{

  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE,(GPIO_PIN_0|GPIO_PIN_1));
  UARTConfigSetExpClk(UART0_BASE,(uint32_t)120000000,(uint32_t)115200,(UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));
  UARTFIFODisable(UART0_BASE);
  UARTIntEnable(UART0_BASE,UART_INT_RX|UART_INT_RT);
  UARTIntRegister(UART0_BASE,UART_Interruption_Handler);
  
  buffer_position = 0;
  lastposition = 0;
  uint8_t *aux_char;

  while(1){

    if(lastposition!=buffer_position){
      //salve o dado do buffer no auxiliar
      aux_char = &buffer[lastposition%BUFFER_SIZE];

      //Se for maisculo transforma em minusculo
      if(((*aux_char)>=(uint8_t)65)&&((*aux_char)<=(uint8_t)90)){
        *aux_char += 32; 
      }

      if(UARTCharPutNonBlocking(UART0_BASE,buffer[lastposition%BUFFER_SIZE])){
        lastposition++;
      }
    }      
    
  }
}

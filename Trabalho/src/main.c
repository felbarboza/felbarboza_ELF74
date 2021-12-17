
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "tx_api.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "system_TM4C1294.h"
#include "utils/uartstdio.h"
#include "driverlib/systick.h"
//#include "driverlib/interrupt.h"
#include <stdio.h>
//#include <stdlib.h>
//#include <ctype.h>
#include <string.h>
#include <inttypes.h>
#include "driverlib/interrupt.h"


#define BUFFER_SIZE 16
#define DEMO_BYTE_POOL_SIZE     9120
#define DEMO_STACK_SIZE         1024
#define DEMO_QUEUE_SIZE         100

#define GPIO_PA0_U0RX           0x00000001
#define GPIO_PA1_U0TX           0x00000401

uint8_t buffer[BUFFER_SIZE];
uint8_t buffer_position;
uint8_t lastposition;


TX_THREAD               thread_1;
TX_THREAD               thread_2;
TX_THREAD               thread_3;
TX_THREAD               thread_main;
TX_BYTE_POOL            byte_pool_0;
TX_QUEUE                queue_1;
TX_QUEUE                queue_2;
TX_QUEUE                queue_3;
TX_QUEUE                queue_interna_1;
TX_QUEUE                queue_interna_2;
TX_QUEUE                queue_interna_3;
TX_MUTEX                mutex_0;


UCHAR                   byte_pool_memory[DEMO_BYTE_POOL_SIZE];


//void UART0_Handler(void){
 // buffer[buffer_position%BUFFER_SIZE] = (uint8_t)UARTCharGetNonBlocking(UART0_BASE);
  //buffer_position++;
  //UARTIntClear(UART0_BASE,UARTIntStatus(UART0_BASE,true));
//}


//extern void UARTStdioIntHandler(void);

void UARTInit(void){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
  
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  GPIOPinTypeUART(GPIO_PORTA_BASE,(GPIO_PIN_0|GPIO_PIN_1));
  UARTConfigSetExpClk(UART0_BASE,SystemCoreClock,(uint32_t)115200,(UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));
  UARTFIFOEnable(UART0_BASE);
  //UARTIntEnable(UART0_BASE,UART_INT_RX|UART_INT_RT);
  //UARTIntRegister(UART0_BASE,UART0_Handler);
  
  buffer_position = 0;
  lastposition = 0;

} // UARTInit

//void UART0_Handler(void){
//  UART_Interruption_Handler();
//} // UART0_Handler

int main(){
  IntMasterEnable(); 
  SysTickPeriodSet(10000000);  
  SysTickIntEnable();
  SysTickEnable();
  UARTInit();
  
  tx_kernel_enter();
}

void initialize_elevator(char n_elevador ){
  UINT status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
  
  UARTCharPut(UART0_BASE,n_elevador);
  UARTCharPut(UART0_BASE,'r');
  //UARTCharPut(UART0_BASE,'\n');
  UARTCharPut(UART0_BASE,'\r');
  
  UARTCharPut(UART0_BASE,n_elevador);
  UARTCharPut(UART0_BASE,'f');
  //UARTCharPut(UART0_BASE,'\n');
  UARTCharPut(UART0_BASE,'\r');
  //UARTprintf("%cr\n\r", n_elevador);
  //UARTprintf("%cf\n\r", n_elevador);

  status =  tx_mutex_put(&mutex_0);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
}


void open_close_doors(char n_elevador){
  UINT status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;

  
    UARTCharPut(UART0_BASE,n_elevador);
    UARTCharPut(UART0_BASE,'a');
    //UARTCharPut(UART0_BASE,'\n');
    UARTCharPut(UART0_BASE,'\r');


  status =  tx_mutex_put(&mutex_0);
  /* Check status.  */
  if (status != TX_SUCCESS)
      return;


  tx_thread_sleep(1000);


  status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
  
    UARTCharPut(UART0_BASE,n_elevador);
    UARTCharPut(UART0_BASE,'f');
    //UARTCharPut(UART0_BASE,'\n');
    UARTCharPut(UART0_BASE,'\r');

  status =  tx_mutex_put(&mutex_0);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
}

void turn_on_led(char n_elevator, char andar){
  UINT status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
  
  
  UARTCharPut(UART0_BASE,n_elevator);
  UARTCharPut(UART0_BASE,'L');
  UARTCharPut(UART0_BASE,andar);
  //UARTCharPut(UART0_BASE,'\n');
  UARTCharPut(UART0_BASE,'\r');

  status =  tx_mutex_put(&mutex_0);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;

}

void turn_off_led(char n_elevator, char andar){
  UINT status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
  
  
  UARTCharPut(UART0_BASE,n_elevator);
  UARTCharPut(UART0_BASE,'D');
  UARTCharPut(UART0_BASE,andar);
  //UARTCharPut(UART0_BASE,'\n');
  UARTCharPut(UART0_BASE,'\r');

  status =  tx_mutex_put(&mutex_0);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;

}

void move_elevator(char n_elevator, int side){
  UINT status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
  
  if(side==1){
    //printf("\n O elevador %c vai subir", n_elevator);
    
    UARTCharPut(UART0_BASE,n_elevator);
    UARTCharPut(UART0_BASE,'s');
    //UARTCharPut(UART0_BASE,'\n');
    UARTCharPut(UART0_BASE,'\r');
    //UARTprintf("%cs\n\r", n_elevator);
  }
  else{
    UARTCharPut(UART0_BASE,n_elevator);
    UARTCharPut(UART0_BASE,'d');
    //UARTCharPut(UART0_BASE,'\n');
    UARTCharPut(UART0_BASE,'\r');
    
    //UARTprintf("%cd\n\r", n_elevator);
  }

  status =  tx_mutex_put(&mutex_0);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
  
}

void stop_elevator(char n_elevator){
  UINT status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
  
  
    UARTCharPut(UART0_BASE,n_elevator);
    UARTCharPut(UART0_BASE,'p');
    //UARTCharPut(UART0_BASE,'\n');
    UARTCharPut(UART0_BASE,'\r');
  
  status =  tx_mutex_put(&mutex_0);

  /* Check status.  */
  if (status != TX_SUCCESS)
      return;
}

char evaluate_andar(char primeiro, char segundo){
  int floor = (primeiro - '0') * 10 + (segundo - '0');
  
  switch (floor) {
      case 0:
          return 'a';
      case 1:
          return 'b';
      case 2:
          return 'c';
      case 3:
          return 'd';
      case 4:
          return 'e';
      case 5:
          return 'f';
      case 6:
          return 'g';
      case 7:
          return 'h';
      case 8:
          return 'i';
      case 9:
          return 'j';
      case 10:
          return 'k';
      case 11:
          return 'l';
      case 12:
          return 'm';
      case 13:
          return 'n';
      case 14:
          return 'o';
      case 15:
          return 'p';
      default:
          return ' ';
    }
          
}


void elevator_thread_1(ULONG n_elevador){
  char command[16];
  int estado;
  int pos = 0;
  char andar = 'a';
  char comando_atual[16];
  char andar_destino= 'a';
  UINT status;
  int tamanho = 0;
  int acao = -1;
  
  initialize_elevator('e');
  
  while(1){
    memset(command, 0, sizeof command);
    status = tx_queue_receive(&queue_1, command, TX_WAIT_FOREVER);  
    if (status != TX_SUCCESS)
            break;
    //printf("esq: %c%c%c%c%c", command[0], command[1], command[2], command[3], command[4]);
    
    if(command[1]>=48 && command[1]<=57)
    {
      if(command[2]>=48 && command[2]<=57){
        andar = evaluate_andar(command[1], command[2]);
      }else{
        andar = evaluate_andar('0', command[1]);
      }
    }
    if(command[1]=='E' || command[1]=='I'){
      tamanho ++;
      if(command[1]=='I'){
        turn_on_led('e', command[2]);
      }
      status = tx_queue_send(&queue_interna_1, command, TX_WAIT_FOREVER);
      if (status != TX_SUCCESS)
          break;
    }
    if(tamanho>0 && strlen(comando_atual)==0){
      status = tx_queue_receive(&queue_interna_1, comando_atual, TX_WAIT_FOREVER);  
      if (status != TX_SUCCESS)
              break;
    }

    if(comando_atual[1]=='E'){
      andar_destino  = evaluate_andar(comando_atual[2], comando_atual[3]);
    }
    else if(comando_atual[1]=='I'){
      andar_destino = comando_atual[2];
    }
    if(andar_destino>andar && acao==-1){
      move_elevator('e', 1);
      acao=1;
    }
    else if(andar_destino<andar && acao==-1){
      move_elevator('e', -1);
      acao=1;
    }
    if(andar_destino == andar && strlen(comando_atual)!=0){
      stop_elevator('e');
      open_close_doors('e');
      turn_off_led('e', andar_destino);
      tamanho--;
      memset(comando_atual, 0, sizeof comando_atual);
      acao=-1;
    }
  }

}

void elevator_thread_2(ULONG n_elevador){
  char command[16];
  int estado;
  int pos = 0;
  char andar = 'a';
  char comando_atual[16];
  char andar_destino='a';
  UINT status;
  int tamanho = 0;
  int acao = -1;
  
  initialize_elevator('c');
  
  while(1){
    memset(command, 0, sizeof command);
    status = tx_queue_receive(&queue_2, command, TX_WAIT_FOREVER);  
    if (status != TX_SUCCESS)
            break;
    
    //printf("cen: %c%c%c%c%c", command[0], command[1], command[2], command[3], command[4]);
    
    if(command[1]>=48 && command[1]<=57)
    {
      if(command[2]>=48 && command[2]<=57){
        andar = evaluate_andar(command[1], command[2]);
      }else{
        andar = evaluate_andar('0', command[1]);
      }
    }
    if(command[1]=='E' || command[1]=='I'){
      tamanho ++;
      if(command[1]=='I'){
        turn_on_led('c', command[2]);
      }
      status = tx_queue_send(&queue_interna_2, command, TX_WAIT_FOREVER);
        if (status != TX_SUCCESS)
            break;
    }
    if(tamanho>0 && strlen(comando_atual)==0){
      status = tx_queue_receive(&queue_interna_2, comando_atual, TX_WAIT_FOREVER);  
      if (status != TX_SUCCESS)
              break;
    }

    if(comando_atual[1]=='E'){
      andar_destino  = evaluate_andar(comando_atual[2], comando_atual[3]);
    }
    else if(comando_atual[1]=='I'){
      andar_destino = comando_atual[2];
    }
    if(andar_destino>andar && acao==-1){
      move_elevator('c', 1);
      acao=1;
    }
    else if(andar_destino<andar && acao==-1){
      move_elevator('c', -1);
      acao=1;
    }
    if(andar_destino == andar && strlen(comando_atual)!=0){
      stop_elevator('c');
      open_close_doors('c');
      turn_off_led('c', andar_destino);
      tamanho--;
      memset(comando_atual, 0, sizeof comando_atual);
      acao=-1;
    }
  }
}

void elevator_thread_3(ULONG n_elevador){
  char command[16];
  int estado;
  int pos = 0;
  char andar = 'a';
  char comando_atual[16];
  char andar_destino ='a';
  UINT status;
  int tamanho = 0;
  int acao = -1;
  
  initialize_elevator('d');
  
  while(1){
    memset(command, 0, sizeof command);
    status = tx_queue_receive(&queue_3, command, TX_WAIT_FOREVER);  
    if (status != TX_SUCCESS)
            break;
    
    //printf("dir: %c%c%c%c%c", command[0], command[1], command[2], command[3], command[4]);
    
    if(command[1]>=48 && command[1]<=57)
    {
      if(command[2]>=48 && command[2]<=57){
        andar = evaluate_andar(command[1], command[2]);
      }else{
        andar = evaluate_andar('0', command[1]);
      }
    }
    if(command[1]=='E' || command[1]=='I'){
      if(command[1]=='I'){
        turn_on_led('d', command[2]);
      }
      tamanho ++;
      status = tx_queue_send(&queue_interna_3, command, TX_WAIT_FOREVER);
        if (status != TX_SUCCESS)
            break;
    }
    if(tamanho>0 && strlen(comando_atual)==0){
      status = tx_queue_receive(&queue_interna_3, comando_atual, TX_WAIT_FOREVER);  
      if (status != TX_SUCCESS)
              break;
    }

    if(comando_atual[1]=='E'){
      andar_destino  = evaluate_andar(comando_atual[2], comando_atual[3]);
    }
    else if(comando_atual[1]=='I'){
      andar_destino = comando_atual[2];
    }
    if(andar_destino>andar && acao==-1){
      move_elevator('d', 1);
      acao=1;
    }
    else if(andar_destino<andar && acao==-1){
      move_elevator('d', -1);
      acao=1;
    }
    if(andar_destino == andar && strlen(comando_atual)!=0){
      stop_elevator('d');
      open_close_doors('d');
      turn_off_led('d', andar_destino);
      tamanho--;
      memset(comando_atual, 0, sizeof comando_atual);
      acao=-1;
    }
  }

}

void main_thread(ULONG msg){
  
  char buffer_interno[16];
  UINT status;
  int pos=0;
  int acabou_entrada = -1;
  char aux_char;
  while(1){
      
     while(UARTCharsAvail(UART0_BASE)){
      tx_thread_sleep(3);
       //buffer_position++;
      //salve o dado do buffer no auxiliar
      aux_char = UARTCharGet(UART0_BASE);
      //aux_char = &buffer[lastposition%BUFFER_SIZE];
      if(aux_char!='\n' && aux_char!='\r'){
      //if((*aux_char)!=(uint8_t)'\n' && (*aux_char)!=(uint8_t)'\r'){
       buffer_interno[pos] = aux_char;
       pos++;
        //lastposition++;
        //buffer_position++;
        if(aux_char=='F'){
          memset(buffer_interno, 0, sizeof buffer_interno);
          pos=0;
        }
      }
       
      
      else{
        pos=0;
        acabou_entrada=1;
        }
     }
      //if(UARTCharPutNonBlocking(UART0_BASE,buffer[lastposition%BUFFER_SIZE])){
       // lastposition++;
      //}
      
      
      //UARTgets(buffer,16);
      
      //printf("%c%c%c%c%c%c \n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5]);
      if(acabou_entrada){
        if(buffer_interno[0]=='e'){
          status = tx_queue_send(&queue_1, buffer_interno, TX_WAIT_FOREVER);
          if (status != TX_SUCCESS)
              break;
        }
        if(buffer_interno[0]=='c'){
          status = tx_queue_send(&queue_2, buffer_interno, TX_WAIT_FOREVER);
          if (status != TX_SUCCESS)
              break;
        }
        if(buffer_interno[0]=='d'){
          status = tx_queue_send(&queue_3, buffer_interno, TX_WAIT_FOREVER);
          if (status != TX_SUCCESS)
              break;
        }
        memset(buffer_interno, 0, sizeof buffer_interno);
        acabou_entrada=-1;
      }
    }
  }
//}


void    tx_application_define(void *first_unused_memory)
{

    CHAR    *pointer;


#ifdef TX_ENABLE_EVENT_TRACE
    tx_trace_enable(trace_buffer, sizeof(trace_buffer), 32);
#endif
    
    tx_byte_pool_create(&byte_pool_0, "byte pool 0", byte_pool_memory, DEMO_BYTE_POOL_SIZE);


    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&thread_1, "thread 1", elevator_thread_1, 1,  
            pointer, DEMO_STACK_SIZE, 
            0, 0, 20, TX_AUTO_START);

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&thread_2, "thread 2", elevator_thread_2, 2,  
            pointer, DEMO_STACK_SIZE, 
            0, 0, 20, TX_AUTO_START);

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&thread_3, "thread 3", elevator_thread_3, 3,  
            pointer, DEMO_STACK_SIZE, 
            0, 0, 20, TX_AUTO_START);

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&thread_main, "thread main", main_thread, 1,  
            pointer, DEMO_STACK_SIZE, 
            0, 0, 20, TX_AUTO_START);


    tx_mutex_create(&mutex_0, "mutex 0", TX_NO_INHERIT);

    
    //one queue for each elevator
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_QUEUE_SIZE*sizeof(ULONG), TX_NO_WAIT);
    tx_queue_create(&queue_1, "queue 1", TX_1_ULONG, pointer, DEMO_QUEUE_SIZE*sizeof(ULONG));

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_QUEUE_SIZE*sizeof(ULONG), TX_NO_WAIT);
    tx_queue_create(&queue_2, "queue 2", TX_1_ULONG, pointer, DEMO_QUEUE_SIZE*sizeof(ULONG));

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_QUEUE_SIZE*sizeof(ULONG), TX_NO_WAIT);
    tx_queue_create(&queue_3, "queue 3", TX_1_ULONG, pointer, DEMO_QUEUE_SIZE*sizeof(ULONG));
    
    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_QUEUE_SIZE*sizeof(ULONG), TX_NO_WAIT);
    tx_queue_create(&queue_interna_1, "queue interna 1", TX_1_ULONG, pointer, DEMO_QUEUE_SIZE*sizeof(ULONG));

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_QUEUE_SIZE*sizeof(ULONG), TX_NO_WAIT);
    tx_queue_create(&queue_interna_2, "queue interna 2", TX_1_ULONG, pointer, DEMO_QUEUE_SIZE*sizeof(ULONG));

    tx_byte_allocate(&byte_pool_0, (VOID **) &pointer, DEMO_QUEUE_SIZE*sizeof(ULONG), TX_NO_WAIT);
    tx_queue_create(&queue_interna_3, "queue interna 3", TX_1_ULONG, pointer, DEMO_QUEUE_SIZE*sizeof(ULONG));

    tx_block_release(pointer);
}

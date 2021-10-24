 
 
THUMB

  PUBLIC EightBitHistogram
  SECTION .text: CODE
  
  
ZeraHistograma
 
  STR R8, [R3], #2
  ADD R7, #1
  CMP R7, #256
  
  BNE ZeraHistograma
  
  BX LR
   
    
PreencheHistograma
  MOV R3, R9
  LDRB R8, [R2], #1
  ADD R8, R8
  
  LDR R10, [R3, R8]
  ADD R3, R8
  ADD R10, #1
  STR R10, [R3]
  
  ADD R7, #1
  CMP R7, R6
  
  BNE PreencheHistograma
  BX LR
 
EightBitHistogram
    MUL R6, R0, R1 
    MOV R9, R3
    
    CMP R6, #65536
    ITT GT
      MOVGT R0, #0
      BXGT LR
      
    MOV R7, #0
    MOV R8, #0
    PUSH {LR}
    BL ZeraHistograma
    POP {LR}
    
    MOV R7, #0
    PUSH {LR}
    BL PreencheHistograma
    POP {LR}
    
    MOV R0, R6
      
    BX LR
	
  END
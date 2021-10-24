 
 
THUMB

  PUBLIC EightBitHistogram
  SECTION .text: CODE
  
  
ZeraHistograma
 ; Vai pegando os valores de 2 em 2 bytes e colocando 0 at� chegar no final do vetor
  STR R8, [R3], #2
  ADD R7, #1
  CMP R7, #256
  
  BNE ZeraHistograma
  
  BX LR
   
    
    
    
    
PreencheHistograma

;Pega a posi��o inicial do vetor que esta em R9
  MOV R3, R9
 
;L� o valor atual da imagem e aumenta R2 = R2 +1 para avan�ar um pixel
  LDRB R8, [R2], #1
;Dobra o valor de R8, pois o vetor do histograma est� de 16 em 16 bits, e n�o 8
  ADD R8, R8
  
;L� o valor atual na posi��o do vetor e adiciona um
  LDR R10, [R3, R8]
  ADD R10, #1
  
;Incrementa a posi��o do vetor no n�mero do pixel correspondente e guarda o valor atualizado
  ADD R3, R8
  STR R10, [R3]
  
;Adiciona 1 em R7 e compara se chegou no final da imagem (R6)
  ADD R7, #1
  CMP R7, R6
  
  BNE PreencheHistograma
  BX LR
 
 
 
 
EightBitHistogram
;Guarda em R6 o tamanho da imagen
    MUL R6, R0, R1 
;Guarda em R9 a posi��o inicial da imagem
    MOV R9, R3
    
;Compara se a imagem � maior do que 64k e se for retorna 0
    CMP R6, #65536
    ITT GT
      MOVGT R0, #0
      BXGT LR
      
;Prepara os registradores e zera o vetor
    MOV R7, #0
    MOV R8, #0
    PUSH {LR}
    BL ZeraHistograma
    POP {LR}
    
;Zera o R7 e preenche o vetor
    MOV R7, #0
    PUSH {LR}
    BL PreencheHistograma
    POP {LR}
    
;Guarda o tamanho da imagem em R0 e retorna
    MOV R0, R6
      
    BX LR
	
  END
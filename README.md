# felbarboza_ELF74

Lab 1 - O "Hello World" aparece no terminal I/O

Lab 2 - Variáveis volatile: São declaradas assim para sinalizar ao compilador que ele não deve otimizar nada relacionado a essa variável, para facilitar o acesso a hardware, mapeamento de memória de I/O e uso de threads.


Lab 5 -

| Thread Name |    entry function    | stack size | priority | auto start | time slicing |
|:-----------:|:--------------------:|:----------:|----------|------------|--------------|
|   thread 0  |    thread_0_entry    |    1024    |     1    |     yes    |      no      |
|   thread 1  |    thread_1_entry    |    1024    |    16    |     yes    |       4      |
|   thread 2  |    thread_2_entry    |    1024    |    16    |     yes    |       4      |
|   thread 3  | thread_3_and_4_entry |    1024    |     8    |     yes    |      no      |
|   thread 4  | thread_3_and_4_entry |    1024    |     8    |     yes    |      no      |
|   thread 5  |    thread_5_entry    |    1024    |     4    |     yes    |      no      |
|   thread 6  | thread_6_and_7_entry |    1024    |     8    |     yes    |      no      |
|   thread 7  | thread_6_and_7_entry |    1024    |     8    |     yes    |      no      |


|      Name     | control structure |             size             |     location     |
|:-------------:|:-----------------:|:----------------------------:|:----------------:|
|  byte pool 0  |    byte_pool_0    |             9120             | byte_pool_memory |
|    queue 0    |      queue_0      |       100*sizeof(ULONG)      |      pointer     |
|  semaphore 0  |    semaphore_0    |     sizeof(TX_SEMAPHORE)     |   &semaphore_0   |
| event flags 0 |   event_flags_0   | sizeof(TX_EVENT_FLAGS_GROUP) |  &event_flags_0  |
|    mutex 0    |      mutex_0      |       sizeof(TX_MUTEX)       |     &mutex_0     |
|  block pool 0 |    block_pool_0   |              100             |      pointer     |



![Diagrama](./diagrama.png)
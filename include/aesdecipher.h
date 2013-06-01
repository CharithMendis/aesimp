 #ifndef DECIPHER
 #define DECIPHER
 
 #include "aeskeyex.h"
 #include "aescipher.h"
 
 void decipher(memblock_t * input,memblock_t * output,uint32 * word,uint32 nb,uint32 nr);
 
 #endif
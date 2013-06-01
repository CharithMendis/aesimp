#ifndef CIPHER
#define CIPHER

#include "aeskeyex.h"
 
 typedef struct memblock{
	unsigned char * mem;
	unsigned int size;
} memblock_t;

 void cipher(memblock_t * input,memblock_t * output,uint32 * word,uint32 nb,uint32 nr);
 
 void transpose(unsigned char * state,uint32 nb);
 void addRoundKey(unsigned char * state,uint32 * word,uint32 round,uint32 nb);
 void printState(unsigned char * state,uint32 nb);
 
#endif
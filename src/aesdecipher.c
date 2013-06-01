#include <stdio.h>
#include "aesdecipher.h"
#include "aessub.h"
#include "aeshelper.h"

 void decipher_block(unsigned char * state,uint32 * word,uint32 nb,uint32 nr){
 
	addRoundKey(state,word,nr,nb);
	
	int round;
	for(round = nr-1;round >= 1 ;round--){
		shiftRows(state,nb,1);
		subBytes(state,nb,inv_s_box);
		addRoundKey(state,word,round,nb);
		mixColumns(state,nb,invGmix_columnTable);
		
	}
	
	shiftRows(state,nb,1);
	subBytes(state,nb,inv_s_box);
	addRoundKey(state,word,round,nb);
	
	printState(state,nb);
	

 }
 
 //the main should give space for the output already allocated - no support for blocks having lengths not multiples of 128 bits
 //simple chaining mode is presented
 void decipher(memblock_t * input,memblock_t * output,uint32 * word,uint32 nb,uint32 nr){
	
	unsigned int blockSize = 4*nb;
	unsigned int noOfBlocks = (input->size)/blockSize;
	int i=0;
	for(i=0;i<noOfBlocks;i++){
		unsigned char * state = (unsigned char *)malloc(blockSize);
		memcpy(state,(input->mem) + i*blockSize,blockSize); 
		decipher_block(state,word,nb,nr);
		transpose(state,nb);
		memcpy((output->mem) + i*blockSize,state,blockSize);
		free(state);
	}
	
 }
 

 
 
 
 
 
 
 
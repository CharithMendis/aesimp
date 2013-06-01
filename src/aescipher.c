 #include "aescipher.h"
 #include "aeshelper.h"
 #include "aessub.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 
 void cipher_block(unsigned char * state,uint32 * word,uint32 nb,uint32 nr){
 
	addRoundKey(state,word,0,nb);
	
	int round;
	for(round = 1;round < nr;round++){
		subBytes(state,nb,s_box);
		shiftRows(state,nb,0);
		mixColumns(state,nb,gmix_columnTable);
		addRoundKey(state,word,round,nb);
	}
	
	subBytes(state,nb,s_box);
	shiftRows(state,nb,0);
	addRoundKey(state,word,round,nb);
	
	printState(state,nb);
	

 }
 
 //the main should give space for the output already allocated - no support for blocks having lengths not multiples of 128 bits
 //simple chaning mode is presented
 void cipher(memblock_t * input,memblock_t * output,uint32 * word,uint32 nb,uint32 nr){
	
	unsigned int blockSize = 4*nb;
	unsigned int noOfBlocks = (input->size)/blockSize;
	int i=0;
	for(i=0;i<noOfBlocks;i++){
		unsigned char * state = (unsigned char *)malloc(blockSize);
		memcpy(state,(input->mem) + i*blockSize,blockSize); 
		transpose(state,nb);
		printState(state,nb);
		cipher_block(state,word,nb,nr);
		memcpy((output->mem) + i*blockSize,state,blockSize);
		free(state);
	}
	
 }
 

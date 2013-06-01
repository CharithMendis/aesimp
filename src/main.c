#include <stdio.h>
#include <stdlib.h>
#include "aeskeyex.h"
#include "aescipher.h"

keycontext_t * initializeKey(){
	
	//we should make the key here
	unsigned int nk = 4;
	
	uint32 * key = (uint32 *)malloc(sizeof(uint32)*nk);
	key[0] = 0x2b7e1516;
	key[1] = 0x28aed2a6;
	key[2] = 0xabf71588;
	key[3] = 0x09cf4f3c;
	
	keycontext_t * keycon = (keycontext_t *)malloc(sizeof(keycontext_t));
	
	if(keycon == NULL){
		return keycon;
	}
	
	keycon->nk = nk;
	keycon->key = key;

	return keycon;
	
}

uint32 getNumberOfRounds(uint32 nk){
	switch(nk){
		case 4: return 10;
		case 5: return 12;
		case 6: return 14;
		default: return 0;
	}
}

void checkSuccess(void * val){
	if(val == NULL){
		printf("out of memory\n");
		exit(1);
	}
}

memblock_t * prepareInput(char * filename){

	if(filename == NULL){   //if no input file is given - get the sample input
		//32 43 f6 a8 88 5a 30 8d 31 31 98 a2 e0 37 07 34
		memblock_t * input = (memblock_t *)malloc(sizeof(memblock_t));
		unsigned char sampleSize = 16;
		unsigned char * mem = (unsigned char *)malloc(sizeof(unsigned char)*sampleSize);
		//enter the values manually
		mem[0] = 0x32;
		mem[1] = 0x43;
		mem[2] = 0xf6;
		mem[3] = 0xa8;
		mem[4] = 0x88;
		mem[5] = 0x5a;
		mem[6] = 0x30;
		mem[7] = 0x8d;
		mem[8] = 0x31;
		mem[9] = 0x31;
		mem[10] = 0x98;
		mem[11] = 0xa2;
		mem[12] = 0xe0;
		mem[13] = 0x37;
		mem[14] = 0x07;
		mem[15] = 0x34;
		
		input->mem = mem;
		input->size = sampleSize;
		
		return input;
	}
	else{
		//not implemented yet
	}
	

}

memblock_t * prepareOutput(memblock_t * input){

	memblock_t * output = (memblock_t *)malloc(sizeof(memblock_t));
	unsigned char * mem = (unsigned char *)malloc(sizeof(unsigned char)*(input->size));
	output->size = input->size;
	output->mem = mem;
	return output;
	
}


int main(){

	//make the key and expand it
	keycontext_t * keycon = initializeKey();
	checkSuccess(keycon);
	
	unsigned int nb = 4;
	unsigned int nr = getNumberOfRounds(keycon->nk); 
	uint32 * word = keyExpand(keycon,nr,nb);
	checkSuccess(word);

	memblock_t * input = prepareInput(NULL);
	memblock_t * output = prepareOutput(input);

	cipher(input,output,word,nb,nr);

	//cleaning up
	free(input);
	free(output);
	free(keycon);
	free(word);
	
	return 0;  
}

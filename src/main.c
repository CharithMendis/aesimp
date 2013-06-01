#include <stdio.h>
#include <stdlib.h>
#include "aeskeyex.h"


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


int main(){

	//make the key and expand it
	keycontext_t * keycon = initializeKey();
	checkSuccess(keycon);
	
	unsigned int nb = 4;
	unsigned int nr = getNumberOfRounds(keycon->nk); 
	uint32 * word = keyExpand(keycon,nr,nb);
	checkSuccess(word);
	
	
	//cleaning up
	free(keycon);
	free(word);
	
	return 0;  
}

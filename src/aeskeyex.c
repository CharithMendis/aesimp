#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "aeskeyex.h"
#include "aessub.h"

#define LEFTROT(x,base,i) (( x << i) | (x >> (base - i)))
#define RotWord(x) LEFTROT(x,32,8)

//#define DEBUG

uint32 Rcon(const unsigned int x){

	return ((uint32)getRcon(x))<<24;
	 
}

uint32 * keyExpand(keycontext_t * keycon,const uint32 nr,const uint32 nb){
    
	uint32 * word = (uint32 *)malloc(sizeof(uint32)*nb*(nr+1));
	
	//not enough memory
	if(word == NULL){
		return word;
	}
	
	unsigned int i=0;
	
	//for first nk words copy the key value
	for(i=0;i<keycon->nk;i++){
		word[i] = keycon->key[i];
	}
	
	i = keycon->nk;
	
	while(i <  nb * (nr + 1)){
		uint32 temp = word[i-1];
		if( i % keycon->nk == 0){
		
			#ifdef DEBUG
				printf("RotWord %x\n",RotWord(temp));
				printf("SubWord %x\n",subBox(RotWord(temp)));
				printf("Rcon %x\n",Rcon(i/keycon->nk));
			#endif
		
			temp = subBox(RotWord(temp)) ^ Rcon(i/keycon->nk);
		}
		else if( keycon->nk > 6 && i % keycon->nk ==4){
			temp = subBox(temp);
		}
		
		word[i] = word[i - keycon->nk] ^ temp;
		i++;
	}
	
	
	#ifdef DEBUG
	for(i=0;i<nb*(nr+1);i++){
		printf("%x\n",word[i]);
	}
	#endif
	
	return word;
}


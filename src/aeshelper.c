//aeshelper functions - for both cipher and decipher 

 #include "aeshelper.h"
 #include "aessub.h"
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 
  
 //sub parts
 void addRoundKey(unsigned char * state,uint32 * word,uint32 round,uint32 nb){
 
	int i=0;
	int j=0;
	for(i=0;i<nb;i++){    //col
		uint32 currentWord = word[round*nb + i];
		for(j=0;j<4;j++){   //row
			unsigned char temp = currentWord >> (24 - 8*j);
			state[nb*j + i] ^= temp;
		}
	}
 
 }
 
 void subBytes(unsigned char * state,uint32 nb,unsigned char * whatSbox){
 
	int i=0;
	int j=0;
	
	for(i=0;i<nb;i++){   //col
		for(j=0;j<4;j++){  //row
			state[nb*j + i] = whatSbox[state[nb*j + i]];
		}
	}
 
 }
 
 
void shiftSingle(unsigned char * row,uint32 nb,int amount,char inv){

	//make a copy
	unsigned char * rowcpy = (unsigned char *)malloc(nb);
	memcpy(rowcpy,row,nb);

	int i=0;
	for(i=0;i<nb;i++){
		if(!inv){
			row[(i-amount)%nb] = rowcpy[i];
		}
		else{
			row[(i+amount)%nb] = rowcpy[i];
		}
	}
	
	free(rowcpy);

}
 
 
 void shiftRows(unsigned char * state,uint32 nb,char inv){
 
	int i=0;
	int j=0;

	for(j=0;j<4;j++){  //row
		shiftSingle(&state[nb*j],nb,j,inv); 
	}

 }
 

void gmix_columnTable(unsigned char *r){
	unsigned char c[4];
	memcpy(c,r,4);
	
	r[0] = table_2[c[0]] ^ table_3[c[1]] ^ c[2] ^ c[3];
	r[1] = c[0] ^ table_2[c[1]] ^ table_3[c[2]] ^ c[3];
	r[2] = c[0] ^ c[1] ^ table_2[c[2]] ^ table_3[c[3]];
	r[3] = table_3[c[0]] ^ c[1] ^ c[2] ^ table_2[c[3]];

}

 void invGmix_columnTable(unsigned char *r){
	unsigned char c[4];
	memcpy(c,r,4);
	
	r[0] = table_14[c[0]] ^ table_11[c[1]] ^ table_13[c[2]] ^ table_9[c[3]];
	r[1] = table_9[c[0]] ^ table_14[c[1]] ^ table_11[c[2]] ^ table_13[c[3]];
	r[2] = table_13[c[0]] ^ table_9[c[1]] ^ table_14[c[2]] ^ table_11[c[3]];
	r[3] = table_11[c[0]] ^ table_13[c[1]] ^ table_9[c[2]] ^ table_14[c[3]];

}
 
 void mixColumns(unsigned char * state,uint32 nb,void (*func)(unsigned char *)){
	
	int i=0;
	int j=0;
	
	for(i=0;i<nb;i++){
		//extract column
		unsigned char col[4];
		for(j=0;j<4;j++){
			col[j] = state[nb*j + i];
		}
		(*func)(col);
		for(j=0;j<4;j++){
			state[nb*j + i] = col[j];
		}
		
	}
	
 }
 
 void printState(unsigned char * state,uint32 nb){
	
	int i=0;
	int j=0;
	
	for(i=0;i<4;i++){
		for(j=0;j<nb;j++){
			printf("%x ",state[nb*i + j]);
		}
		printf("\n");
	}
	printf("\n");
 
 }
 
 
 void transpose(unsigned char * state,uint32 nb){
	unsigned char * cpy = (unsigned char *)malloc(4*nb);
	memcpy(cpy,state,4*nb);
	
	int i=0;
	int j=0;
	
	for(i=0;i<4;i++){
		for(j=0;j<nb;j++){
			state[i*nb + j] = cpy[j*nb + i];
		}
	}
	
	free(cpy);
	
	
 }
 
 

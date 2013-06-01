#include <stdio.h>
#include "aesdecipher.h"
#include "aeskeyex.h"
#include "aessub.h"
#include "aescipher.h"

void invShiftSingle(unsigned char * row,uint32 nb,int amount){

	//make a copy
	unsigned char * rowcpy = (unsigned char *)malloc(nb);
	memcpy(rowcpy,row,nb);

	int i=0;
	for(i=0;i<nb;i++){
		row[(i+amount)%nb] = rowcpy[i];
	}
	
	free(rowcpy);

}
 
 
 void invShiftRows(unsigned char * state,uint32 nb){
 
	int i=0;
	int j=0;

	for(j=0;j<4;j++){  //row
		invShiftSingle(&state[nb*j],nb,j); 
	}

 }
 
 
  void invSubBytes(unsigned char * state,uint32 nb){
 
	int i=0;
	int j=0;
	
	for(i=0;i<nb;i++){   //col
		for(j=0;j<4;j++){  //row
			state[nb*j + i] = inv_s_box[state[nb*j + i]];
		}
	}
 
 }
 
 void invGmix_columnTable(unsigned char *r){
	unsigned char c[4];
	memcpy(c,r,4);
	
	r[0] = table_14[c[0]] ^ table_11[c[1]] ^ table_13[c[2]] ^ table_9[c[3]];
	r[1] = table_9[c[0]] ^ table_14[c[1]] ^ table_11[c[2]] ^ table_13[c[3]];
	r[2] = table_13[c[0]] ^ table_9[c[1]] ^ table_14[c[2]] ^ table_11[c[3]];
	r[3] = table_11[c[0]] ^ table_13[c[1]] ^ table_9[c[2]] ^ table_14[c[3]];

}
 
 void invMixColumns(unsigned char * state,uint32 nb){
	
	int i=0;
	int j=0;
	
	for(i=0;i<nb;i++){
		//extract column
		unsigned char col[4];
		for(j=0;j<4;j++){
			col[j] = state[nb*j + i];
		}
		invGmix_columnTable(col);
		for(j=0;j<4;j++){
			state[nb*j + i] = col[j];
		}
		
	}
	
 }
 
 
 
 
 
 
 
 
 
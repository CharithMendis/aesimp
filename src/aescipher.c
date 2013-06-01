 #include "aescipher.h"
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
 
 void subBytes(unsigned char * state,uint32 nb){
 
	int i=0;
	int j=0;
	
	for(i=0;i<nb;i++){   //col
		for(j=0;j<4;j++){  //row
			state[nb*j + i] = subBox8(state[nb*j + i]);
		}
	}
 
 }
 
 
void shiftSingle(unsigned char * row,uint32 nb,int amount){

	//make a copy
	unsigned char * rowcpy = (unsigned char *)malloc(nb);
	memcpy(rowcpy,row,nb);

	int i=0;
	for(i=0;i<nb;i++){
		row[(i-amount)%nb] = rowcpy[i];
	}
	
	free(rowcpy);

}
 
 
 void shiftRows(unsigned char * state,uint32 nb){
 
	int i=0;
	int j=0;

	for(j=0;j<4;j++){  //row
		shiftSingle(&state[nb*j],nb,j); 
	}

 }
 
 //from wikipedia
void gmix_column(unsigned char *r) {
        unsigned char a[4];
        unsigned char b[4];
        unsigned char c;
        unsigned char h;
        /* The array 'a' is simply a copy of the input array 'r'
         * The array 'b' is each element of the array 'a' multiplied by 2
         * in Rijndael's Galois field
         * a[n] ^ b[n] is element n multiplied by 3 in Rijndael's Galois field */ 
        for(c=0;c<4;c++) {
                a[c] = r[c];
                /* h is 0xff if the high bit of r[c] is set, 0 otherwise */
                h = (unsigned char)((signed char)r[c] >> 7); /* arithmetic right shift, thus shifting in either zeros or ones */
                b[c] = r[c] << 1; /* implicitly removes high bit because b[c] is an 8-bit char, so we xor by 0x1b and not 0x11b in the next line */
                b[c] ^= 0x1B & h; /* Rijndael's Galois field */
        }
        r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; /* 2 * a0 + a3 + a2 + 3 * a1 */
        r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
        r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
        r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */
}

void gmix_columnTable(unsigned char *r){
	unsigned char c[4];
	memcpy(c,r,4);
	
	r[0] = table_2[c[0]] ^ table_3[c[1]] ^ c[2] ^ c[3];
	r[1] = c[0] ^ table_2[c[1]] ^ table_3[c[2]] ^ c[3];
	r[2] = c[0] ^ c[1] ^ table_2[c[2]] ^ table_3[c[3]];
	r[3] = table_3[c[0]] ^ c[1] ^ c[2] ^ table_2[c[3]];

}
 
 void mixColumns(unsigned char * state,uint32 nb){
	
	int i=0;
	int j=0;
	
	for(i=0;i<nb;i++){
		//extract column
		unsigned char col[4];
		for(j=0;j<4;j++){
			col[j] = state[nb*j + i];
		}
		gmix_columnTable(col);
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
 
 
 
 void cipher_block(unsigned char * state,uint32 * word,uint32 nb,uint32 nr){
 
	addRoundKey(state,word,0,nb);
	
	int round;
	for(round = 1;round < nr;round++){
		subBytes(state,nb);
		shiftRows(state,nb);
		mixColumns(state,nb);
		addRoundKey(state,word,round,nb);
	}
	
	subBytes(state,nb);
	shiftRows(state,nb);
	addRoundKey(state,word,round,nb);
	
	printState(state,nb);
	

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
		cipher_block(state,word,nb,nr);
		memcpy((output->mem) + i*blockSize,state,blockSize);
		free(state);
	}
	
 }
 

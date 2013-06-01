 #include <stdio.h>
 #include "aessbox.h"
 #include "aessub.h"
 
 //#define DEBUG

 
 uint32 subBox(uint32 before){
 
	uint32 after = 0;
	int i=0;
	
	for(;i<4;i++){
		after <<= 8;
		unsigned char temp = before >> (24 - i*8);
		after |= s_box[temp];
		#ifdef DEBUG
			printf("temp %x after %x\n",temp,after);
		#endif
	}
	
	return after;
 
 }
 
 unsigned char getRcon(unsigned char val){
	return RconArray[val];
 }
 
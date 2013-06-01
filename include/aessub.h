 #ifndef AESSUB
 #define AESSUB
 
 #include "aeskeyex.h"
 
extern const unsigned char s_box[];
extern const unsigned char inv_s_box[];
extern const unsigned char RconArray[];
extern const unsigned char table_2[];
extern const unsigned char table_3[];
extern const unsigned char table_9[];
extern const unsigned char table_11[];
extern const unsigned char table_13[];
extern const unsigned char table_14[];
 
 uint32 subBox(uint32 before);
 unsigned char getRcon(unsigned char val);
 unsigned char subBox8(unsigned char before);
 
 #endif
 
 
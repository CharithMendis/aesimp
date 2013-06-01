#ifndef AESKEY
#define AESKEY

typedef unsigned int uint32;

typedef struct keycontext{
  uint32 * key;
  unsigned int nk;
} keycontext_t;


uint32 * keyExpand(keycontext_t * keycon,const uint32 nr,const uint32 nb);
void printTheFile();

#endif 

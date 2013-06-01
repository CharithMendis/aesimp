#ifndef AESKEY
#define AESKEY

typedef unsigned int uint32;

typedef struct keycontext{
  uint32 * key;
  unsigned int nk;
} keycontext_t;


uint32 * keyExpand(keycontext_t * keycon,const uint32 nr,const uint32 nb);
void printTheFile();

#define LEFTROT(x,base,i) (( x << i) | (x >> (base - i)))
#define RotWord(x) LEFTROT(x,32,8)

#endif 

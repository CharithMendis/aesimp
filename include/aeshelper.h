#ifndef HELPER
#define HELPER

#include "aeskeyex.h"

void mixColumns(unsigned char * state,uint32 nb,void (*func)(unsigned char *));
void invGmix_columnTable(unsigned char *r);
void gmix_columnTable(unsigned char *r);
void shiftRows(unsigned char * state,uint32 nb,char inv);
void subBytes(unsigned char * state,uint32 nb,unsigned char * whatSbox);
void addRoundKey(unsigned char * state,uint32 * word,uint32 round,uint32 nb);
void printState(unsigned char * state,uint32 nb);
void transpose(unsigned char * state,uint32 nb);

#endif
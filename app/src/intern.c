#include <stdio.h>
#include <stdlib.h>
#include "../inc/intern.h"
#include "../inc/types.h"


/** 
 * @brief Fonction f du processus de SHA-1. 
 */
uint32_t f(uint32_t B,uint32_t C,uint32_t D,int t){
	uint32_t f;
	if((0<=t)&&(t<=19)) f=((B & C) | ((~B) & D)); //F1
	else if((20<=t)&&(t<=39)) f=B ^ C ^ D; //F2
	else if((40<=t)&&(t<=59)) f=((B & C) | (B & D) | (C & D)); //F3
	else if((60<=t)&&(t<=79)) f=B ^ C ^ D; //F4
	else f=-1;
	return f;
}

/** 
 * @brief Fonction k du processus de SHA-1. 
 */
uint32_t k(int t){
	uint32_t out;
	if((0<=t)&&(t<=19)) out=K1;
	else if((20<=t)&&(t<=39)) out=K2;
	else if((40<=t)&&(t<=59)) out=K3;
	else if((60<=t)&&(t<=79)) out=K4;
	else out=-1;
	return out;
}

/** 
 * @brief Fonction shift du processus de SHA-1. 
 */
uint32_t shift(int n,uint32_t X){
	uint32_t out=((X<<n) | (X>>(32-n)));
	return out;
}

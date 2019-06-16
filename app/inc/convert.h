#ifndef CONVERT_H
#define CONVERT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void my_itoa(int in,char* out,int longueur);
int convert_bi(char* chaine);
uint32_t convert_hexa(char* chaine);
void fill_zeros(char* t,int taille);
void fill_value(char* t,int rang,int val);


#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/convert.h"
#include "../inc/types.h"

/** 
 * @brief Convertit un int en string. 
 * @param in entrée de la fonction (entier à convertir).
 * @param out sortie de la fonction (string résultat).
 * @param longueur de l'entrée. 
 */
void my_itoa(int in,char* out,int longueur){
	int i,quotient,reste;
	int j=longueur;
	char g[2];
	int compteur=0;
	for(i=0;i<j-1;i++){
		out[i]='0';
	}
	out[j-1]='\0';
	while(in!=0){
		quotient=in/2;
		reste=in%2;
		if(reste==0) out[j-2-compteur]='0';
		else out[j-2-compteur]='1';
		compteur++;
		in=quotient;
	}
}

/** 
 * @brief Convertit un string écrit en binaire en entier base 10. 
 * @param chaine représentant le string à écrire en base 10.
 * @return entier écrit en base 10. 
 */
int convert_bi(char* chaine){
	int out=0;
	double rang=3;
	int caset=0;
	while(rang!=-1){
		if(chaine[caset]=='1') {out=out+pow(2,rang);}
		rang--;
		caset++;
	}
	return out;
}

/** 
 * @brief Convertit un string écrit en hexa en entier base 10. 
 * @param chaine représentant le string à écrire en base 10.
 * @return entier écrit en base 10. 
 */
uint32_t convert_hexa(char* chaine){
	uint32_t out=0;
	uint32_t puiss;
	double rang=8-1;
	int caset=0;
	while(rang!=-1){
		puiss=pow(16,rang);
		if(chaine[caset]=='1') {out=out+puiss;}
		else if(chaine[caset]=='2') {out=out+2*puiss;}
		else if(chaine[caset]=='3') {out=out+3*puiss;}
		else if(chaine[caset]=='4') {out=out+4*puiss;}
		else if(chaine[caset]=='5') {out=out+5*puiss;}
		else if(chaine[caset]=='6') {out=out+6*puiss;}
		else if(chaine[caset]=='7') {out=out+7*puiss;}
		else if(chaine[caset]=='8') {out=out+8*puiss;}
		else if(chaine[caset]=='9') {out=out+9*puiss;}
		else if(chaine[caset]=='a') {out=out+10*puiss;}
		else if(chaine[caset]=='b') {out=out+11*puiss;}
		else if(chaine[caset]=='c') {out=out+12*puiss;}
		else if(chaine[caset]=='d') {out=out+13*puiss;}
		else if(chaine[caset]=='e') {out=out+14*puiss;}
		else if(chaine[caset]=='f') {out=out+15*puiss;}
		rang--;
		caset++;
	}
	return out;
}

/** 
 * @brief Remplit de "0" t. 
 * @param t représente l'entier où rajouter les "0".
 * @param taille représente la taille de t.
 */
void fill_zeros(char* t,int taille){
	int i;
	for(i=0;i<taille;i++){
		t[i]='0';
	}
	t[taille-1]='\0';
}

/** 
 * @brief Remplit de la valeur val dans t. 
 * @param t représente l'entier base 16.
 * @param rang représente le rang de la valeur à convertir.
 * @param val représente l'entier à traduire dans t.
 */
void fill_value(char* t,int rang,int val){
	if(val==0) t[rang]='0';
	else if(val==1) t[rang]='1';
	else if(val==2) t[rang]='2';
	else if(val==3) t[rang]='3';
	else if(val==4) t[rang]='4';
	else if(val==5) t[rang]='5';
	else if(val==6) t[rang]='6';
	else if(val==7) t[rang]='7';
	else if(val==8) t[rang]='8';
	else if(val==9) t[rang]='9';
	else if(val==10) t[rang]='a';
	else if(val==11) t[rang]='b';
	else if(val==12) t[rang]='c';
	else if(val==13) t[rang]='d';
	else if(val==14) t[rang]='e';
	else if(val==15) t[rang]='f';
}

#include <stdio.h>
#include <stdlib.h>
#include "../inc/sha.h"
#include "../inc/types.h"
#include "../inc/convert.h"
#include "../inc/intern.h"

/** 
 * @brief Initialisation des registres du hash sha-1. 
 * @param hash représentant le hash à réaliser.
 * @return hash initialisé.
 */
SHA1 init_registres(SHA1 hash){
	
	// H0,H1,H2,H3,H4,H5 initialises
	hash.registre2[0]=0x67452301;
	hash.registre2[1]=0xEFCDAB89;
	hash.registre2[2]=0x98BADCFE;
	hash.registre2[3]=0x10325476;
	hash.registre2[4]=0xC3D2E1F0;
	
	return hash;
}

/** 
 * @brief Initialisation des 16W du hash sha-1. 
 * @param hash représentant le hash à réaliser.
 * @return hash initialisé.
 */
SHA1 init_16W(SHA1 hash,int rang){
	int i;
	for(i=0;i<16;i++){
		hash.W[i]=hash.mot[i][rang];
	}
	return hash;
}

/** 
 * @brief Initialisation du hash sha-1. 
 * @param hash représentant le hash à réaliser.
 * @return hash initialisé.
 */
SHA1 init_sha1(char* message){
	SHA1 hash;
	hash=init_registres(hash);
	int taille=strlen(message);
	int nb=taille*sizeof(char)*TAILLE_OCTET+1+1;
	char binaire[nb]; // contiendra le binaire du message
	binaire[0]='\0';
	char lettre[sizeof(char)*TAILLE_OCTET+1]; // contiendra le binaire de la lettre
	unsigned char c; int i=0; int j;
	for(j=0;j<strlen(message);j++){
		c=message[j];
		my_itoa(c,lettre,sizeof(lettre));
		strcat(binaire,lettre);
	}
	char temp[2];
	temp[0]='1';temp[1]='\0';
	strcat(binaire,temp);

	int calc=0;
	int k;
	for(k=0;k<512;k++){
		if((strlen(binaire)+64+k)%512==0){ 
			calc=k;
		}
	}
	hash.nbBlocs=(strlen(binaire)+64+calc)/512; 
	
	char blocZero[calc+1];
	fill_zeros(blocZero,calc+1);
	char finalBinaire[strlen(binaire)+64+calc+1]; 
	finalBinaire[0]='\0';
	strcat(finalBinaire,binaire);
	strcat(finalBinaire,blocZero);
	
	char blocTaille[64+1];
	fill_zeros(blocTaille,sizeof(blocTaille));
	my_itoa(taille*TAILLE_OCTET,blocTaille,sizeof(blocTaille));
	strcat(finalBinaire,blocTaille);
		
	char finalHexa[strlen(finalBinaire)/4+1];
	finalHexa[sizeof(finalHexa)-1]='\0';
	int grQuatre;
	int p=0;int rang=0;
	char paquet[5]; paquet[4]='\0';
	do{
		paquet[0]=finalBinaire[p];
		paquet[1]=finalBinaire[p+1];
		paquet[2]=finalBinaire[p+2];
		paquet[3]=finalBinaire[p+3];
		grQuatre=convert_bi(paquet);
		fill_value(finalHexa,rang,grQuatre);
		rang++;
		p=p+4;
	}while(p!=strlen(finalBinaire));
	int d;
	for(d=0;d<16;d++){
		hash.mot[d]=malloc(hash.nbBlocs * sizeof(uint32_t));
	}
	p=0;rang=0;
	uint32_t grHuit;
	char paquet1[9]; paquet1[8]='\0';
	do{
		paquet1[0]=finalHexa[p];
		paquet1[1]=finalHexa[p+1];
		paquet1[2]=finalHexa[p+2];
		paquet1[3]=finalHexa[p+3];		
		paquet1[4]=finalHexa[p+4];
		paquet1[5]=finalHexa[p+5];
		paquet1[6]=finalHexa[p+6];
		paquet1[7]=finalHexa[p+7];
		grHuit=convert_hexa(paquet1);
		hash.mot[(p/8)%16][p/(16*8)]=grHuit;
		rang++;
		p=p+8;
	}while(p!=strlen(finalHexa));
	return hash;
}

/** 
 * @brief Etapes de processus du calcul du hash sha-1. 
 * @param hash représentant le hash à réaliser.
 * @param out représente le résultat écrit en base 16.
 */
void process_sha1(SHA1 hash,char* out){
	int i,t,h;
	uint32_t TEMP;
	for(i=0;i<hash.nbBlocs;i++){
		hash=init_16W(hash,i);
		for(t=16;t<80;t++){
			hash.W[t]=(shift(1,(hash.W[t-3] ^ hash.W[t-8] ^ hash.W[t-14] ^ hash.W[t-16] )));
		}
		hash.registre1[0]=hash.registre2[0]; //A<-HO
		hash.registre1[1]=hash.registre2[1]; //B<-H1
		hash.registre1[2]=hash.registre2[2]; //C<-H2
		hash.registre1[3]=hash.registre2[3]; //D<-H3
		hash.registre1[4]=hash.registre2[4]; //E<-H4

		for(t=0;t<80;t++){
			TEMP=(shift(5,hash.registre1[0]))+f(hash.registre1[1],hash.registre1[2],hash.registre1[3],t)+hash.registre1[4]+hash.W[t]+k(t);
			hash.registre1[4]=hash.registre1[3];
			hash.registre1[3]=hash.registre1[2];
			hash.registre1[2]=shift(30,hash.registre1[1]);
			hash.registre1[1]=hash.registre1[0];
			hash.registre1[0]=TEMP;
		}

		hash.registre2[0]=hash.registre2[0]+hash.registre1[0];
		hash.registre2[1]=hash.registre2[1]+hash.registre1[1];
		hash.registre2[2]=hash.registre2[2]+hash.registre1[2];
		hash.registre2[3]=hash.registre2[3]+hash.registre1[3];
		hash.registre2[4]=hash.registre2[4]+hash.registre1[4];
	}
	
	sprintf(out,"%0x%0x%0x%0x%0x",hash.registre2[0],hash.registre2[1],hash.registre2[2],hash.registre2[3],hash.registre2[4]);
}

/** 
 * @brief Libération de la mémoire du hash sha-1. 
 * @param hash représentant le hash à libérer.
 */
void done_sha1(SHA1 hash){
	int i;
	for(i=0;i<16;i++){
		free(hash.mot[i]);
	}
}

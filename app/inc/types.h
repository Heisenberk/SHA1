
#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define TAILLE_HASH_SHA1 (40)
#define TAILLE_OCTET (8)

#define K1 (0x5A827999)
#define K2 (0x6ED9EBA1)
#define K3 (0x8F1BBCDC)
#define K4 (0xCA62C1D6)

/**
 * \struct SHA1
 * \brief Objet représentant le résultat et qui permet de faire les 
 * différentes étapes du hachage.
 **/
struct sha1{
	int nbBlocs; 
	uint32_t* mot[16];
	uint32_t registre1[5]; // A, B, C, D, E
	uint32_t registre2[5]; //H0, H1, H2, H3, H4, H5
	uint32_t W[80];
};typedef struct sha1 SHA1;

#endif

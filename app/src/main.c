#include <stdio.h>
#include <stdlib.h>
#include "../inc/sha.h"
#include "../inc/types.h"

/** 
 * @brief Fonction principale. 
 * @param argv nombre de paramètres en arguments.
 * @param argc arguments.
 */
int main(int argv,char** argc){
	SHA1 hash;
	char final[TAILLE_HASH_SHA1];
	if(argv!=2){
		printf("Argument(s) invalides\n");
		return EXIT_FAILURE;
	}
	hash=init_sha1(argc[1]);
	process_sha1(hash,final);
	done_sha1(hash);
	printf("%s\n",final);
	return EXIT_SUCCESS;
}

#include "hasher.h"

/*
 * Crea un hasher
 */
struct hasher* init_hasher(){

	struct hasher* h=malloc(sizeof(struct hasher));
	return h;
}

/*
 * Crea un hasher
 */
struct hasher* init_hasher2(int seed){

	struct hasher* h=malloc(sizeof(struct hasher));
	h->seed=seed;
	return h;
}

/*
 * Produce codice hash di un oggetto
 */
int hash(struct hasher* h,const void*o,int whichhash){

		 return ((java_hashCode(o)*h->randomkeys[whichhash])&2147483647)%h->maxval;
}


/*
 * Calcola hash su una stringa
 */
int java_hashCode(const char *str) {

    int hash = 0;

    for (int i = 0; i < strlen(str); i++) {
        hash = 31 * hash + str[i];
    }

    return hash;
}

/*
 * Setta il numero di chiavi random
 */
void setNumberOfRandomKeys(struct hasher* h,int K){

	//if(h->randomkeys!=NULL){
		//printf("Errore\n");
		//return;
	//}

	h->numdichiavi = K;
	h->randomkeys=malloc(sizeof(int)*K);
	for(int i=0;i<K;++i)
		h->randomkeys[i]=(int_rand(0,2147483647)>>2)*2+1;

}

/*
 * Genera un numero casuale
 */
int int_rand(int min,int max){

 int numero_casuale;
 int differenza;
 differenza = (max - min) + 1;
 srand(clock());
 numero_casuale = rand() % differenza ;
 numero_casuale = numero_casuale + min ;
 return numero_casuale;
}


/*
 * Setta il massimo valore sulla base del bitSet
 */
void setMaxValue(struct hasher*h,int bitSetSize){

	h->maxval=bitSetSize;
}

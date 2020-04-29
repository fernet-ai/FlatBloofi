#include <stdio.h>
#include <stdlib.h>
#include "flatBloofi.h"
#include <string.h>

int numcrifre(int n);
char* concatena(char* str, int i);

int main(void) {
	setbuf(stdout, NULL);

	puts("******* FLAT BLOOFI  C *******");
	/*
	 * NB: il numero di funzioni hash deve essere generato in funzione della probabilità
	 * di falsi positivi
	 */

	// istanzio bloom filter
    struct flatbloofi *bl;
    bl= flat_bloom_filter_index();

	//Setto un hasher
    struct hasher* h = init_hasher();

    //Setto i parametri
    int expectedNbElemInFilter = 10000; //Numero di parole che dovrebbe contenere il bloom filter
	double falsePosProb = 0.21;  //setto la probabilità di falsi positivi
    int metric = 1;// metrica di confronto tra Bloom filters. Assume valore 1 se la metrica utilizzata è di Hamming, 2 se di Jaccard, 3 se di Cosine;


	//Creo una lista dove metterò il bloom filter
    list bfList = newList();

	// Creao un po' di bloom filter
	struct bloom* bf;
	bf = malloc(sizeof(struct bloom));
	bloom_init(bf, expectedNbElemInFilter,falsePosProb,metric,h);

	struct bloom* bf2;
	bf2 = malloc(sizeof(struct bloom));
	bloom_init(bf2, expectedNbElemInFilter,falsePosProb,metric,h);

	struct bloom* bf3;
	bf3 = malloc(sizeof(struct bloom));
	bloom_init(bf3, expectedNbElemInFilter,falsePosProb,metric,h);

	struct bloom* bf4;
	bf4 = malloc(sizeof(struct bloom));
	bloom_init(bf4, expectedNbElemInFilter,falsePosProb,metric,h);


	bfList=insertElement(bfList,bf); //Inserimento del bf nella lista
	bfList=insertElement(bfList,bf2); //Inserimento del bf nella lista
	bfList=insertElement(bfList,bf3); //Inserimento del bf nella lista
	bfList=insertElement(bfList,bf4); //Inserimento del bf nella lista


	 for(int i = 0; i <5000; i++) {


		bloom_add(bf,concatena("Gatto", i));
		bloom_add(bf,concatena("cane", i));

		bloom_add(bf2, concatena("pappagallo", i));
		bloom_add(bf2,concatena("bimbo", i));
		bloom_add(bf2,concatena("aldrovandi", i));

		bloom_add(bf3,concatena("pentola", i));
		bloom_add(bf3,concatena("forchetta", i));

		bloom_add(bf4,concatena("pc", i));
	 }


    struct bloom* current; // bloom filter di appoggio

	// Per ogni bloom filter nella lista, lo inserisco nel FLAT BLOOFI
	for(int i = 0; i < bfList->size; i++){
		current = getElement(bfList,i);
		insertBloomFilter(bl,current);
	}


    // Cerco una parola... in che bloom filter/bloom filters  si trova/trovano?
	int* idbloom = search(bl, "pc4900");
	while(*idbloom != -1 && *idbloom!=0){ // 0 non è un valore valido
		printf("\nla parola si trova nel bloom filter con id: %d\n", *idbloom);
		idbloom++;
	}


	free(bl);
	return EXIT_SUCCESS;
}





int numcrifre(int n)
{
int i=1;

if(n==0) return 0;

   while(n>10)
   {
      n/=10;
      i++;
   }

return i;
}



char* concatena(char* str, int i){

	int size = strlen(str)+ numcrifre(i)+1;

	char *temp = calloc( size+1, sizeof(char));
	sprintf(temp, "%s%d", str, i);

	temp[size] = '\0';

	return temp;
}

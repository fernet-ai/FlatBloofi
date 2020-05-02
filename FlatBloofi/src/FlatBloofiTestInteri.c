/*
 * FlatBloofiTestInteri.c

 *
 *  Created on: 30/apr/2020
 *      Author: fernet
 */

#include <stdio.h>
#include <stdlib.h>
#include "flatBloofi.h"
#include <string.h>


int main3(void) {
	setbuf(stdout, NULL);

	puts("******* FLAT BLOOFI  C SU INTERI *******");
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
	double falsePosProb = 0.01;  //setto la probabilità di falsi positivi
    int metric = 1;// metrica di confronto tra Bloom filters. Assume valore 1 se la metrica utilizzata è di Hamming, 2 se di Jaccard, 3 se di Cosine;



    int counter = 0;
	//Creo una lista dove metterò il bloom filter
	list bfList = NULL;
	bfList = newList();

	// 190x4 bloom filter sono quasi 12 flat...
	for(int j = 0; j < 54; j++){
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


		 for(int i = 0; i <5000; i++) {

			int num = 11;
			int num2 = 111;
			int num3 = 22;
			int num4 = 222;
			int num5 = 2222;
			int num6 = 33;
			int num7 = 333;
			int num8 = 44;

			bloom_add(bf, &num);
			bloom_add(bf,&num2);

			bloom_add(bf2, &num3);
			bloom_add(bf2,&num4);
			bloom_add(bf2,&num5);

			bloom_add(bf3,&num6);
			bloom_add(bf3,&num7);

			bloom_add(bf4, &num8);

		 }
			bfList=insertElement(bfList,bf); //Inserimento del bf nella lista
			bfList=insertElement(bfList,bf2); //Inserimento del bf nella lista
			bfList=insertElement(bfList,bf3); //Inserimento del bf nella lista
			bfList=insertElement(bfList,bf4); //Inserimento del bf nella lista

	}


	struct bloom* current = NULL; // bloom filter di appoggio

	// Per ogni bloom filter nella lista, lo inserisco nel FLAT BLOOFI j-esimo
	for(int i = 0; i < bfList->size; i++){
		current = getElement(bfList,i);
		insertBloomFilter(bl,current);
		counter++;
	 }


	printf("\n Numero di bloom aggiunti: %d\n", counter);

	printf("\nSto cercando la parola ...");

    // Cerco una parola... in che bloom filter/bloom filters  si trova/trovano?
	int parolacercata = 33;
	int* idbloom = search(bl, &parolacercata);
	/*while(*idbloom != -1){ // 0 non è un valore valido
		printf("\nla parola si trova nel bloom filter con id: %d\n", *idbloom);
		idbloom++;
	}*/


	free(bl);
	return EXIT_SUCCESS;
}










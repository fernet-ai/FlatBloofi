/*
 * flatBloofi.c
 *
 *  Created on: 24/apr/2020
 *      Author: fernet
 */
#include <stdio.h>
#include "flatBloofi.h"
#include "time.h"

struct flatbloofi* flat_bloom_filter_index(){

	struct flatbloofi*bl;
	bl=malloc(sizeof(struct flatbloofi));

	bl->fromindextoId = newList();
	for(int i=0;i<SIZE;i++) bl->idMap[i]=NULL;
	bl->buffer = newList();
	bl->busy = bitset_create_with_capacity(0);

	return bl;

}


void insertBloomFilter(struct flatbloofi *bl,struct bloom *b){

	if(bl->h != NULL){
		if(b->h != NULL)
			printf("Stai usando più di un hasher, mmmh\n");
	}
	else bl->h = b->h;

	int i = nextUnSetBit(bl->busy, 0);

	if (i < 0) {

        i = bitset_size_in_bits(bl->busy);

        bitset_resize(bl->busy, i+64, false);

        int capienza = get_length(b->b);
        uint64_t *arraydilong = calloc(capienza, sizeof(uint64_t));


        insertElementDim(bl->buffer, arraydilong, capienza);

        /*come si dovrebbe gettare un array lungo...
		struct nodeList_withSize *temp= getNodeElementDim(bl->buffer, 0);
		for(int i =0; i< 1024; i++) printf(" %d ", temp->array[i]);
*/

    }


	int idBloomFilterNew  =  b->id;

	if(i < getSize(bl->fromindextoId)){
		insertElementByIndex(bl->fromindextoId, i, idBloomFilterNew);
	}
	else{
		insertElement(bl->fromindextoId, idBloomFilterNew);
	}

	setBloomAt(bl, i, b->b);
	insert(bl->idMap, idBloomFilterNew, i);
	bitset_set(bl->busy, i);


}


int* search(struct flatbloofi*bl, const void*o){

	int *answer = calloc(500, sizeof(int)); //da migliorare .. mi ritorna max 500 id

	for (int i = 0; i < getSize(bl->buffer); ++i) {

		printf("nel flat %d ...\n", i);

		uint64_t w = ~0l; // set tutti i bit al contrario, quindi setta 64 bit a 1



		//prendo un bloom a caso x sapere il num di funzioni hash..
		for(int l = 0; l <  bl->h->numdichiavi; ++l){

			int hashvalue = (int) hash( bl->h, o, l);
			printf("l'hash #%d  sull'elemento %s  mi ritorna l'indice %d\n",l, o, hashvalue);


			struct nodeList_withSize *nodoDiLong= getNodeElementDim(bl->buffer, i ); // torna un array i-esimo di long

            w &=  (uint64_t) nodoDiLong->array[hashvalue];

			printf("\nnvalore di w =");
			printBits(sizeof(w), &w);

		}

		int counter = 0;
        while (w != 0) {
        	uint64_t t = w & -w; // torna solo un bit a 1 un una data posizione
        	printf("t= %lu in binario:", t);
        	printBits(sizeof(t), &t);
        	//Inserisci gli id dei bloom filter che hanno la parola cercata
        	int indexbloom = getElement(bl->fromindextoId, i * 64 +  __builtin_popcountll(t-1));

        	//printf("counter: %d la parola si trova nel bloom filter con id: %d",counter, indexbloom);

        	answer[counter] = indexbloom;

        	w ^= t;  // XOR si salva in w lo XOR bit a bit tra w e t --> dà 1 se i bit sono diversi
        	counter++;
        }
        answer[counter+1] = -1; // mi servirà per far capire che sono finiti gli id  e quello di prima era l'ultimo


	}
	return answer;
}


void setBloomAt(struct flatbloofi*bl, int i, bitset_t *bitset) {
	puts("SetBLoomAt");

	struct nodeList_withSize *nodo= getNodeElementDim(bl->buffer, i >> 6);// torna un array di long
//	for(int i =0; i< 1024; i++) printf(" %d ", nodo->array[i]);
	//puts("");
	uint64_t*mybuffer = nodo->array;

    if(get_length(bitset)!= nodo->dim){//Confronta le lunghezza
    	puts("C'è qualcosa che non va ...");
    }

   uint64_t mask = (1l << i);
   printf("k = %d\n", nextSetBit2(bitset,0));

    for (int k = nextSetBit2(bitset, 0); k >= 0; k = nextSetBit2(bitset, k+1)) {
        //printf("mybuffer ORato  ");
        //printBits(sizeof(uint64_t),mybuffer+k);
    	mybuffer[k] |= mask;
    }

}


void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}


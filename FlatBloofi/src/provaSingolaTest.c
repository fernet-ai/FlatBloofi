#include <stdio.h>
#include <stdlib.h>
#include "flatBloofi.h"
#include <string.h>

int numcrifre2(int n);
char* concatena2(char* str, int i);

int main(void) {
	setbuf(stdout, NULL);

	puts("******* FLAT BLOOFI SINGOLO  C *******");
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



		//Creo una lista dove metterò il bloom filter
		list bfList = NULL;
		bfList = newList();

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


		 for(int i = 0; i <1; i++) {


			bloom_add(bf,concatena2("Gatto", i));
			bloom_add(bf,concatena2("cane", i));

			bloom_add(bf2, concatena2("pappagallo", i));
			bloom_add(bf2,concatena2("bimbo", i));
			bloom_add(bf2,concatena2("aldrovandi", i));

			bloom_add(bf3,concatena2("pentola", i));
			bloom_add(bf3,concatena2("forchetta", i));

			bloom_add(bf4,concatena2("pc", i));
		 }


		struct bloom* current = NULL; // bloom filter di appoggio

		// Per ogni bloom filter nella lista, lo inserisco nel FLAT BLOOFI j-esimo
		for(int i = 0; i < bfList->size; i++){
			current = getElement(bfList,i);
			insertBloomFilter(bl,current);
		 }


		//aggiorno un bloom filter con un nuovo valore
	   current=getElement(bfList,2);
	   bloom_add(current, "lupo"); //così modifico il bitset del bloom in modo da modificarne il bitset
	   updateIndex(bl,current);

	    // Cerco una parola... in che bloom filter/bloom filters  si trova/trovano?
	   search(bl, "lupo");



	printf("\nSto cercando la parola ...");

    // Cerco una parola... in che bloom filter/bloom filters  si trova/trovano?
	int* idbloom = search(bl, "aldrovandi0");
	/*while(*idbloom != -1){ // 0 non è un valore valido
		printf("\nla parola si trova nel bloom filter con id: %d\n", *idbloom);
		idbloom++;
	}*/

	int index = 2;
	printf("\n\n Ora cancello il bloom filter con id %d ...", index);
	// CANCELLO Bloom filter
	deleteBloomFromIndex(bl, index);  //Parte da 0 l'indicizzazione?


	printf("\nCerco le parole..\n");
    char* parolacercata = "Gatto0";
	printf("\ncerco la parola %s\n", parolacercata);
	search(bl, parolacercata);

    char* parolacercata2= "cane0";
	printf("\ncerco la parola %s\n", parolacercata2);
	search(bl, parolacercata2);

    char* parolacercata3 = "pappagallo0";
	printf("\ncerco la parola %s\n", parolacercata3);
	search(bl, parolacercata3);

    char* parolacercata4 = "bimbo0";
	printf("\ncerco la parola %s\n", parolacercata4);
	search(bl, parolacercata4);

	char* parolacercata5 = "aldrovandi0";
	printf("\ncerco la parola %s\n", parolacercata5);
	search(bl, parolacercata5);

    char* parolacercata6 = "pentola0";
	printf("\ncerco la parola %s\n", parolacercata6);
    search(bl, parolacercata6);

    char* parolacercata7 = "forchetta0";
	printf("\ncerco la parola %s\n", parolacercata7);
    search(bl, parolacercata7);

    char* parolacercata8 = "pc0";
	printf("\ncerco la parola %s\n", parolacercata8);
	search(bl, parolacercata8);

	puts("END");


	free(bl);
	return EXIT_SUCCESS;
}




int numcrifre2(int n)
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



char* concatena2(char* str, int i){

	int size = strlen(str)+ numcrifre(i)+1;

	char *temp = calloc( size+1, sizeof(char));
	sprintf(temp, "%s%d", str, i);

	temp[size] = '\0';

	return temp;
}

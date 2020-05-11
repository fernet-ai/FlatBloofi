/*
 * TestFlatBloomFilter.c
 *
 *  Created on: 10/mag/2020
 *      Author: fernet
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "flatBloofi.h"
#include <sys/time.h>
#include <sys/resource.h>

#define DIM 100
#define RUN 1

struct bloom* createBloomFilter(float falsePosProb, int expectedNbElemInFilter,struct hasher*h,int metric,int num);


int main5(int argc,char**argv) {
	setbuf(stdout, NULL);


	printf("******	TESTANDO FLAT BLOOFI *******\n");

	 clock_t t_start,t_end;
	 double t_passed;
	 double totInsertTime, totUpdateTime, totSearchTime,totDeleteTime;


	 for(int i=0;i<RUN;i++){

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

	    struct bloom*current;



	 //inizializzo una lista di bloom filter
	   for(int i=0;i<DIM;i++){
	       current=createBloomFilter(falsePosProb,expectedNbElemInFilter,h,1,i+1);
	       bfList=insertElement(bfList,current);

	   }




	 //inserisco i BloomFilter nel bloofi
	 for(int i=0;i<DIM;i++){
	   current=getElement(bfList,i);
	   t_start=clock();
	   insertBloomFilter(bl,current);
	   t_end=clock();
	   t_passed = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
	   totInsertTime+=t_passed;

	 }


	 //AGGIORNO
	 for(int i=0;i<DIM;i++){
	   current=getElement(bfList,i);
	   int num = 88+i;
	   bloom_add(current, &num); //così modifico il bitset del bloom in modo da modificarne il bitset
	   t_start=clock();
	   updateIndex(bl,current);
	   t_end=clock();
	   t_passed = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
	   totUpdateTime+=t_passed;

	 }



	 //cerca nell'indice i valori inseriti
	 int *find;
	 int numCerca;

	 for(int i=0;i<DIM;i++){
		 numCerca=i+1;
		 t_start=clock();
	     find=search(bl,&numCerca);
	     free(find);
	     t_end=clock();
	     t_passed = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
	     totSearchTime+=t_passed;


	 }

	/*elimina
	 // GLI INDICI PARTONO DA 1
	 for(int i=1;i<=DIM;i++){
		 t_start=clock();
		 deleteBloomFromIndex(bl,i);
		 t_end=clock();
		 t_passed = ((double)(t_end - t_start)) / CLOCKS_PER_SEC;
		// totDeleteTime+=t_passed;

	 }*/




	 free(bl);
	}

	printf("Elapsed  insert time: %f ms.\n", totInsertTime*1000);
	printf("Elapsed  update time: %f ms.\n", totUpdateTime*1000);
	printf("Elapsed  search time: %f ms.\n", totSearchTime*1000);
	//printf("Elapsed  delete time: %f ms.\n", totDeleteTime*1000);




	 return EXIT_SUCCESS;


}

struct bloom* createBloomFilter(float falsePosProb, int expectedNbElemInFilter,
		                         struct hasher*h,int metric,int num){
 struct bloom* bf;
// int num;
  bf=malloc(sizeof(struct bloom));
  bloom_init(bf,expectedNbElemInFilter,falsePosProb,metric,h);
 for(int i=0;i<DIM;i++){
	 num=i;
	  bloom_add(bf,&num);
  }
  return bf;
}

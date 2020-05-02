/*
 * flatBloofi.h
 *
 *  Created on: 24/apr/2020
 *      Author: fernet
 */
#include "bitset.h"
#include "bloom.h"
#include "list.h"
#include "hashtable.h"
#define SIZE 10000// PUO ESSERE UN VINCOLO
#ifndef FLATBLOOFI_H_
#define FLATBLOOFI_H_

#ifdef __cplusplus
extern "C" {
#endif

struct flatbloofi{

	list fromindextoId; 	// un array di ID di bloom filter
	struct DataItem* idMap[SIZE];	// mappa ogni ID bloom filter ad un numero
	list buffer;	//un arrayList di array di long
	bitset_t* busy; // BitSet

	struct hasher* h; // hasher predefinito

};

void printBits(size_t const size, void const * const ptr);
struct flatbloofi* flat_bloom_filter_index();
void insertBloomFilter(struct flatbloofi *bl,struct bloom *b);
int* search(struct flatbloofi*bl,const void*o);
void setBloomAt(struct flatbloofi*bl, int i, bitset_t *bitset);



#endif /* FLATBLOOFI_H_ */

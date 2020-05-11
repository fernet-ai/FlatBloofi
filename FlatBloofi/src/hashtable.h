#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//dimensione dell'hashTable
#define SIZE 1000000 //Può essere un vincolo

struct DataItem {
   int data;
   int key;
};


struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key);

int searchHash(struct DataItem** hashArray,int key);

void insert(struct DataItem** hashArray,int key,int data);

void delete(struct DataItem** hashArray, int key);

void display(struct DataItem** hashArray);

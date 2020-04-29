typedef short boolean;
#include <stdint.h>


struct nodeList_c{

	struct nodeList*first;
	int size;
};

struct nodeList{

	void *bf;
	struct nodeList *next;

};


typedef struct nodeList_c *list;


//Ogni nodo in questa variante possiede la sua taglia********************
struct nodeList_withSize{

	uint64_t *array;
	struct nodeList *next;
	int dim;

};


typedef struct nodeList_withSize *nododim;
list insertElementDim(list l,uint64_t *x, int dim);
void* getNodeElementDim(list l,int index);

//**************************************



list newList();
list insertElement(list l,void *x);
boolean isFullList(list l);
boolean isEmptyList(list l);
int getSize(list l);
void* getElement(list l,int index);
int compareElement(void *a,void *b);
list addAll(list l,list new);
list insertElementByIndex(list l,int index,void *newChild);
list deleteElement(list l,void *x);
list deleteElementByIndex(list l,int index);
int indexOfElement(list l,void *bfn);
list removeLastHalf(list l,int from);

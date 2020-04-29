#include "list.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

clock_t t_start, t_end;
double t_passed;

/** DA FERNET*******/
list insertElementDim(list l, uint64_t *x, int dim){

	__uint64_t *vectore =  x;
	vectore  = calloc(dim, sizeof(__uint64_t));

	//Si può migliorare, forse è inutile
    for(int i =0; i<dim; i++){
    	vectore[i] = *(x+i);
    }

	l->size++;
	struct nodeList_withSize *temp; //modificato
	list p;
	p=newList();
	p->first=l->first;
	if(!isFullList(l)){
		temp=malloc(sizeof(struct nodeList_withSize));//modificato
		temp->array= vectore;
		temp->dim = dim; // add
		if(l->first==NULL){
			temp->next=NULL;
			l->first=temp;
		}else{
			while(p->first->next!=NULL){
				p->first=p->first->next;
			}
			if(p->first->next==NULL){
				p->first->next=temp;
				temp->next=NULL;
			}
		}


	}
	free(p);




	return l;

}

void* getNodeElementDim(list l,int index){

	list p;
	p=newList();
	p->first=l->first;
	int conta=0;
	//se la lista è vuota
	if(l->first==NULL){
		free(p);
		return NULL;
	}
	//ci sta un solo elemento
	if(l->first->next==NULL){
		if(conta==index){
			free(p);
			struct nodeList_withSize *temp= l->first;
			return temp;
		}

		else{

			return NULL;
		}
	}

	//ci sono almeno due elementi
	while(p->first->next!=NULL){
		if(conta==index){
			struct nodeList_withSize *temp=p->first;
			free(p);
			return temp;
		}
		conta++;
	}

	//controllo su ultimo elemento
	if(p->first->next==NULL)
		if(conta==index){
			struct nodeList_withSize *temp=p->first;
			free(p);
			return temp;
		}
	free(p);
	return NULL;

	}

//____________________________



/*
 * Crea una nuova lista
 */
list newList(){

	struct nodeList_c *l;
	l=malloc(sizeof(struct nodeList_c));
	if(l!=NULL){
		l->first=NULL;
		l->size=0;
	}
return l;
}

/*
 * Confronta due elementi
 */
int compareElement(void *a,void *b){

	if(a==b){

			return 0;
	}
	else {

		return 1;
	}

}


/*
 * Inserisce un elemento nella lista
 */
list insertElement(list l,void *x){

	l->size++;
	struct nodeList *temp;
	list p;
	p=newList();
	p->first=l->first;
	if(!isFullList(l)){
		temp=malloc(sizeof(struct nodeList));
		temp->bf=x;
		if(l->first==NULL){
			temp->next=NULL;
			l->first=temp;
		}else{
			while(p->first->next!=NULL){
				p->first=p->first->next;
			}
			if(p->first->next==NULL){
				p->first->next=temp;
				temp->next=NULL;
			}
		}

	}
	free(p);
	return l;
}

/*
 * Preleva un elemento dalla lista in base al suo indice
 */
void* getElement(list l,int index){

list p;
p=newList();
p->first=l->first;
int conta=0;
//se la lista è vuota
if(l->first==NULL){
	free(p);
	return NULL;
}
//ci sta un solo elemento
if(l->first->next==NULL){
	if(conta==index){
		free(p);
		return l->first->bf;
	}

	else{

		return NULL;
	}
}

//ci sono almeno due elementi
while(p->first->next!=NULL){
	if(conta==index){
		struct BFINode *temp=p->first->bf;
		free(p);
		return temp;
	}
	p->first=p->first->next;
	conta++;
}

//controllo su ultimo elemento
if(p->first->next==NULL)
	if(conta==index){
		struct BFINode *temp=p->first->bf;
		free(p);
		return temp;
	}
free(p);
return NULL;
}

/*
 * Controlla se la lista è vuota
 */
boolean isFullList(list l){
	struct nodeList *temp;
	temp=malloc(sizeof(struct nodeList));
	if(temp==NULL)
		return 1;
	free(temp);
	return 0;
}

/*
 * Controlla se la lista non è creata
 */
boolean isEmptyList(list l){

	return(l->first==NULL);
}

/*
 * Restituisce la dimensione della lista
 */
int getSize(list l){
	int conta=0;
	list p;
	p=newList();
	if(l->first==NULL){
		free(p);
		return 0;
	}
	else{
	p->first=l->first;
	//if(p->next==NULL)
		//return 1;
	   while(p->first->next!=NULL){
		    conta++;
		    p->first=p->first->next;
	   }
	}
	free(p);
	return conta+1;
}

/*
 * Inserisce un elemento in un certo indice
 */
list insertElementByIndex(list l,int index,void *newChild){
	l->size++;
	struct nodeList *newNode;
	list prec;
	struct nodeList *l2;
	int pos=0;
	if(index==0){
		newNode=malloc(sizeof(struct nodeList));
		newNode->bf=newChild;
		newNode->next=l->first;
		l->first=newNode;
		return l;
	}
	prec=newList();
	prec->first=l->first;
	while(pos<index-1&&prec->first!=NULL){
		prec->first=prec->first->next;
		pos++;
	}

	if(prec->first!=NULL){
		l2=malloc(sizeof(struct nodeList));
		l2->bf=newChild;
		l2->next=prec->first->next;
		prec->first->next=l2;

	}
free(prec);
return l;
}


/*
 * Elimina un elemento dalla lista
 */
list deleteElement(list l,void *x){
	list p;
	p=newList();
	list p2;
	p2=newList();
    p->first=l->first;
    p2->first=l->first;

	//elimino primo elemento
	if(!isEmptyList(l)){
		l->size--;
		if(!compareElement(l->first->bf,x)){
			l->first=l->first->next;
			free(p->first);
			free(p);
			return l;
		}

		p->first=p->first->next;
		while(p->first->next!=NULL){
			if(!compareElement(p->first->bf,x)){
				p2->first->next=p2->first->next->next;
				break;
			}

				p2->first=p2->first->next;
				p->first=p->first->next;
		}

		if(p->first->next==NULL)
			if(!compareElement(p->first->bf,x))
				p2->first->next=NULL;
	}
	free(p->first);
	free(p);
	free(p2);
	return l;
}


/*
 * Elimina un elemento dalla lista secondo un certo indice
 */
list deleteElementByIndex(list l,int index){
	int count=0;
	list p;
	p=newList();
	list p2;
	p2=newList();
    p->first=l->first;
    p2->first=l->first;

	//elimino primo elemento
	if(!isEmptyList(l)){
		l->size--;
		if(count==index){
			l->first=l->first->next;
			free(p->first);
			free(p);
			return l;
		}
		count++;
		p->first=p->first->next;
		while(p->first->next!=NULL){
			if(count==index){
				p2->first->next=p2->first->next->next;
				//free(p);
				break;
			}
				count++;
				p2->first=p2->first->next;
				p->first=p->first->next;
		}
		if(p->first->next==NULL)
			if(count==index)
				p2->first->next=NULL;
	}
	free(p->first);
	free(p);
	free(p2);
	return l;
}


/*
 * Restituisce l'indice di un elemento nella lista
 */
int indexOfElement(list l,void *bfn){

	int pos=0;
	int found=0;
	list p;
	p=newList();
	p->first=l->first;
	if(l->first==NULL)
		return -1;
	while(!isEmptyList(p)&&!found){

		if(!compareElement(p->first->bf,bfn))
			found=1;
		else{
			pos++;
			p->first=p->first->next;
		}
	}
	if(!found)
		return -1;

	free(p);
	return pos;
}

/*
 * Rimuove la seconda metà di elementi di una lista
 */
list removeLastHalf(list l,int from){

	list p;
	list p2;
	list p3;
	p=newList();
	p2=newList();
	p3=newList();
	p->first=l->first;
	int count=0;
	while(p->first->next!=NULL){
		if(count+1==from){
			p2->first=p->first->next;
			p->first->next=NULL;
			break;
		}
	p->first=p->first->next;
	count++;
	}

	l->size=count+1;
	free(p);

	while(p2->first->next!=NULL){
		p3->first=p2->first;
		p2->first=p2->first->next;
		free(p3->first);
		p3->first=p2->first;
		}
	free(p2);
	free(p3);
	return l;
}


/*
 * Aggiunge tutti gli elementi nella lista
 */
list addAll(list l,list new){

	list p;
	p=newList();
	p->first=l->first;
	if(l->first==NULL){
		free(p);
		return new;
	}
	while(p->first->next!=NULL){

		p->first=p->first->next;
	}

	if(p->first->next==NULL){

		if(new->first!=NULL){

			p->first->next=new->first;
		}
	}

	l->size=l->size+new->size;
	free(p);
	free(new);

	return l;
}




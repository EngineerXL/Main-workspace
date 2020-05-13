#include <stdio.h>
#include <stdlib.h>
#include "dequeue.h"

void create(dequeue* dq){
	dq->size=0;
	dq->data=NULL;
}

bool empty(dequeue* dq){
	return dq->size==0? true:false;
}

void push_back(dequeue* dq, int elem){
	dq->size++;
	dq->data=realloc(dq->data, sizeof(int)*dq->size);
	dq->data[dq->size-1]=elem;
}

int pop_back(dequeue* dq){
	if(empty(dq)) return -1000000007;
	dq->size--;
	int elem=dq->data[dq->size];
	dq->data=realloc(dq->data, sizeof(int)*dq->size);
	return elem;
}

void push_front(dequeue* dq, int elem){
	dq->size++;
	dq->data=realloc(dq->data, sizeof(int)*dq->size);
	for(int i=dq->size-1; i>0; i--) dq->data[i]=dq->data[i-1];
	dq->data[0]=elem;
}

int pop_front(dequeue* dq){
	if(empty(dq)) return -1000000007;
	dq->size--;
	int elem=dq->data[0];
	for(int i=0; i<dq->size; i++) dq->data[i]=dq->data[i+1];
	dq->data=realloc(dq->data, sizeof(int)*dq->size);
	return elem;
}

void print(dequeue* dq){
	for(int i=0; i<dq->size; i++) printf("%d ", dq->data[i]);
	if(empty(dq)==false) printf("\n");
}

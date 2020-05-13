#ifndef _DEQUEUE_H_
#define _DEQUEUE_H_

#include <stdlib.h>

enum boolean {false=0, true=1};

typedef enum boolean bool;

struct dequeue{
	int size;
	int* data;
};

typedef struct dequeue dequeue;

void create(dequeue* dq);

bool empty(dequeue* dq);

void push_back(dequeue* dq, int elem);

int pop_back(dequeue* dq);

void push_front(dequeue* dq, int elem);

int pop_front(dequeue* dq);

void print(dequeue* dq);

#endif
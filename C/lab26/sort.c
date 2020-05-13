#include "dequeue.h"
#include "sort.h"

void concat(dequeue* l, dequeue* r){
	while(empty(r)==false){
		push_back(l, pop_front(r));
	}
}

void sort(dequeue* dq){
	if(dq->size<2) return;
	int p=pop_back(dq);
	dequeue ldq;
	dequeue rdq;
	create(&ldq);
	create(&rdq);
	while(dq->size>1){
		int l=pop_front(dq);
		int r=pop_back(dq);
		while(l<p && empty(dq)==false){
			push_back(&ldq, l);
			l=pop_front(dq);
		}
		while(r>p && empty(dq)==false){
			push_front(&rdq, r);
			r=pop_back(dq);
		}
		if(l<p) push_back(&ldq, l);
		else push_front(&rdq, l);
		if(r<p) push_back(&ldq, r);
		else push_front(&rdq, r);
	}
	if(dq->size==1){
		int m=pop_back(dq);
		if(m<p) push_back(&ldq, m);
		else push_front(&rdq, m);
	}
	sort(&ldq);
	sort(&rdq);
	push_front(&rdq, p);
	concat(&ldq, &rdq);
	*dq=ldq;
}
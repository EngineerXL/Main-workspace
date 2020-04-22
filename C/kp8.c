#include <stdio.h>
#include <stdlib.h>

struct list{
	struct list* next;
	int data;
};

typedef struct list list;

int empty(list* lst){
	return lst==NULL;
}

list* find(list* lst, int p){
	if(empty(lst)) return NULL;
	while(p>1){
		p--;
		lst=lst->next;
	}
	return lst;
}

int len(list* lst){
	if(empty(lst)) return 0;
	list* tmp=lst;
	int length=1;
	while(lst->next!=tmp){
		length++;
		lst=lst->next;
	}
	return length;
}

void print(list* lst){
	if(empty(lst)) return;
	list* tmp=lst;
	while(lst->next!=tmp){
		printf("%d ", lst->data);
		lst=lst->next;
	}
	printf("%d\n", lst->data);
}

void append(list** lst, int p, int x){
	if(empty(*lst)){
		*lst=malloc(sizeof(list));
		(*lst)->data=x;
		(*lst)->next=*lst;
		return;
	}
	int p0=p;
	list* tmp=*lst;
	while((*lst)->next!=tmp){
		*lst=(*lst)->next;
	}
	while(p>0){
		p--;
		*lst=(*lst)->next;
	}
	list* left=*lst;
	list* right=(*lst)->next;
	list* mid=malloc(sizeof(list));
	mid->data=x;
	left->next=mid;
	mid->next=right;
	if(p0==0) *lst=mid;
	else *lst=tmp;
}

void pop(list** lst, int p){
	if(len(*lst)<=1){
		*lst=NULL;
		return;
	}
	int p0=p;
	list* tmp=*lst;
	while((*lst)->next!=tmp){
		*lst=(*lst)->next;
	}
	while(p>1){
		p--;
		*lst=(*lst)->next;
	}
	list* nnext=(*lst)->next->next;
	free((*lst)->next);
	(*lst)->next=nnext;
	if(p0==1) *lst=(*lst)->next;
	else *lst=tmp;
}

int main(){
	int n, v, p;
	scanf("%d", &n);
	list* lst=NULL;
	for(int i=0; i<n; i++){
		scanf("%d %d", &v, &p);
		append(&lst, p, v);
		//print(lst);
	}
	for(int i=0; i<n; i++){
		scanf("%d", &p);
		pop(&lst, p);
		//print(lst);
	}
	print(lst);
}
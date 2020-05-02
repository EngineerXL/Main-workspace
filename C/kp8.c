#include <stdio.h>
#include <stdlib.h>

struct list{
	struct list* next;
	int re, im;
};

typedef struct list list;

int empty(list* lst){
	return (lst==NULL? 1:0);
}

list* next(list* lst){
	if(empty(lst)) return lst;
	else return lst->next;
}

int len(list* lst){
	if(empty(lst)) return 0;
	list* begin=lst;
	int length=1;
	while(lst->next!=begin){
		lst=lst->next;
		length++;
	}
	return length;
}

list* append(list* it, int reval, int imval){
	list* elem=malloc(sizeof(list));
	elem->re=reval;
	elem->im=imval;
	if(empty(it)){
		elem->next=elem;
		return elem;
	}else{
		elem->next=it->next;
		it->next=elem;
		return it;
	}
}

list* pop(list* it){
	if(empty(it)) return NULL;
	list* begin=it;
	while(it->next!=begin) it=it->next;
	list* end=it;
	if(it==begin) return NULL;
	it->next=begin->next;
	free(begin);
	return end->next;
}

list* insert(list* lst, int p, int reval, int imval){
	if(empty(lst)) return append(lst, reval, imval);
	list* elem=malloc(sizeof(list));
	elem->re=reval;
	elem->im=imval;

	list* begin=lst;
	while(lst->next!=begin) lst=lst->next;
	for(int i=0; i<p; i++) lst=lst->next;
	lst=append(lst, reval, imval);
	if(p==0) begin=lst->next;
	return begin;
}

void print(list* lst, list* it){
	if(empty(lst)) return;
	list* begin=lst;
	while(lst->next!=begin){
		if(lst==it) printf("> %d+%di < ", lst->re, lst->im);
		else printf("%d+%di ", lst->re, lst->im);
		lst=lst->next;
	}
	if(lst==it) printf("> %d+%di <\n", lst->re, lst->im);
	else printf("%d+%di\n", lst->re, lst->im);
}

void swap(list** lst, list** it){
	if(empty(*lst)) return;
	list* begin=*lst;
	int n=len(*lst);
	while((*lst)->next!=begin) *lst=(*lst)->next;
	begin=(*lst)->next->next;	
	for(int i=0; i<n/2; i++){
		list* elem1=(*lst)->next;
		list* elem2=(*lst)->next->next;
		if(*it==elem1 || *it==elem2){
			if(*it==elem1) *it=elem2;
			else *it=elem1;
		}
		(*lst)->next=elem2;
		elem1->next=elem2->next;
		elem2->next=elem1;
		*lst=(*lst)->next->next;
	}
	*lst=begin;
}

void help(){
	printf("h - show this message\n");
	printf("f - go to the first element\n");
	printf("n - go to the next element\n");
	printf("a - insert element next to the curent ones\n");
	printf("l - print length of the list\n");
	printf("p - pop curent element\n");
	printf("i - insert element by position\n");
	printf("s - swap elements\n");
}

signed main(){
	list* lst=NULL;
	list* it=lst;
	char c;
	int p, reval, imval;
	help();
	while(scanf("%c", &c)>0){
		if(c==' ' || c=='\n' || c=='\t') continue;
		if(c=='h') help();
		if(c=='f') it=lst;
		if(c=='n') it=next(it);
		if(c=='a'){
			scanf("%d %d", &reval, &imval);
			if(empty(lst)) lst=append(lst, reval, imval);
			else it=append(it, reval, imval);
		}
		if(c=='l') printf("%d\n", len(lst));
		if(c=='p'){
			if(lst==it){
				lst=pop(lst);
				it=lst;
			}
			else it=pop(it);
		}
		if(c=='i'){
			scanf("%d %d %d", &p, &reval, &imval);
			lst=insert(lst, p, reval, imval);
		}
		if(c=='s') swap(&lst, &it);
		if(!empty(lst) && empty(it)) it=lst;
		print(lst, it);
	}
}
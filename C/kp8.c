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
	if(it==begin) return NULL;
	it->next=begin->next;
	free(begin);
	return it;
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

signed main(){
	list* lst=NULL;
	list* it=lst;
	char c;
	int p, reval, imval;
	while(scanf("%c", &c)>0){
		if(c==' ' || c=='\n' || c=='\t') continue;
		if(c=='n') it=next(it);
		if(c=='a'){
			scanf("%d %d", &reval, &imval);
			if(empty(lst)) lst=append(lst, reval, imval);
			else it=append(it, reval, imval);
		}
		if(c=='l') printf("%d\n", len(lst));
		if(c=='p'){
			if(lst==it) lst=pop(lst);
			else it=pop(it);
		}
		if(c=='i'){
			scanf("%d %d %d", &p, &reval, &imval);
			lst=insert(lst, p, reval, imval);
		}
		if(!empty(lst) && empty(it)) it=lst;
		print(lst, it);
	}
}
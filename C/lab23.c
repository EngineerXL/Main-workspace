#include <stdio.h>
#include <stdlib.h>

struct node{
	struct node* son;
	struct node* bro;
	int re, im;
};

typedef struct node node;

node* insert(node* cur, char* path, int it, int n, int reval, int imval){
	if(cur==NULL){
		cur=malloc(sizeof(node));
		cur->re=reval;
		cur->im=imval;
		cur->son=NULL;
		cur->bro=NULL;
		return cur;
	}
	
	if(it==n){
		if(cur->son==NULL) cur->son=insert(cur->son, path, it, n, reval, imval);
		else{
			node* ccur=cur;
			cur=cur->son;
			while(cur->bro!=NULL) cur=cur->bro;
			cur->bro=insert(cur->bro, path, it, n, reval, imval);
			cur=ccur;
		}
		return cur;
	}
	if(path[it]=='b') cur->bro=insert(cur->bro, path, it+1, n, reval, imval);
	else cur->son=insert(cur->son, path, it+1, n, reval, imval);
	return cur;
}

node* delete(node* cur){
	if(cur==NULL) return NULL;
	cur->son=delete(cur->son);
	cur->bro=delete(cur->bro);
	free(cur);
	return NULL;
}

node* erase(node* cur, char* path, int it, int n){
	if(cur==NULL) return NULL;
	if(it==n){
		cur->son=delete(cur->son);
		node* ccur=cur->bro;
		free(cur);
		return ccur;
	}
	if(path[it]=='b') cur->bro=erase(cur->bro, path, it+1, n);
	else cur->son=erase(cur->son, path, it+1, n);
	return cur;
}

void print(node* cur, int d){
	if(cur==NULL) return;
	for(int i=0; i<2*d; i++) printf("-");
	printf("%d+%di\n", cur->re, cur->im);
	print(cur->son, d+1);
	print(cur->bro, d);
}

void treecount(node* cur, int *treedeg, int *count, int curdegree){
	if(cur==NULL) return;
	treecount(cur->son, treedeg, count, 0);
	treecount(cur->bro, treedeg, count, 0);
	if(cur->son!=NULL){
		curdegree=1;
		node* tmp=cur->son;
		while(tmp->bro!=NULL){
			curdegree++;
			tmp=tmp->bro;
		}
	}
	if(curdegree==*treedeg) (*count)++;
	if(curdegree>*treedeg){
		*treedeg=curdegree;
		*count=1;
	}
}

signed main(){
	int reval, imval, n, treedeg, count;
	char c;
	char* path=NULL;
	node* root=NULL;
	while(scanf("%c", &c)>0){
		if(c==' ' || c=='\n' || c=='\t') continue;
		if(c=='i'){
			scanf("%d %d", &reval, &imval);
			n=0;
			while(scanf("%c", &c)>0){
				if(c==' ' || c=='\t') continue;
				if(c=='b' || c=='s'){
					n++;
					path=realloc(path, sizeof(char)*n);
					path[n-1]=c;
				}else break;				
			}
			root=insert(root, path, 0, n, reval, imval);
			free(path);
			path=NULL;
		}
		if(c=='e'){
			n=0;
			while(scanf("%c", &c)>0){
				if(c==' ' || c=='\t') continue;
				if(c=='b' || c=='s'){
					n++;
					path=realloc(path, sizeof(char)*n);
					path[n-1]=c;
				}else break;				
			}
			root=erase(root, path, 0, n);
			free(path);
			path=NULL;
		}
		if(c=='c'){
			treedeg=0, count=0;
			treecount(root, &treedeg, &count, 0);
			printf("%d %d\n", treedeg, count);
		}
		if(c=='p') print(root, 0);
	}
}
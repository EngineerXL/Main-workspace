#include <stdio.h>
#include <stdlib.h>

struct node{
	int value;
	struct node *left;
	struct node *right;
};

typedef struct node node;

node* insert(node* cur, int val){
	if(cur==NULL){
		cur=malloc(sizeof(node));
		cur->left=NULL;
		cur->right=NULL;
		cur->value=val;
		return cur;
	}
	if(val>=cur->value) cur->right=insert(cur->right, val);
	else cur->left=insert(cur->left, val);
	return cur;
}

node* delete(node* cur){
	if(cur->left==NULL && cur->right==NULL){
		free(cur);
		return NULL;
	}
	if(cur->left==NULL){
		node* ccur=cur->right;
		free(cur);
		return ccur;
	}
	if(cur->right==NULL){
		node* ccur=cur->left;
		free(cur);
		return(ccur);
	}
	node* ccur=cur;
	node* prev=cur;
	cur=cur->right;
	while(cur->left!=NULL){
		prev=cur;
		cur=cur->left;
	}
	ccur->value=cur->value;
	if(prev->right==cur) prev->right=delete(cur);
	else prev->left=delete(cur);
	return ccur;
}

node* erase(node* cur, int val){
	if(cur==NULL) return NULL;
	if(cur->value==val){
		cur=delete(cur);
		return cur;
	}
	if(val>cur->value) cur->right=erase(cur->right, val);
	if(val<cur->value) cur->left=erase(cur->left, val);
	return cur;
}

void print(node* cur, int d){
	if(cur==NULL) return;
	for(int i=0; i<d; i++) printf("--");
	printf("%d\n", cur->value);
	print(cur->left, d+1);
	print(cur->right, d+1);
}

signed main(){
	int val;
	char c;
	node* root=NULL;
	while(scanf("%c", &c)>0){
		if(c==' ' || c=='\n' || c=='\t') continue;
		if(c=='i'){
			scanf("%d", &val);
			root=insert(root, val);
		}
		if(c=='e'){
			scanf("%d", &val);
			root=erase(root, val);
		}
		if(c=='p') print(root, 0);
	}
}
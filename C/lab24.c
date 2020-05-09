#include <stdio.h>
#include <stdlib.h>

enum boolean {false=0, true=1};

typedef enum boolean bool;

long long binpow(long long x, long long y){
	long long z=1;
	while(y>0){
		if(y&1) z=z*x; 
		x=x*x;
		y=y>>1;
	}
	return z;
}

enum operator {sum=0, diference=1, multiplication=2, division=3, power=4};

typedef enum operator operator;

enum bracket {open=0, close=1};

typedef enum bracket bracket;

union item{
	long long val;
	operator op;
	bracket br;
	char var;
};

typedef union item item;

struct token{
	int type;
	item elem;
};

typedef struct token token;

void print(token tok){
	if(tok.type==1) printf("%lli", tok.elem.val);
	if(tok.type==2){
		if(tok.elem.op==sum) printf("+");
		if(tok.elem.op==diference) printf("-");
		if(tok.elem.op==multiplication) printf("*");
		if(tok.elem.op==division) printf("/");
		if(tok.elem.op==power) printf("^");
	}
	if(tok.type==3) printf("%c", (tok.elem.br==open? '(':')'));
	if(tok.type==4) printf("%c", tok.elem.var);
}

struct vector{
	int n;
	token* data;
};

typedef struct vector vector;

vector create(vector vect, int n_){
	vect.n=n_;
	vect.data=malloc(sizeof(token)*vect.n);
	return vect;
}

vector push_back(vector vect, token tok){
	vect.n++;
	vect.data=realloc(vect.data, sizeof(token)*vect.n);
	(vect.data)[vect.n-1]=tok;
	return vect;
}

struct node{
	struct node* left;
	struct node* right;
	token data;
	long long res;
	bool calculatable;
};

typedef struct node node;

node* build(node* cur, vector* v, int l, int r){
	if(l==r){
		cur=malloc(sizeof(node));
		cur->data=(*v).data[r];
		cur->left=NULL;
		cur->right=NULL;
		cur->res=0;
		cur->calculatable=false;
		return cur;
	}
	if(l+1==r){
		cur=malloc(sizeof(node));
		cur->data=(*v).data[l];
		cur->left=NULL;
		cur->right=build(cur->right, v, l+1, r);
		cur->res=0;
		cur->calculatable=false;
		return cur;
	}
	int* index=malloc(sizeof(int)*(r-l+2));
	index[0]=0;
	int flag=-1;
	for(int i=1; i<r-l+2; i++){
		index[i]=index[i-1];
		if((*v).data[l+i-1].type==1 || (*v).data[l+i-1].type==4) index[i]++;
		if((*v).data[l+i-1].type==2) index[i]--;
		if((*v).data[l+i-1].type==3 && (*v).data[l+i-1].elem.br==close) index[i]--;
		if((*v).data[l+i-1].type==3 && (*v).data[l+i-1].elem.br==open) index[i]++;
	}
	for(int i=r-l+1; i>0; i--){
		if(flag!=-1) break;
		if(flag==-1 && index[i]==0 && (*v).data[l+i-1].type==2 && ((*v).data[l+i-1].elem.op==sum || (*v).data[l+i-1].elem.op==diference)) flag=l+i-1;
	}
	for(int i=r-l+1; i>0; i--){
		if(flag!=-1) break;
		if(flag==-1 && index[i]==0  && (*v).data[l+i-1].type==2 && ((*v).data[l+i-1].elem.op==multiplication || (*v).data[l+i-1].elem.op==division)) flag=l+i-1;
	}
	for(int i=1; i<r-l+2; i++){
		if(flag!=-1) break;
		if(flag==-1 && index[i]==0 && (*v).data[l+i-1].type==2 && (*v).data[l+i-1].elem.op==power) flag=l+i-1;
	}
	if(flag==-1) return build(cur, v, l+1, r-1);
	cur=malloc(sizeof(node));
	cur->left=build(cur->left, v, l, flag-1);
	cur->right=build(cur->right, v, flag+1, r);
	cur->data=(*v).data[flag];
	cur->res=0;
	cur->calculatable=false;
	free(index);
	return cur;
}

bool asociate(node* cur, int optype){
	if((cur->data).type==2 && (cur->data).elem.op==optype){
		return asociate(cur->left, optype) | asociate(cur->right, optype);
	}
	return cur->calculatable;
}

node* add(node* cur, int optype, long long val){
	if(cur->calculatable){
		cur->res=(optype==0? cur->res+val:cur->res*val);
		(cur->data).elem.val=cur->res;
		return cur;
	}
	if((cur->data).type==2 && (cur->data).elem.op==optype){

		if(asociate(cur->left, optype)) cur->left=add(cur->left, optype, val);
		else cur->right=add(cur->right, optype, val);
	}
	return cur;
}

node* copy(node* cur){
	if(cur==NULL) return NULL;
	node* ans=malloc(sizeof(node));
	ans->data=cur->data;
	ans->res=cur->res;
	ans->calculatable=cur->calculatable;
	ans->left=copy(cur->left);
	ans->right=copy(cur->right);
	return ans;
}

node* delete(node* cur){
	if(cur==NULL) return NULL;
	cur->left=delete(cur->left);
	cur->right=delete(cur->right);
	free(cur);
	return cur;
}

node* fmult(node* cur, node* factor){
	if((cur->data).type==2 && ((cur->data).elem.op==sum || (cur->data).elem.op==diference)){
		cur->right=fmult(cur->right, factor);
		cur->left=fmult(cur->left, factor);
		return cur;
	}else{
		node* mmult=malloc(sizeof(node));
		(mmult->data).type=2;
		(mmult->data).elem.op=multiplication;
		mmult->right=cur;
		mmult->left=copy(factor);
		mmult->calculatable=false;
		return mmult;
	}
}

node* calc(node* cur){
	if((cur->data).type==1){
		cur->res=(cur->data).elem.val;
		cur->calculatable=true;
	}
	if((cur->data).type==2){
		if((cur->data).elem.op==multiplication && (cur->right->data).type==2 && ((cur->right->data).elem.op==sum || (cur->right->data).elem.op==diference)){
			cur->right=fmult(cur->right, cur->left);
			node* ccur=cur->right;
			cur->left=delete(cur->left);
			free(cur);
			return calc(ccur);
		}
		if((cur->data).elem.op==multiplication && (cur->left->data).type==2 && ((cur->left->data).elem.op==sum || (cur->left->data).elem.op==diference)){
			cur->left=fmult(cur->left, cur->right);
			node* ccur=cur->left;
			cur->right=delete(cur->right);
			free(cur);
			return calc(ccur);
		}
		cur->left=calc(cur->left);
		cur->right=calc(cur->right);
		cur->calculatable=(cur->left->calculatable)&(cur->right->calculatable);
		if(cur->calculatable==false){
			if((cur->data).elem.op==diference || (cur->data).elem.op==division || (cur->data).elem.op==power || ((cur->right->calculatable)==false && (cur->left->calculatable)==false)) return cur;
			if(cur->right->calculatable==true){
				if(asociate(cur->left, (cur->data).elem.op)){
					cur->left=add(cur->left, (cur->data).elem.op, cur->right->res);
					node* ccur=cur->left;
					free(cur->right);
					free(cur);
					return ccur;
				}
			}else{
				if(asociate(cur->right, (cur->data).elem.op)){
					cur->right=add(cur->right, (cur->data).elem.op, cur->left->res);
					node* ccur=cur->right;
					free(cur->left);
					free(cur);
					return ccur;
				}
			}
			return cur;
		}
		long long l=cur->left->res;
		long long r=cur->right->res;
		if((cur->data).elem.op==sum) cur->res=l+r;
		if((cur->data).elem.op==diference) cur->res=l-r;
		if((cur->data).elem.op==multiplication) cur->res=l*r;
		if((cur->data).elem.op==division) cur->res=l/r;
		if((cur->data).elem.op==power) cur->res=binpow(l, r);
		free(cur->left);
		free(cur->right);
		cur->left=NULL;
		cur->right=NULL;
		(cur->data).type=1;
		(cur->data).elem.val=cur->res;
	}
	return cur;
}

node* multiply(node* f, node* g){
	if(f==NULL || g==NULL) return NULL;
	node* ans=malloc(sizeof(node));
	(ans->data).type=2;
	(ans->data).elem.op=multiplication;
	ans->left=copy(f);
	ans->right=copy(g);
	ans->res=0;
	ans->calculatable=false;
	return ans;
}

void printt(node* cur){
	if(cur==NULL) return;
	if(!(((cur->data).type==1 && (cur->data).elem.val>=0) || (cur->data).type==4)) printf("(");
	printt(cur->left);
	print(cur->data);
	printt(cur->right);
	if(!(((cur->data).type==1 && (cur->data).elem.val>=0) || (cur->data).type==4)) printf(")");
}

signed main(){
	node* f=NULL;
	node* g=NULL;
	char c;
	short mult=1;
	vector v;
	token cur;
	cur.type=0;
	v=create(v, 0);
	while(scanf("%c", &c)>0){
		if(c=='#'){
			if(cur.type>0){
				if(cur.type==1) cur.elem.val*=mult;
				if(cur.type==4){
					if(mult<0){
						cur.type=1;
						cur.elem.val=-1;
						v=push_back(v, cur);
						cur.type=2;
						cur.elem.op=multiplication;
						v=push_back(v, cur);
					}
				}
				v=push_back(v, cur);
			}
			f=build(f, &v, 0, v.n-1);
			free(v.data);
			v=create(v, 0);
			mult=1;
			cur.type=0;
			continue;
		}
		if(c=='\n' || c=='\t' || c==' ') continue;
		if('0'<=c && c<='9'){
			if(cur.type==1){
				cur.elem.val=10*cur.elem.val+c-'0';
			}else{
				cur.type=1;
				cur.elem.val=c-'0';
			}
			continue;
		}
		if(c=='+' || c=='-'){
			if(cur.type==1){
				cur.elem.val*=mult;
				v=push_back(v, cur);
				mult=1;
			}
			if(v.data[v.n-1].type==2 || v.n==0 ||(v.data[v.n-1].type==3 && v.data[v.n-1].elem.br==open)){
				mult*=(c=='+'? 1:-1);
			}else{
				cur.type=2;
				cur.elem.op=(c=='+'? sum:diference);
				v=push_back(v, cur);
				cur.type=0;
			}
			continue;
		}
		if(c=='*' || c=='/' || c=='^'){
			if(cur.type==1){
				cur.elem.val*=mult;
				v=push_back(v, cur);
				mult=1;
			}
			cur.type=2;
			if(c=='*') cur.elem.op=multiplication;
			if(c=='/') cur.elem.op=division;
			if(c=='^') cur.elem.op=power;
			v=push_back(v, cur);
			cur.type=0;
			continue;
		}
		if(c=='(' || c==')'){
			if(cur.type==1){
				cur.elem.val*=mult;
				v=push_back(v, cur);
				mult=1;
			}
			if(c=='(' && mult<0){
				cur.type=1;
				cur.elem.val=-1;
				v=push_back(v, cur);
				cur.type=2;
				cur.elem.op=multiplication;
				v=push_back(v, cur);
				mult=1;
			}
			cur.type=3;
			cur.elem.br=(c=='('? open:close);
			v=push_back(v, cur);
			cur.type=0;
			continue;
		}
		if(mult<0){
			cur.type=3;
			cur.elem.br=open;
			v=push_back(v, cur);
			cur.type=1;
			cur.elem.val=-1;
			v=push_back(v, cur);
			cur.type=2;
			cur.elem.op=multiplication;
			v=push_back(v, cur);
			cur.type=4;
			cur.elem.var=c;
			v=push_back(v, cur);
			cur.type=3;
			cur.elem.br=close;
			v=push_back(v, cur);
			mult=1;
			
		}else{
			cur.type=4;
			cur.elem.var=c;
			v=push_back(v, cur);
		}
		cur.type=0;		
	}
	if(cur.type>0){
		if(cur.type==1) cur.elem.val*=mult;
		if(cur.type==4){
			if(mult<0){
				cur.type=1;
				cur.elem.val=-1;
				v=push_back(v, cur);
				cur.type=2;
				cur.elem.op=multiplication;
				v=push_back(v, cur);
			}
		}
		v=push_back(v, cur);
	}
	g=build(g, &v, 0, v.n-1);
	printf("YOUR INPUT:\n");
	printt(f);
	printf("\n");
	printt(g);
	printf("\n");
	f=calc(f);
	g=calc(g);
	printf("CALC\n");
	printt(f);
	printf("\n");
	printt(g);
	printf("\n");
	node* ans=multiply(f, g);
	printf("YOUR MULT:\n");
	printt(ans);
	printf("\n");
	ans=calc(ans);
	printf("CALC\n");
	printt(ans);
	printf("\n");
}
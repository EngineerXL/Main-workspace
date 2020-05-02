#include <stdio.h>
#include <stdlib.h>

const double e0=1e-6;

enum boolean {true=1, false=0};

typedef enum boolean bool;

struct field{
	int index;
	double value;
	int next;
};

typedef struct field field;

struct vector_int{
	int n;
	int *data;
};

typedef struct vector_int vectorInt;

void vi_create(vectorInt *vector, int n_){
	vector->n=n_;
	vector->data=malloc(n_*sizeof(int));
}

void vi_push_back(vectorInt *vector, int x){
	vector->n++;
	vector->data=realloc(vector->data, vector->n*sizeof(int));
	vector->data[vector->n-1]=x;
}

void vi_print(vectorInt *vector){
	printf("PRINTING VECTORINT\n");
	for(int i=0; i<vector->n; i++) printf("%d ", vector->data[i]);
	printf("\n");
}

struct vector_field{
	int n;
	field *data;
};

typedef struct vector_field vectorField;

void vf_create(vectorField *vector, int n_){
	vector->n=n_;
	vector->data=malloc(n_*sizeof(field));
}

void vf_push_back(vectorField *vector, field x){
	vector->n++;
	vector->data=realloc(vector->data, vector->n*sizeof(field));
	vector->data[vector->n-1]=x;
}

void vf_print(vectorField *vector){
	printf("PRINTING VECTORFIELD\n");
	for(int i=0; i<vector->n; i++) printf("%d %lf %d ", vector->data[i].index, vector->data[i].value, vector->data[i].next);
	printf("\n");
}

void print_matrix(vectorInt *vi, vectorField *vf, int n, int m){
	printf("PRINTING MATRIX\n");
	for(int i=0; i<n; i++){
		if(vi->data[i]==-1){
			for(int j=0; j<m; j++) printf("0.0 ");
		}else{
			field k=vf->data[vi->data[i]];
			bool endStr=false;
			for(int j=0; j<m; j++){
				if(endStr==false && j==k.index){
					printf("%.1lf ", k.value);
					if(k.next==-1) endStr=true;
					else k=vf->data[k.next];
				}else printf("0.0 ");
			}
		}
		printf("\n");
	}
}

double myabs(double x){
	if(x<e0) return -x;
	else return x;
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	vectorInt a;
	vi_create(&a, 0);
	vectorField b;
	vf_create(&b, 0);
	double x;
	for(int i=0; i<n; i++){
		bool isNull=true;
		for(int j=0; j<m; j++){
			scanf("%lf", &x);
			if(myabs(x)>e0){
				if(isNull) vi_push_back(&a, b.n);
				if(isNull==false) b.data[b.n-1].next=b.n;
				isNull=false;
				field toPush={j, x, -1};
				vf_push_back(&b, toPush);
			}
		}
		if(isNull) vi_push_back(&a, -1);
	}
	vi_print(&a);
	vf_print(&b);
	print_matrix(&a, &b, n, m);
	double prevMaxElem=1e9+7, lastMaxElem=0;
	int prevCol=-1, lastCol=-1;
	for(int i=0; i<b.n; i++){
		if(myabs(b.data[i].value)-myabs(lastMaxElem)>e0){
					lastMaxElem=b.data[i].value;
					prevMaxElem=1e9+7;
					lastCol=b.data[i].index;
					prevCol=-1;
				}
				if(myabs(myabs(b.data[i].value)-myabs(lastMaxElem))<e0){
					if(b.data[i].index>lastCol){
						prevMaxElem=lastMaxElem;
						lastMaxElem=b.data[i].value;
						prevCol=lastCol;
						lastCol=b.data[i].index;
					}else{
						if(b.data[i].index!=lastCol && b.data[i].index>prevCol){
							prevMaxElem=b.data[i].value;
							prevCol=b.data[i].index;
						}
					}
				}
		//printf("%d %lf %d %lf\n", lastCol, lastMaxElem, prevCol, prevMaxElem);
	}
	if(prevCol==-1){
		prevCol=lastCol;
		prevMaxElem=lastMaxElem;
	}
	for(int i=0; i<b.n; i++){
		if(b.data[i].index==prevCol) b.data[i].value/=prevMaxElem;
	}
	printf("PRINTING MAX %lf %d\n", prevMaxElem, prevCol);
	vi_print(&a);
	vf_print(&b);
	print_matrix(&a, &b, n, m);
	return 0;
}


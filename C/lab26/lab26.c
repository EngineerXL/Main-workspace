#include <stdio.h>
#include "dequeue.h"
#include "sort.h"

void help(){
	printf("h - show this message\n");
	printf("w - print all dequeue elements\n");
	printf("p - push element at the end of dequeue\n");
	printf("t - pop element from the end of dequeue\n");
	printf("a - push element at the beginning of dequeue\n");
	printf("b - pop element from the beginning of dequeue\n");
	printf("s - sort dequeue\n");
}

signed main(){
	char c;
	int num=-1000000007;
	dequeue dq;
	create(&dq);
	help();
	while(scanf("%c", &c)>0){
		if(c==' ' || c=='\n' || c=='\t') continue;
		if(c=='h') help();
		if(c=='w') print(&dq);
		if(c=='p'){
			scanf("%d", &num);
			push_back(&dq, num);
		}
		if(c=='t'){
			num=pop_back(&dq);
			if(num>-1000000007)	printf("%d\n", num);
		}
		if(c=='a'){
			scanf("%d", &num);
			push_front(&dq, num);
		}
		if(c=='b'){
			num=pop_front(&dq);
			if(num>-1000000007)	printf("%d\n", num);
		}
		if(c=='s') sort(&dq);
	}
}
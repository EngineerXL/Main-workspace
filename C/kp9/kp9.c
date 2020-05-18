#include <stdio.h>
#include <stdlib.h>

enum boolean { false = 0, true = 1 };

typedef enum boolean bool;

struct string {
	char* data;
	int size;
};

typedef struct string string;

void create(string* s) {
	s->data = NULL;
	s->size = 0;
}

void append(string* s, char c) {
	s->size++;
	s->data = realloc(s->data, sizeof(char) * s->size);
	s->data[s->size - 1] = c;
}

void print(string* s) {
	for(int i = 0; i < s->size; i++) {
		printf("%c", s->data[i]);
	}
	printf("\n");
}

struct field {
	int key;
	string value;
};

typedef struct field field;

void clear(field* arr, int n) {
	for(int i = 0; i < n; i++)
		free(arr[i].value.data);
	free(arr);
	arr = NULL;
}

bool check_sorted(field* arr, int n) {
	for(int i = 0; i < n - 1; i++) {
		if(arr[i].key > arr[i + 1].key)
			return false;
	}
	return true;
}

bool check_reverse_sorted(field* arr, int n) {
	for(int i = 0; i < n - 1; i++) {
		if(arr[i].key < arr[i + 1].key)
			return false;
	}
	return true;
}

void find(field* arr, int n, int num) {
	if(check_sorted(arr, n) == false)
		return;
	int l = 0, r = n;
	while(l + 1 < r) {
		int m = (l + r) / 2;
		if(arr[m].key > num)
			r = m;
		else
			l = m;
	}
	if(arr[l].key == num) {
		while(arr[l].key == num)
			l--;
		l++;
		while(arr[l].key == num) {
			printf("%d ", arr[l].key);
			print(&arr[l].value);
			l++;
		}
	}
}

long long SEED = 1;

long long rnd() {
	SEED = (SEED * 11235813 + 123456789) % 1000000007;
	return SEED;
}

void swap(field* l, field* r) {
	field m = *l;
	*l = *r;
	*r = m;
}

void shuffle(field* arr, int n) {
	for(int i = 0; i < n; i++)
		swap(&arr[i], &arr[rnd() % (n - i)]);
}

void reverse(field* arr, int n) {
	for(int i = 0; i < n / 2; i++)
		swap(&arr[i], &arr[n-1-i]);
}

void sort(field* arr, int n) {
	if(check_sorted(arr, n) == true)
		return;
	if(check_reverse_sorted(arr, n) == true) {
		reverse(arr, n);
		return;
	}
	field* tmp = malloc(sizeof(field) * n);
	for(int i = 0; i < n; i++) {
		int count1 = 0, count2 = 0;
		for(int j = 0; j < n; j++) {
			if(i!=j && arr[j].key < arr[i].key)
				count1++;
			if(j < i && arr[j].key == arr[i].key)
				count2++;
		}
		tmp[count1 + count2] = arr[i];
	}
	for(int i = 0; i < n; i++)
		arr[i] = tmp[i];
	free(tmp);
}

void help() {
	printf("h - show this message\n");
	printf("r - read from files\n");
	printf("p - print\n");
	printf("d - randomize\n");
	printf("v - reverse\n");
	printf("f - find by key\n");
	printf("s - sort by keys\n");
}

signed main() {
	char c;
	int n = 0;
	field* arr = NULL;
	help();
	while(scanf("%c", &c) > 0) {
		if(c == ' ' || c == '\t' || c == '\n')
			continue;
		if(c == 'h')
			help();
		if(c == 'r') {
			scanf("%c", &c);
			string p1;
			create(&p1);
			while(scanf("%c", &c) > 0) {
				if(c == ' ' || c == '\t')
					break;
				append(&p1, c);
			}
			string p2;
			create(&p2);
			while(scanf("%c", &c) > 0) {
				if(c == ' ' || c == '\t' || c == '\n')
					break;
				append(&p2, c);
			}
			FILE* f1 = NULL;
			f1 = fopen(p1.data, "r");
			FILE* f2 = NULL;
			f2 = fopen(p2.data, "r");
			if(f1 == NULL || f2 == NULL) {
				printf("Invalid input\n");
				continue;
			}
			clear(arr, n);
			n = 0;
			int num;
			while(fscanf(f1, "%d", &num) > 0)
				n++;
			arr = malloc(sizeof(field) * n);
			fclose(f1);
			f1 = fopen(p1.data, "r");
			for(int i = 0; i < n; i++) {
				fscanf(f1, "%d", &arr[i].key);
				create(&arr[i].value);
				while(fscanf(f2, "%c", &c) > 0) {
					if(c == '\n')
						break;
					append(&arr[i].value, c);
				}
			}
		}
		if(c == 'p') {
			if(arr == NULL)
				continue;
			for(int i = 0; i < n; i++) {
				printf("%d ", arr[i].key);
				print(&arr[i].value);
			}
		}
		if(c == 'd')
			shuffle(arr, n);
		if(c == 'v')
			reverse(arr, n);
		if(c == 'f') {
			int num;
			scanf("%d", &num);
			find(arr, n, num);
		}
		if(c == 's')
			sort(arr, n);
	}
}
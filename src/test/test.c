#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../quicksort/quicksort.h"

#define SIZE	100000

int cmpInt(const void *a,const void *b){
	return *(int*)a - *(int*)b;
}

void printArr(const char *formatter,int amount, int elemSize,const void *arr){
	char *p = (char*)arr;	
	while(amount--){
		printf(formatter,*(int*)p);
		p += elemSize;
	}
	printf("\n");
}

void fill(int *a,int *b,int *c,int n){
	int i;
	for(i = 0;i < n;i++){
		c[i] = a[i] = b[i] = rand();
	}
}


int main(){

	srand(time(NULL));
	int a[SIZE],b[SIZE],c[SIZE];
	int n,rounds;
	rounds = 100;
	while(rounds--){
		n = rand()%SIZE;
		fill(a,b,c,n);
		quicksort(a,n,sizeof(int),cmpInt);
		qsort(b,n,sizeof(int),cmpInt);	
		if(memcmp(a,b,n) != 0){
			printf("Test failed %d\n",n);
			printArr("%d, ",n,sizeof(int),c);
			printf("quicksort:\t");
			printArr("%d ",n,sizeof(int),a);
			printf("qsort:\t");
			printArr("%d ",n,sizeof(int),b);
			return 1;
		}	
	}
	printf("Test OK\n");
	return 0;

}



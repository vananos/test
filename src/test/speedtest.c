#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "../quicksort/quicksort.h"

#define SIZE			100000
#define MAXTYPESIZE		32
#define ROUNDS			15

static char a[SIZE],b[SIZE],c[SIZE];
long size;


int cmp(const void *a,const void *b){
	return memcmp(a,b,size);
}



void fill(char *a,char *b,char *c,long n){
	int i;
	for(i = 0;i < n;i++){
		c[i] = a[i] = b[i] = rand()%0xFF;
	}
}

double time_diff(struct timeval x , struct timeval y)
{
    double x_ms , y_ms , diff;
     
    x_ms = (double)x.tv_sec*1000000 + (double)x.tv_usec;
    y_ms = (double)y.tv_sec*1000000 + (double)y.tv_usec;
     
    diff = (double)y_ms - (double)x_ms;
     
    return diff;
}




int main(){

	srand(time(NULL));
	struct timeval before , after;
	long elements,i;
	double myqt,qt;	
	printf("size\telements\tquicksort\tqsort\n");
	for(size = 1; size < MAXTYPESIZE;size <<= 1){
		for(elements = 1;elements < SIZE/size;elements <<= 2){
			i = ROUNDS;
			myqt = qt = 0;
			while(i--){
				fill(a,b,c,elements*size);
				gettimeofday(&before , NULL);
				quicksort(a,elements,size,cmp);
				gettimeofday(&after , NULL);
				myqt += time_diff(before,after);
				gettimeofday(&before , NULL);
				qsort(b,elements,size,cmp);
				gettimeofday(&after , NULL);
				qt += time_diff(before,after);
			}
			myqt /= ROUNDS;
			qt /= ROUNDS;
			printf("%d;%d;%f;%f\n",size,elements,myqt,qt);
		}
	}
	for(size = 1; size < MAXTYPESIZE;size += 2){
		for(elements = 1;elements < SIZE/size;elements <<= 2){
			i = ROUNDS;
			myqt = qt = 0;
			while(i--){
				fill(a,b,c,elements*size);
				gettimeofday(&before , NULL);
				quicksort(a,elements,size,cmp);
				gettimeofday(&after , NULL);
				myqt += time_diff(before,after);
				gettimeofday(&before , NULL);
				qsort(b,elements,size,cmp);
				gettimeofday(&after , NULL);
				qt += time_diff(before,after);
			}
			myqt /= ROUNDS;
			qt /= ROUNDS;
			printf("%d;%d;%f;%f\n",size,elements,myqt,qt);
		}
	}
	
	return 0;	
}



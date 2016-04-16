#include <stdlib.h>
#include "quicksort.c"

typedef  int(*cmp_function)(const void *,const void *); 

extern void quicksort(void *,size_t,size_t,cmp_function cmp);


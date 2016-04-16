#include <stdlib.h>

typedef int(*cmp_function)(const void *,const void *);


typedef struct {
	char *l,*r;
}borders;

#define STACKSIZE	64
#define push(x,y)	stack[top].l = x;stack[top++].r = y;
#define pop()		l = stack[--top].l;r = stack[top].r;
#define	empty()		(top <= 0)

#define INSERTSORT	8


#define SWAP(a,b,T)	register size_t _a;												\
						register T	*__l = (T*)(a);									\
						register T *__r = (T*)(b);									\
						register T tmp;												\
						for(_a = n;_a%sizeof(T);_a--){								\
							tmp = *(char*)__l;										\
							*(char*)__l = *(char*)__r;								\
							*(char*)__r = tmp;										\
							__l = (T*)((char*)__l + 1);								\
							__r = (T*)((char*)__r + 1);								\
						}															\
						for(;_a  >= sizeof(T);_a -= sizeof(T)){						\
							tmp = *__l;												\
							*__l++ = *__r;											\
							*__r++ = tmp;											\
						}															\

#define 			_swap(x,y,n,type)												\
					if(type == 2){													\
						register long tmp = *(long*)(x);							\
						*(long*)(x) = *(long*)(y);									\
						*(long*)(y) = tmp;											\
					}else															\
						swap(x,y,n,type);

#define SWAPTYPE(a)	a > sizeof(long)?1:a==sizeof(long)?2:0;
							

inline void swap(char *a, char *b, size_t n, int type){
	if(type == 1){
		SWAP(a,b,long);
	}else{
		SWAP(a,b,int);
	}
}

inline void insertionsort(char *l, char *r, size_t es,int stype, cmp_function cmp){
	char *i = l;
	char *j = l;
	for(i += es; i <= r;i += es)
		if(cmp(i,j) < 0)
			j = i;
	if(j != l)
		_swap(l,j,es,stype);
		
	for(i = l + es;i <= r;i += es)
		for(j = i;cmp(j,j-es) < 0;j -= es){
			_swap(j,j-es,es,stype);	
		}
}


void quicksort(void *a, size_t n, size_t es, cmp_function cmp){
	
	if(a == NULL || n <= 1)
		return;
	borders stack[STACKSIZE];
	int top = 0;
	push(a,(char*)a+(n-1)*es);
	char *l,*r,*i,*j,*m;
	int stype = SWAPTYPE(es);
	int isval = INSERTSORT * es;
	while(!empty()){
		pop();
		do{
			if((r-l) <= isval){
				insertionsort(l,r,es,stype,cmp);
				break;
			}
			m = l + (r-l)/es/2*es;
			if(cmp(m,l) < 0)
				_swap(m,l,es,stype);
			if(cmp(m,r) > 0){
				_swap(r,m,es,stype);
				if(cmp(m,l) < 0)
					_swap(m,l,es,stype);
			}
			i = l + es;j = r - es;
			for(;;){
				while(cmp(i,m) < 0) i += es;
				while(cmp(j,m) > 0) j -= es;
				if(i > j)
					break;
				_swap(i,j,es,stype);
				m = (i==m)?j:(j==m)?i:m;
				i += es;
				j -= es;				
			}


			if(r - i <= j - l){
				if(l < j){
					push(l,j);
				}
				l = i;
			}else{
				if(r > i){
					push(i,r);
				}
				r = j;
			}
		}while(l <= r);
	}
}



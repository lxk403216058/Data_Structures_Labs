#ifndef LIB_S
#define LIB_S

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


#define TURE  1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;
typedef char SElemType;

typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
} SqStack;

Status InitStack(SqStack *);
Status DestroyStack(SqStack *);
Status StackEmpty(SqStack );
Status GetTop(SqStack ,SElemType *);
Status Push(SqStack *,SElemType ) ;
Status Pop(SqStack *,SElemType *);;

Status InitStack(SqStack *S){
	S -> base = (SElemType *)malloc(sizeof(SElemType)*STACK_INIT_SIZE);
	if (S -> base== NULL)
	exit(OVERFLOW);
	S -> top = S -> base;
	S-> stacksize =  STACK_INIT_SIZE;
	
	return OK;

}

Status DestroyStack(SqStack *S){
	if (S -> base)
	   free(S ->base);
	S-> top = S->base = NULL;
	S->stacksize = 0;
	
	return OK;
}

Status Push(SqStack *S,SElemType e){
	if (S->top - S->base >= S->stacksize){
		S->base = (SElemType *)realloc(S->base,sizeof(SElemType)*(S->stacksize + STACKINCREMENT));
		if (!S->base)
	    exit(OVERFLOW);
	    S->top = S->base + S->stacksize;
	    S->stacksize += STACKINCREMENT; 
	}
	//printf("1");
	*(S->top) = e;
    (S->top)++;
	
	return OK;
}

Status Pop(SqStack *S,SElemType *e){
	if (S->top == S->base)
	     return ERROR;
	--(S->top);
    *e = *(S->top);
    
	return OK;
}

Status GetTop(SqStack S,SElemType *e){
	if (S.top > S.base) {
          *e = *(S.top -1);
		return OK;
    }
    else 
	    return ERROR;

}

Status StackEmpty(SqStack S){
	if (S.top == S.base)
	     return TURE;
	
	return FALSE;
}

#endif

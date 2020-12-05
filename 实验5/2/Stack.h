
#ifndef LIB_H
#define LIB_H

#include<stdio.h>
#include<stdlib.h>

#define TURE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10


typedef int Status;
typedef char TElemType;

typedef BiTree SElemType;
typedef struct{
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack; 

Status InitStack(SqStack *);//对栈的初始化 
Status Push(SqStack *,SElemType );//将元素压入栈顶 
Status Pop(SqStack *,SElemType *);//将栈顶元素弹出栈 
void PrintStack(SqStack *);//输出栈 
Status StackEmpty(SqStack *);//判断栈是否为空 
Status GetTop(SqStack *S,SElemType *e);//若栈不为空,则用e返回S的栈顶元素,并返回OK,否则返回ERROR 

Status StackEmpty(SqStack *S){
	//判断栈是否为空，若为空，则输出1，反之输出0; 
	if(S->top==S->base)
	return TURE;
	else
	return FALSE;
}

Status InitStack(SqStack *S){
	S->base=(SElemType *)malloc(STACK_INIT_SIZE *sizeof(SElemType));
	if(!S->base)
	exit(OVERFLOW);
	S->top=S->base;
	S->stacksize=STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack *S,SElemType e){
   //插入元素e为新的栈顶元素
   if(S->top-S->base>=S->stacksize){//栈满,追加存储空间 
   	S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
   	if(!S->base)
   	exit(OVERFLOW);//存储分配失败 
   	S->top=S->base+S->stacksize;
   	S->stacksize+=STACKINCREMENT;
   }
   *S->top++=e;
   return OK; 
}

Status Pop(SqStack *S,SElemType *e){
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK,否则返回ERROR
	if(S->top==S->base)
	return ERROR;
	*e=*--S->top;
	return OK; 
}

Status GetTop(SqStack *S,SElemType *e){
	//若栈不空,则用e返回S的栈顶元素,并返回OK,否则返回ERROR 
	 if(S->top==S->base)
	 return ERROR;
	 *e=*(S->top-1);
	 return OK;
}
#endif 

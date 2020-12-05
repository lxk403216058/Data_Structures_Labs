
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

Status InitStack(SqStack *);//��ջ�ĳ�ʼ�� 
Status Push(SqStack *,SElemType );//��Ԫ��ѹ��ջ�� 
Status Pop(SqStack *,SElemType *);//��ջ��Ԫ�ص���ջ 
void PrintStack(SqStack *);//���ջ 
Status StackEmpty(SqStack *);//�ж�ջ�Ƿ�Ϊ�� 
Status GetTop(SqStack *S,SElemType *e);//��ջ��Ϊ��,����e����S��ջ��Ԫ��,������OK,���򷵻�ERROR 

Status StackEmpty(SqStack *S){
	//�ж�ջ�Ƿ�Ϊ�գ���Ϊ�գ������1����֮���0; 
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
   //����Ԫ��eΪ�µ�ջ��Ԫ��
   if(S->top-S->base>=S->stacksize){//ջ��,׷�Ӵ洢�ռ� 
   	S->base=(SElemType *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
   	if(!S->base)
   	exit(OVERFLOW);//�洢����ʧ�� 
   	S->top=S->base+S->stacksize;
   	S->stacksize+=STACKINCREMENT;
   }
   *S->top++=e;
   return OK; 
}

Status Pop(SqStack *S,SElemType *e){
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK,���򷵻�ERROR
	if(S->top==S->base)
	return ERROR;
	*e=*--S->top;
	return OK; 
}

Status GetTop(SqStack *S,SElemType *e){
	//��ջ����,����e����S��ջ��Ԫ��,������OK,���򷵻�ERROR 
	 if(S->top==S->base)
	 return ERROR;
	 *e=*(S->top-1);
	 return OK;
}
#endif 

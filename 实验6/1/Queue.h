#ifndef _MQUEUE_H_ 
#define _MQUEUE_H_
#include<malloc.h>
#include<stdlib.h>
#define ERROR 0  // �������״̬��
#define OK 1
#define OVERFLOW -1
#define true 1
#define false 0
#define STACK_INIT_SIZE 500

typedef int Status;  // ��������ֵ����
typedef struct QUeue1{
QElemType base[STACK_INIT_SIZE];
	int front; // ��ͷ
	int rear; // ��β
}QNode;

Status InitQueue(QNode *Q){ // ��ʼ������
	Q->front=0; 
	Q->rear=0;
	if(!Q->base)
		return OVERFLOW;
	return OK;
}
	
Status QueueEmpty(QNode *Q){ // �ж϶����Ƿ�Ϊ��
	if(Q->front==Q->rear)
		return true;
	else
		return false;
}
	
Status EnQueue(QNode *Q,QElemType data){ // �����
	if(Q->rear==STACK_INIT_SIZE-1)
		return OVERFLOW;
	else{
		Q->base[(Q->rear)]=data;
		Q->rear++;//ָ����һ��Ԫ��
	}
	return OK;
}
	
Status DeQueue(QNode *Q,QElemType *data){ // ������,���в�Ϊ��,������ֵ
	if(Q->front==Q->rear)
		return OVERFLOW;
	else
	{	
			*data=Q->base[Q->front];
			Q->front++; 
	} 
	return OK;
}	
#endif


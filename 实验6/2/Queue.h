#ifndef _MQUEUE_H_ 
#define _MQUEUE_H_
#include<malloc.h>
#include<stdlib.h>
#define ERROR 0  // 函数结果状态码
#define OK 1
#define OVERFLOW -1
#define true 1
#define false 0
#define STACK_INIT_SIZE 500

typedef int Status;  // 函数返回值类型
typedef struct QUeue1{
QElemType base[STACK_INIT_SIZE];
	int front; // 队头
	int rear; // 队尾
}QNode;

Status InitQueue(QNode *Q){ // 初始化队列
	Q->front=0; 
	Q->rear=0;
	if(!Q->base)
		return OVERFLOW;
	return OK;
}
	
Status QueueEmpty(QNode *Q){ // 判断队列是否为空
	if(Q->front==Q->rear)
		return true;
	else
		return false;
}
	
Status EnQueue(QNode *Q,QElemType data){ // 入队列
	if(Q->rear==STACK_INIT_SIZE-1)
		return OVERFLOW;
	else{
		Q->base[(Q->rear)]=data;
		Q->rear++;//指向下一个元素
	}
	return OK;
}
	
Status DeQueue(QNode *Q,QElemType *data){ // 出队列,队列不为空,返回其值
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


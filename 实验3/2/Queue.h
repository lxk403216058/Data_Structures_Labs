#ifndef LIB_Q
#define LIB_Q

#include "MazeType.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define TURE  1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define INFEASIBLE -2
#define QUEUE_INIT_SIZE 100
#define QUEUEINCREMENT 10

typedef int Status;

typedef struct Queue{
	QElemType *front;
	QElemType *rear;
	int queuesize;
} SqQueue;

Status InitQueue(SqQueue *);
Status DestoryQueue(SqQueue *);
Status QueueEmpty(SqQueue );
Status GetHead(SqQueue ,QElemType *);
Status EnQueue(SqQueue *,QElemType );
Status DeQueue(SqQueue *,QElemType *);

Status InitQueue(SqQueue *Q){//初始化队列 
	Q -> front = (QElemType *)malloc(sizeof(QElemType)*QUEUE_INIT_SIZE);
	if (Q -> rear== NULL)
	exit(OVERFLOW);
	Q -> rear = Q -> front;
	Q-> queuesize =  QUEUE_INIT_SIZE;
	
	return OK;

}

Status DestoryQueue(SqQueue *Q){//销毁队列 
	if (Q -> front)
	   free(Q ->front);
	Q-> front = Q->rear = NULL;
	Q->queuesize = 0;
	
	return OK;
}

Status EnQueue(SqQueue *Q,QElemType e){//入队 
	if (Q->rear - Q->front >= Q->queuesize){
		Q->rear = (QElemType *)realloc(Q->rear,sizeof(QElemType)*(Q->queuesize + QUEUEINCREMENT));
		if (!Q->rear)
	    exit(OVERFLOW);
	    Q->front = Q->rear + Q->queuesize;
	    Q->queuesize += QUEUEINCREMENT; 
	}
	*(Q->rear) = e;
    (Q->rear)++;
	
	return OK;
}

Status DeQueue(SqQueue *Q,QElemType *e){//出队 
	if (Q->front == Q->rear)
	     return ERROR;
    *e = *(Q->front);
    ++(Q->front);
    
	return OK;
}

Status QueueEmpty(SqQueue Q){//判断队列是否为空 
	if (Q.rear == Q.front)
	     return TURE;
	
	return FALSE;
}

Status GetHead(SqQueue Q,QElemType *e){//获取队头 
	if (Q.front > Q.rear) {
          *e = *(Q.front);
		return OK;
    }
    else 
	    return ERROR;
}

#endif

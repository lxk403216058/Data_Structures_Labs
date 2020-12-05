#ifndef _QUEUE_H_ 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define STACK_MAX_SIZE 30
#define QUEUE_MAX_SIZE 30
typedef struct BitNode{
   char data;
   struct BitNode *lchild;
   struct BitNode *rchild;
}BiTNode, *BiTree;
typedef struct node
{
   BiTNode *data;
}node,*queue;
typedef struct Queue{ 
  node *base;
  int front;
  int rear;
}Queue;
void InitQueue(Queue *Q)
{ 
   Q->base=(queue)malloc(QUEUE_MAX_SIZE*sizeof(node));
   Q->front=Q->rear=0;
}
int EmptyQueue(Queue *Q){
  if(Q->front==Q->rear)
     return 1;
  else
    return 0;
}

void EnQueue(Queue *Q,BiTNode *e){ 
   Q->base[Q->rear].data=e;
   Q->rear++;
}

BiTree DeQueue(Queue *Q){	
   int m;
   m=Q->front;
   Q->front++;
   return (Q->base[m].data);
}
#endif

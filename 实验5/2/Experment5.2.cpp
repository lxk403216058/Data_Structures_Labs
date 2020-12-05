#include<stdio.h>
#include<malloc.h>

#define TRUE            1
#define FALSE           0         
#define OK              1
#define ERROR           0
#define INFEASIBLE      -1
#define OVERFLOW        -2
#define EQUAL           1 
typedef int Status;


#include "Stack.h"

Status preOrder(BiTree );
Status Create_Tree(BiTree *);
int Count_Nodes(BiTree);



int main() {
	BiTree T; 
	Create_Tree(&T);
	preOrder(T);
	Count_Nodes(T);
	printf("\n%d", Count_Nodes(T));
	
}

Status Create_Tree(BiTree *T) {
	
	SqStack S;
	InitStack(&S);
	*T = NULL;
	char ch ;	int flag = 0;
	BiTree BT1, BT2,e;
	BT1 = BT2 = NULL;
	scanf("%c", &ch);
	while(ch != '#') {
		switch(ch) {
			case '(':	Push(&S, BT1);	flag = 1;
						break;
			case ',':	flag = 0;
						break;
			case ')':	Pop(&S,&BT2);
						break;
			default :	BT1 = (BiTree)malloc(sizeof(BiTNode));
						BT1->lchild = BT1->rchild = NULL;
						BT1->data = ch;
						if(!(*T))
							(*T) = BT1;
						else{
					        GetTop(&S,&e);
							if(flag)	e->lchild = BT1;
							else	e->rchild = BT1;
						}
												
		}
		scanf("%c", &ch);
	}
	
}
Status preOrder(BiTree T) {//先序遍历 
	if(T){
		printf("%c", T->data);
		preOrder(T->lchild);
		preOrder(T->rchild);
		return OK;
	} 
	
}
int Count_Nodes(BiTree T) {//节点总数 
	if(!T)	return 0;
	else
		return Count_Nodes(T->lchild) + Count_Nodes(T->rchild) + 1;
}

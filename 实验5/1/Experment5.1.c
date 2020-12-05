#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define TRUE 1 //函数结果状态代码
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define Max_Tree_SIZE 20
#include "Queue.h"
#include "Stack.h"
//比如你要创建两层的二叉树：
// s
//a d
//那输入的应该是sa##d##

//ABC##DE#G##F###

typedef int Status;
typedef char TElemType;
Status Equal(BiTree BT1, BiTree BT2);
Status InitBiTree(BiTree *); //构造空二叉树
Status CreateBiTree(BiTree *); //先序递归建立二叉树
Status InOrderCreateBiTree(BiTree *); //中序递归建立二叉树
Status PreOrder(BiTree); //先序递归遍历
Status InOrder(BiTree); //中序递归遍历
Status LevelOrder(BiTree T);
Status PostOrder(BiTree); //后序递归遍历
Status NRPreOrder(BiTree BT);
int TreeDepth(BiTree); //求高度
int LeafNumber(BiTree); //求叶结点数

int main()
{
	BiTree  T;
	BiTree T1;
	TElemType ch;

	int flag = 1, select;

	printf("输入先序序列建立第一颗二叉树，以#结束:\n");//输入二叉树的先序序列

	InitBiTree(&T);
	InOrderCreateBiTree(&T);
	fflush(stdin);
	printf("输入先序序列建立第二颗二叉树，以#结束::\n");//输入二叉树的先序序列
    InitBiTree(&T1);
	InOrderCreateBiTree(&T1);//ABC##DE#G##F###
	while (flag)
	{
		printf("请选择:\n");
		printf("1.先序递归遍历二叉树 \n");
		printf("2.中序递归遍历二叉树 \n");
		printf("3.后序递归遍历二叉树 \n");
		printf("4.按层次非递归遍历二叉树 \n");
		printf("5.先序非递归遍历二叉树 \n");
		printf("6.二叉树的高度 \n");
		printf("7.叶结点数 \n");
		printf("8.比较两棵树\n");
		printf("0.退出\n");
		scanf("%d", &select);
		system("cls");
		switch (select)
		{
			case 1:
				printf("\n先序递归遍历二叉树：");
				PreOrder(T);
				printf("\n");
				break;
			case 2:
				printf("\n中序递归遍历二叉树：");
				InOrder(T);
				printf("\n");
				break;
			case 3:
				printf("\n后序递归遍历二叉树：");
				PostOrder(T);
				printf("\n");
				break;
			case 4:
				printf("\n按层次非递归遍历二叉树：");
				LevelOrder(T);
				printf("\n");
				break;
            case 5:
				printf("\n先序非递归遍历二叉树：");
				NRPreOrder(T);
				printf("\n");
				break;
			case 6:
				printf("\n二叉树的高度：%d\n",TreeDepth(T));
				break;
			case 7:printf("\n叶节点数：%d\n",LeafNumber(T));
				  break;
			case 8:
				if(Equal(T,T1)){
                    printf("\n两棵树相等\n");
				}
				else{
                    printf("\n两棵树不相等\n");
				}

				break;

			default:
				flag = 0;
				printf("任意键退出\n");
				getch();
		}
		printf("\n");
	}
}

Status InitBiTree(BiTree *T)
{
	*T = NULL;
	return 0;
}

Status CreateBiTree(BiTree *T)
{
	char ch;
	ch = getchar();
	if (ch != '#'){
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->data = ch; (*T)->lchild = (*T)->rchild = NULL;
		CreateBiTree(&((*T)->lchild));
		CreateBiTree(&((*T)->rchild));
	}
	else
		return 0;
}

Status InOrderCreateBiTree(BiTree *T)
{
	char ch;
	ch = getchar();
	if (ch != '#'){
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->lchild = (*T)->rchild = NULL;
		InOrderCreateBiTree(&((*T)->lchild));
		(*T)->data = ch;
		InOrderCreateBiTree(&((*T)->rchild));
	}
	else
		return 0;
}



Status PreOrder(BiTree T)
{
	//先序遍历树
	if (T)
	{
		if (!T->data)
			return 0;
		printf("%c ", T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
		return OK;
	}
}

Status InOrder(BiTree T)
{
	//中序遍历树
	if (T){
		if (!T->data)
			return 0;
		InOrder(T->lchild);
		printf("%c ", T->data);
		InOrder(T->rchild);
		return OK;
	}

}

Status PostOrder(BiTree T)
{
	//后序遍历树
	if (T){
		if (!T->data)
			return 0;
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%c ", T->data);
		return OK;
	}

}

Status LevelOrder(BiTree T)
{
    Queue l;
    Queue *Q=&l;
    BiTree p;
    InitQueue(Q);
    if(T)
    {
	   EnQueue(Q,T);
       while(!EmptyQueue(Q))
       {
	       p=DeQueue(Q);
           printf("%c",p->data);
           if(p->lchild)
               EnQueue(Q,p->lchild);
           if(p->rchild)
               EnQueue(Q,p->rchild);
        }
    }
    return OK;
}

Status NRPreOrder(BiTree BT)
{
     SqStack S;
    InitStack(&S);///初始化创建栈
    BiTree p=BT;///p为工作指针
    while(p||!StackEmpty(&S))
    {
	   while(p)///到最左下的孩子
	   {
	      printf(" %c ",p->data);///先序先遍历结点
	      Push(&S,p);///入栈
	      p=p->lchild;
	   }
	   if(!StackEmpty(&S))///在栈不为空的情况下，左孩子为空，弹出该结点，遍历右孩子
	   {
	      Pop(&S,&p);
	       p=p->rchild;
	   }
    }
    return OK;
}

int TreeDepth(BiTree T)
{
	//求高度
	int ldepth, rdepth;
	if (!T)
		return 0;
	else{
		ldepth = TreeDepth(T->lchild);
		rdepth = TreeDepth(T->rchild);
		return ldepth > rdepth ? ldepth + 1 : rdepth + 1;
	}
}

Status Equal(BiTree BT1, BiTree BT2) {
	if((!BT1) && (!BT2))	//都为空，返回true
		return OK;
	//值相同且左子树和右子树相等，返回true
	if(BT1->data == BT2->data)
		if(Equal(BT1->lchild, BT2->lchild) && (Equal(BT1->rchild, BT2->rchild)))
			return OK;
	return ERROR;
}

int LeafNumber(BiTree T)
{
	//求叶节点个数
	if (!T)
 		return 0;
	else if ((!T->lchild) && (!T->rchild))
		return 1;
	else
		return LeafNumber(T->lchild) + LeafNumber(T->rchild);
}

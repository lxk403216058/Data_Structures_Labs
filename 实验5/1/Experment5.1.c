#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define TRUE 1 //�������״̬����
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define Max_Tree_SIZE 20
#include "Queue.h"
#include "Stack.h"
//������Ҫ��������Ķ�������
// s
//a d
//�������Ӧ����sa##d##

//ABC##DE#G##F###

typedef int Status;
typedef char TElemType;
Status Equal(BiTree BT1, BiTree BT2);
Status InitBiTree(BiTree *); //����ն�����
Status CreateBiTree(BiTree *); //����ݹ齨��������
Status InOrderCreateBiTree(BiTree *); //����ݹ齨��������
Status PreOrder(BiTree); //����ݹ����
Status InOrder(BiTree); //����ݹ����
Status LevelOrder(BiTree T);
Status PostOrder(BiTree); //����ݹ����
Status NRPreOrder(BiTree BT);
int TreeDepth(BiTree); //��߶�
int LeafNumber(BiTree); //��Ҷ�����

int main()
{
	BiTree  T;
	BiTree T1;
	TElemType ch;

	int flag = 1, select;

	printf("�����������н�����һ�Ŷ���������#����:\n");//�������������������

	InitBiTree(&T);
	InOrderCreateBiTree(&T);
	fflush(stdin);
	printf("�����������н����ڶ��Ŷ���������#����::\n");//�������������������
    InitBiTree(&T1);
	InOrderCreateBiTree(&T1);//ABC##DE#G##F###
	while (flag)
	{
		printf("��ѡ��:\n");
		printf("1.����ݹ���������� \n");
		printf("2.����ݹ���������� \n");
		printf("3.����ݹ���������� \n");
		printf("4.����ηǵݹ���������� \n");
		printf("5.����ǵݹ���������� \n");
		printf("6.�������ĸ߶� \n");
		printf("7.Ҷ����� \n");
		printf("8.�Ƚ�������\n");
		printf("0.�˳�\n");
		scanf("%d", &select);
		system("cls");
		switch (select)
		{
			case 1:
				printf("\n����ݹ������������");
				PreOrder(T);
				printf("\n");
				break;
			case 2:
				printf("\n����ݹ������������");
				InOrder(T);
				printf("\n");
				break;
			case 3:
				printf("\n����ݹ������������");
				PostOrder(T);
				printf("\n");
				break;
			case 4:
				printf("\n����ηǵݹ������������");
				LevelOrder(T);
				printf("\n");
				break;
            case 5:
				printf("\n����ǵݹ������������");
				NRPreOrder(T);
				printf("\n");
				break;
			case 6:
				printf("\n�������ĸ߶ȣ�%d\n",TreeDepth(T));
				break;
			case 7:printf("\nҶ�ڵ�����%d\n",LeafNumber(T));
				  break;
			case 8:
				if(Equal(T,T1)){
                    printf("\n���������\n");
				}
				else{
                    printf("\n�����������\n");
				}

				break;

			default:
				flag = 0;
				printf("������˳�\n");
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
	//���������
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
	//���������
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
	//���������
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
    InitStack(&S);///��ʼ������ջ
    BiTree p=BT;///pΪ����ָ��
    while(p||!StackEmpty(&S))
    {
	   while(p)///�������µĺ���
	   {
	      printf(" %c ",p->data);///�����ȱ������
	      Push(&S,p);///��ջ
	      p=p->lchild;
	   }
	   if(!StackEmpty(&S))///��ջ��Ϊ�յ�����£�����Ϊ�գ������ý�㣬�����Һ���
	   {
	      Pop(&S,&p);
	       p=p->rchild;
	   }
    }
    return OK;
}

int TreeDepth(BiTree T)
{
	//��߶�
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
	if((!BT1) && (!BT2))	//��Ϊ�գ�����true
		return OK;
	//ֵ��ͬ������������������ȣ�����true
	if(BT1->data == BT2->data)
		if(Equal(BT1->lchild, BT2->lchild) && (Equal(BT1->rchild, BT2->rchild)))
			return OK;
	return ERROR;
}

int LeafNumber(BiTree T)
{
	//��Ҷ�ڵ����
	if (!T)
 		return 0;
	else if ((!T->lchild) && (!T->rchild))
		return 1;
	else
		return LeafNumber(T->lchild) + LeafNumber(T->rchild);
}

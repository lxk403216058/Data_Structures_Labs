# include<stdio.h>
# include<stdlib.h>

#define OK 1
#define ERROR 0
#define TURE 1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef struct  LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

Status Create_LinkList(LinkList );
Status Judge_LinkList(LinkList );
Status Printf_LinkList(LinkList );
void Destroy_LinkList(LinkList* );
Status Delete_Same_LinkList(LinkList );
Status Reverse_LinkList(LinkList );
Status InitList_LinkList(LinkList* );

int main(){
	LinkList head;
	Status flag;
	
	InitList_LinkList(&head);
	Create_LinkList(head);
	printf("单向链表：");
	Printf_LinkList(head);
	flag = Judge_LinkList(head);
	if(Judge_LinkList(head) == 0){
		Delete_Same_LinkList(head);
		printf("删除相同后的单向链表：");
		Printf_LinkList(head);
	    Reverse_LinkList(head);
	    printf("逆置删除相同后的单向链表：");
	    Printf_LinkList(head);
	} else{
		printf("该链表不是非递增有序链表");
	}
	
	Destroy_LinkList(&head);
	
	return OK;
}

Status InitList_LinkList(LinkList *head){
	*head = (LinkList )malloc(sizeof(LNode));
	if (!head)
	exit(ERROR);
	(*head) -> next = NULL;
	
	return OK;
}

Status Create_LinkList(LinkList head){//用尾插法构造一个单链表
	int n, i, m;
	LinkList p,q;
	//head = (LinkList )malloc(sizeof(LNode));
	
	printf("请输入你要输入数据元素的个数：");
	scanf("%d",&n);
	
	p = head;
	for (i = 0;i < n; i ++){
		q = (LNode* )malloc(sizeof(LNode));
		printf("请输入一个数据元素：");
		scanf("%d",&m);
		q -> data = m;
		p -> next = q;
		p = q;
	}
	
	q -> next = NULL;
	
	return OK;
}

Status Judge_LinkList(LinkList head){//判断单向链表是否为非单向递增 
	LinkList p,q;
	int i = 0;
	p = head -> next;
	q = p -> next;
	
	while (q){
		if (p -> data < q -> data){
			i = 1;
		}
		p = q;
		q = q -> next;
	}
	
	return i;
}

Status Printf_LinkList(LinkList head){//打印单向链表 
	LinkList p;
	p = head -> next ;

	while (p){
		printf("%d ",p -> data);
		p = p -> next;
	}
	printf("\n");
	
	return OK;
}

void Destroy_LinkList(LinkList *head){//回收链表存储空间 
	LinkList p,q;
	p = *head;
	q= p -> next;
	while (p){
		free(p);
		p = q;
		q = q-> next;
		
	}
}

Status Delete_Same_LinkList(LinkList head){//删除单向链表中相同元素 
	LinkList p,q;
	p = head -> next;
	q = p -> next;
	
	if (head == NULL){
		return ERROR;
	}
	if (head -> next == NULL){
		return ERROR;
	}
	
	while (q){
		if (p -> data == q -> data){
			p -> next = q -> next;
			free(q);
			q = p;
		}
		p = q;
		q = q -> next;
	}
	
	return OK;
}

Status Reverse_LinkList(LinkList head){//逆置单向链表 
	LinkList p,q;
	p = head -> next;
	
	head -> next = NULL;
	
	while (p != NULL){
		q = p;
		p = p -> next;
		q -> next = head -> next;
		head -> next = q;
	}
	
	return OK;
}


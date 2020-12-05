# include<stdio.h>
# include<stdlib.h>

#define OK 1
#define ERROR 0
#define TURE 1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int Status;
typedef int ElemType;

typedef struct {
	ElemType *elem;
	int length;
	int listsize;
}SqList;

Status InitList_Sq(SqList *L){//构造一个空的顺序表 
	L -> elem = (ElemType* )malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if (!L -> elem)
	exit(OVERFLOW);
	L -> length = 0;
	L -> listsize = LIST_INIT_SIZE;
	
	return OK;
}

int ListLength_SqList(SqList L){//返回顺序表的长度 
	return L.length;
}

void GetElem_SqList(){// 
	
}

void Generate_Sq(SqList *L){//建立一个顺序表，表中含有n个元素 
	int i,n;
	
	printf("请输入你要输入元素的个数：");
	scanf("%d",&n); 
	
	printf("请输入递增%d个元素",n);
	for (i = 0;i < n;i ++){
		scanf("%d",&L -> elem[i]);
		L -> length++;
	}
	
}

void Output_Sq(SqList L){//输出顺序表中的元素 
	int i;
	
	printf("顺序表中的元素是：");
	for(i = 0;i < L.length;i ++){
		printf("%d ",L.elem[i]);
	}
	
	printf("\n");
}

void Destroy_Sq(SqList *L){//销毁一张顺序表 
	free(L);
} 

void MergeList_Sq(SqList *la,SqList *lb,SqList *lc){//合并两张顺序表 
	ElemType *pa,*pb,*pc,*pa_last,*pb_last;
	
	pa = la -> elem;
	pb = lb -> elem;
	
	lc -> listsize = lc -> length = la -> length + lb -> length;
	pc = lc -> elem = (ElemType *)malloc(lc -> listsize*sizeof(ElemType));
	if (!lc -> elem)
	   exit(OVERFLOW);
	   
	pa_last = la -> elem + la -> length - 1;
	pb_last = lb -> elem + lb -> length - 1;
	
	while (pa <= pa_last && pb <= pb_last){
		if (*pa <= *pb){
			*pc++ = *pa++;
		}else //if(*pa > *pb)
		{
			*pc++ = *pb++;
		}
	}
	
	while (pa <= pa_last){
		*pc++ = *pa++ ;
	}
	
	while (pb <= pb_last){
		*pc++ = *pb++;
	}
	
}

void ReverseList_Sq(SqList *la,SqList *lb){//将顺序表逆置，结果存入另一张顺序表 
	int i,j;
	
	InitList_Sq(lb);
	j = la -> length - 1;
	
	for (i = 0;i <= j;i ++){
		lb -> elem[i] = la -> elem[j - i];
		lb -> length ++;
	}
}

void Delete_Same_Sq(SqList *L){
	int *p,*q,*r = L ->length + L -> elem;
	
	for (p = L -> elem,q = p + 1;q < r;q ++){
		if (*p != *q){
			*(p + 1) = *q;
			p ++;
		}else{
			L -> length --;
		}
	}
}

int main(){
	SqList la,lb,lc,ld;
	InitList_Sq(&la);
	Generate_Sq(&la);
	InitList_Sq(&lb);
	Generate_Sq(&lb);
	InitList_Sq(&lc);
	InitList_Sq(&ld);
	
	Output_Sq(la);
	Output_Sq(lb);
	
	MergeList_Sq(&la,&lb,&lc);
	Output_Sq(lc);
	
	Delete_Same_Sq(&lc);
	Output_Sq(lc);
	
	ReverseList_Sq(&lc,&ld);
	Output_Sq(ld);
	
	Destroy_Sq(&la);
	Destroy_Sq(&lb);
	Destroy_Sq(&lc);
	Destroy_Sq(&ld);
	
	return OK;
}

#include<stdio.h>
#include<stdlib.h>
#include"conio.h"
#include"time.h"

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXSIZE 50000 /*设待排序记录数不超过5000个*/

	int  compare[8]={0};  //比较次数
	int  move[8]={0};  //移动次数
	double duration[8]={0};//比较时间 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef int Status;  /*Status为函数返回值类型，其值为的数结果状态代码*/
typedef int KeyType;  /*定义关键字类型为整型*/
typedef int InfoType;  /*定义其他数据项类型为整型*/
typedef struct{
  KeyType key;  /*关键字项*/
  InfoType otherinfo;  /*其它数据项*/
} RedType;
typedef struct{  /*定义顺序表的结构*/
  RedType *r;  /*存储空间基址，r[0]闲置或用作哨兵或用作缓冲区*/
  int length;  /*顺序表的长度*/
}SqList;

Status InitSqList(SqList *);  /*构造一个空顺序表 L*/
Status CreatSqList(SqList *) ;/*输入数据元素个数，随机产生整数样本*/
Status CopySqList(SqList,SqList *);
Status OutputSqList(SqList);  /*输出排序之后的数据*/
int LT(KeyType ,KeyType);  /*判断数据元素e1是否小于e2*/
void Swap(RedType *,RedType *);/*数据元素el和e2互换*/
Status InsertSort (SqList *);  /*直接插入排序*/
void BInsertSort(SqList *);  /*折半插入排序*/
void ShellInsert(SqList *, int);/*一趟希尔插入排序*/
void ShellSort(SqList *, int [], int);/*希尔排序*/
Status BubbleSort(SqList *);  /*冒泡排序*/
int Partition( SqList *, int ,int); /*一趟快速排序*/
void QSort(SqList *,int ,int);/*对 L中的子序列L r[low. . high]进行快速排序*/
void QuickSort (SqList *);  /*对L进行快速排序*/
Status SelectSort (SqList *);  /*直接选择排序*/
void HeapAdjust(SqList *,int , int);/*调整L.r[s]的关键字，使L. r[s..m]成大顶堆*/
void HeapSort(SqList *);  /*堆排序*/
Status Merge(SqList *,int ,int ,int);/*将 两个有序的子序列L. r[1ow. . mid]和L r[mid+1.. high]归并成有序的序列L r[low. high]*/
void MSort(SqList *, int);  /*对L.rL..n)做 趟归井排序*/
Status MergeSort(SqList *); /*对L.r[1.. n)自底向上二路归井排序*/

/********************* main ***************/
void main() {  /*典型内部排序的比较*/
	SqList L[8],L_BAK; 
	int t;
	int dlta[MAXSIZE];
//	double duration;
	clock_t start, finish;

/*clock t用于计时*/
	InitSqList(&L[0]);
	InitSqList(&L[1]);
	InitSqList(&L[2]);
	InitSqList(&L[3]);
	InitSqList(&L[4]);
	InitSqList(&L[5]);
	InitSqList(&L[6]);
	InitSqList(&L[7]);
	InitSqList(&L_BAK); 
	CreatSqList(&L_BAK);
	t=0;
	dlta[0] = L_BAK.length/2;
	while (dlta[t]>1) 
	{
		dlta[t+1]= dlta[t]/2;
		t++;
//产生希尔排序的增量序列da10.0.
	}
    	 		printf("\n Now is in InsertSort ......" );
    			CopySqList(L_BAK,&L[0]);
    			start = clock();
				InsertSort(&L[0]);
				finish = clock();
				duration[0] = (double) (finish - start) / CLK_TCK; /*輸出算木吋*/
    	 		printf("\n Now is in BInsertSort ...... ");
				CopySqList(L_BAK,&L[1]);
      			start = clock();
	  			BInsertSort(&L[1]);
	  			finish = clock();
	  			duration[1] = (double) (finish - start) / CLK_TCK;
    	  		printf("\n Now is in ShellSort ...... ");
    			CopySqList(L_BAK,&L[2]);
      			start=clock();
      			ShellSort(&L[2],dlta,t+1);
      			finish = clock();
      			duration[2] = (double) (finish - start)/ CLK_TCK;
    	 		printf("\n Now is in BubbleSort ...... ");
    			CopySqList(L_BAK,&L[3]);
      			start = clock();
	  			BubbleSort(&L[3]);
	  			finish = clock();
	  			duration[3] = (double) (finish - start) / CLK_TCK;
     			printf("\n Now is in QuickSort ...... ");
    			CopySqList(L_BAK,&L[4]);    	
    			start = clock();
	  			QuickSort(&L[4]);
	  			finish = clock();
	  			duration[4] = (double) (finish - start) / CLK_TCK;
      	 		printf("\n Now is in SelectSort ...... ");
    			CopySqList(L_BAK,&L[5]);      	
      			start = clock();
	  			SelectSort(&L[5]);
	  			finish = clock();
	  			duration[5] = (double) (finish - start) / CLK_TCK;
      			printf("\n Now is in HeapSort ..... ");
    			CopySqList(L_BAK,&L[6]);      	
      			start = clock();
	  			HeapSort(&L[6]);
      			finish = clock();
      			duration[6] = (double) (finish - start) / CLK_TCK;
 	  			printf("\n Now is in MergeSort......");
 	  	    	CopySqList(L_BAK,&L[7]);
	  			start = clock();
	  			MergeSort(&L[7]);
	   			finish = clock();
	   			duration[7] = (double) (finish - start) / CLK_TCK;
	   		
		OutputSqList(L[0]);
		printf("\n ");
		printf("                      比  较  结  果                  \n");
		printf(" \n");
		printf("		比较次数        移动次数        运行时间      \n");
		printf("1. InsertSort	%d	%d	%lf\n",compare[0],move[0],duration[0]);
		printf("2. BinsertSort	%d	        %d	%lf\n",compare[1],move[1],duration[1]);
		printf("3. ShellSort	%d		%d		%lf\n",compare[2],move[2],duration[2]);
		printf("4. BubbleSott	%d	%d	%lf\n",compare[3],move[3],duration[3]);
		printf("5. QuicSort	%d		%d		%lf\n",compare[4],move[4],duration[4]);
		printf("6. SelectSort	%d		%d		%lf\n",compare[5],move[5],duration[5]);
		printf("7. HeapSort	%d		%d		%lf\n",compare[6],move[6],duration[6]);
		printf("8. MergeSort	%d		%d		%lf\n",compare[7],move[7],duration[7]);
	
}/*main*/


Status InitSqList(SqList *L){  /*构造一个空顺序表L*/
	L->r= (RedType *)malloc((MAXSIZE+1)*sizeof(RedType));
/*分配内存*/
	if (!L->r)
 		exit(OVERFLOW);
	L->length=0;
	return OK;
}/*InitSqList*/
Status CreatSqList(SqList *L){ /*输入数据元素个数。随机产生整数样本*/
	int i;

/*存储分配失败，退出*//*空表长度为0*/
	srand(time (NULL));
	printf("\nPlease Input the Number of Unsorted Data:" );
	scanf("%d", &L->length) ;

	for ( i=1; i<= L->length; i++ )
		L->r[i].key=rand();

/*随机产生整数样本*/
	printf("\n\nThe UnSorted data is:\n");
	for ( i=1;i<=L->length; i++)
		printf("%8d",L->r[i].key);
	return OK;
}/*CreatSqList*/

Status CopySqList(SqList L_BAK,SqList *L){

	int i;
	if ( !L_BAK. length){
		printf("The Salist is Empty!" );
		return ERROR;
	}

	for ( i=1; i<=L_BAK.length;i++)
		L->r[i].key=L_BAK.r[i].key;
	L->length=L_BAK.length;

	return OK;
}/*CopySqList*/

Status OutputSqList(SqList L){
	int i;

/*输出排序之后的数据*/
	printf("\nThe Length of SqList is:%d\n", L.length);
	printf(" \n\nThe Sorted Data is:\n"); 
	for ( i=1; i<= L. length; i++ )
		printf("%8d",L.r[i].key);
	printf("\n");
	return OK;
}/*0utputSqList*/

int LT(KeyType e1,KeyType e2){
	
 /*判断数据元素 ol是否小于e2*/
 	if(e1<e2)
		return 1;
	else
		return 0;
}

void Swap(RedType *e1,RedType *e2){
	RedType e;
	e = *e1;
	*e1 = *e2;
	*e2 = e;
}
   

/**************** 1. InsertSort *****************/
Status InsertSort(SqList *L){
	int i,j;
	if (!L->length){
		printf("the sqlist is empty!");
		return ERROR;
	}
	
	for(i=2;i<=L->length;i++)
		if (LT(L->r[i].key,L->r[i-1].key)){
			compare[0]++;
			L->r[0] = L->r[i];
			L->r[i] = L->r[i-1];
			move[0]+=2;
			for (j=i-2;LT(L->r[0].key,L->r[j].key);j--){
				L->r[j+1]=L->r[j];
				compare[0]++;
				move[0]++;
			}
			
			L->r[j+1]=L->r[0];
			move[0]++;
		}
		return OK;
}

/**************** 2. BInsertSort *****************/

void BInsertSort(SqList *L) {
//对顺序表工作折半插人排序。
	int i,low,high,m,j;
	
	for(i=2;i<=L->length;++i){
		L->r[0] = L->r[i];
		move[1]++;
	low = 1;  high = i- 1;
	while (low<= high) {
	m = (low+ high)/2;
	if (LT(L->r[0].key,L->r[m].key)){
		high = m-1;
		compare[1]++;
	} 
	else  low=m+1;
	}// while
	for( j=i-1; j>= high+ 1; --j ){
	L->r[j+ 1] = L->r[j];
	move[1]++;
	} 
	L->r[high+ 1]= L->r[0];
	move[1]++;
	}// for
} //BInsertSort


/**************** 3. ShellInsert *****************/

void ShellInsert(SqList *L,int dk){
//对顺序表工作一趟希尔插人排序。本算法是和一趟直接插人排序相比，
//  1.前后记录位置的增量是dk,而不是1;
//2. r[0]只是暂存单元,不是哨兵。当j<=0时，插入位置已找到.
int i,j;
for( i=dk+1; i<= L->length; ++ i )
	if (LT(L->r[i].key, L->r[i-dk].key)) 
	{
	 //需将L.r[i]插人有序增量子表 
	 	compare[2]++;
		L->r[0] = L->r[i];  //暂存在L.r[0]
		move[2]++;
		for (j=i-dk; j>0&& LT(L->r[0].key, L->r[j].key); j-=dk){
			L->r[j+dk] = L->r[j];  //记录后移，查找插人位置
			compare[2]++;
			move[2]++;
		}
		move[2]++;
		L->r[j+dk] = L->r[0];  //插人
	}
}// ShellInsert..

void ShellSort(SqList *L, int dlta[], int t) {
//按增量序列dita[0..t- 1]对顺序表L作希尔排序。
	int k;
	for (k=0;k<t;++k)
		ShellInsert(L,dlta[k]); //- 趟 增量为dlta[k]的插人排序
}// ShellSort

/**************** 4. BubbleSort *****************/
Status BubbleSort(SqList *L) { /*冒 泡排序*/
	int i,j;

    if ( !L->length ){
		printf("The SqList is Empty!");
        return ERROR;
    }
    for ( i=1; i<L->length; i++ )
    for ( j=1; j<=L->length-i; j++ )
    if ( !LT(L->r[j].key,L->r[j+1].key) ){
    	Swap(&L->r[j],&L->r[j+1]);
    	compare[3]++;
    	move[3]+=3;
    	
	}
        

    return OK;
} /*BubbleSort*/

/**************** 5. QuickSort *****************/
/*一趙快速排序*/
int Partition(SqList *L,int low,int high)
{
//分割区域函数
	L->r[0] = L->r[low];
	int pivotkey = L->r[low].key;//一般将顺序表第一个元素作为支点
	while(low < high)
	{
		
		while(low<high && L->r[high].key>=pivotkey){
			high--;
			compare[4]++;
		}
		compare[4]++;
		
		move[4]++;
		L->r[low] = L->r[high];
		while(low<high && L->r[low].key<=pivotkey){
			low++;
			compare[4]++;
		}
		compare[4]++;
			move[4]++;
		L->r[high] = L->r[low];
	}
	move[4]++;
	L->r[low] = L->r[0];//返回枢轴位置
	return low;
}

void QSort(SqList *L,int low,int high)
{
//每张子表的快速排序
	if(low<high)
	{
		int pivotloc = Partition(L,low,high);
		QSort(L,low,pivotloc-1);
		QSort(L,pivotloc+1,high);
	}
}

void QuickSort(SqList *L)
{
	QSort(L,1,L->length);
}

/**************** 6. SelectSort *****************/
Status SelectSort(SqList *L){
	int i, j, min;

	if ( !L->length ){

		printf("The SqList is Empty!" );
		return ERROR;
	}
	for ( i=1; i<L->length; i++ ){

		min=i;
		for ( j=i+1; j<=L->length; j++ )
			if ( LT(L->r[j].key, L->r[min].key) ){
					min=j;
					compare[5]++;
			}
			
			if(min!=i){
					Swap(&L->r[i], &L->r[min]); /*for*/
					move[5]+=3;
			}
			
	}
	return OK;

} /*SelectSort*/

/**************** 7. HeapSort *****************/
/*一趙快速排序*/
void HeapAdjust(SqList *H,int s,int m)
{
//堆调整，将记录调整为小顶堆
	int j;
	RedType rc = H->r[s];//暂时存储根结点
	for(j=2*s; j<=m; j*=2)
	{
//沿着结点记录较小的向下筛选	
        compare[6]++;
		if(j<m && H->r[j].key<H->r[j+1].key){
			++j;
		}
			
		if(rc.key>= H->r[j].key)
			break;
		H->r[s] = H->r[j];
		move[6]++;
			s = j;
	}
	H->r[s] = rc;
	move[6]++;
}

void HeapSort(SqList *H)
{
	int i;
	RedType temp;
	for(i = H->length; i>0; --i)
		HeapAdjust(H,i,H->length);
	for(i=H->length; i>1; --i)
	{
		Swap(&H->r[1],&H->r[i]);
		move[6]+=3;
		HeapAdjust(H,1,i-1);
	}
}


/**************** 8. MergeSort *****************/


Status Merge(SqList *L,int low,int mid,int high){/*将两个有序的子序列L.r[low.. mid]和L. r[mid+1.. high]归并成有序的序列L. r[1ow. . high]*/

	int i=low, j=mid+1, k=0;  /*赋初值*/

    SqList L1;  /*L1暂存L.r[low.mid] 和L. r[mid+1.. high]归并后的结果*/

    L1.r = (RedType *)malloc( (high-low+1)*sizeof (RedType)) ;/*分配内存*/
	if (!L1.r)
		exit(OVERFLOW) ;  /*存储分配失败，退出*/

	while ( i<=mid & j<=high )   /*两个子序列非空时，取其小者输出到L1. r[k]上*/
	{
			L1.r[k++] = LT(L->r[i]. key,L->r[j]. key)? L->r[i++]:L->r[j++];
			compare[7]++;
	}
	while ( i<=mid)  /*复制第一个子序列的剩余记录到L1*/
	{
			L1. r[k++]=L->r[i++];
			move[7]++;
		}
    while ( j<=high)/*复制第二个子序列的剩余记录到L1*/
	{	L1. r[k++]=L->r[j++];
		move[7]++;
	}
	for ( k=0, i=low; i<=high; k++,i++)
	{
		L->r[i]. key=L1. r[k]. key;
		move[7]++;
	} /*将归并结 果复制回L->r[low. . high]*/
}/*Merge*/

void MSort (SqList *L, int len) {/*对L. r[L.L. length]做趟归并排序*/
	int i;
	for ( i=1; i+2*len-1<=L->length; i=i+2*len )/*归并长度为len的两个相邻的子序列*/
		Merge(L, i, i+len-1, i+2*len-1);
	if ( i+len-1<L->length )/*仍有一个子序列，其中最后一个长度度小于lens，此时，若i<l->length且i+em-1>L->length时，则剩余一个子序列轮空，无须归并*/
		Merge(L,i, i+len- 1,L->length); /*归并最后两 个子序列*/
} /*MSort*/

Status MergeSort(SqList *L){ /*对 L r[1.. n]自底向上二路归并排序*/
	int len;
	if ( !L->length ){
		printf("The Sqlist is Empty! ");
		return ERROR;

	}
	for ( len=1; len<L->length; len*=2 ) /*有序 长度len≥n时终止*/
		MSort(L,len);
	return OK;
}










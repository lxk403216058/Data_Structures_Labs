#include<stdio.h>
#include<stdlib.h>
#include"conio.h"
#include"time.h"

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAXSIZE 50000 /*��������¼��������5000��*/

	int  compare[8]={0};  //�Ƚϴ���
	int  move[8]={0};  //�ƶ�����
	double duration[8]={0};//�Ƚ�ʱ�� 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef int Status;  /*StatusΪ��������ֵ���ͣ���ֵΪ�������״̬����*/
typedef int KeyType;  /*����ؼ�������Ϊ����*/
typedef int InfoType;  /*������������������Ϊ����*/
typedef struct{
  KeyType key;  /*�ؼ�����*/
  InfoType otherinfo;  /*����������*/
} RedType;
typedef struct{  /*����˳���Ľṹ*/
  RedType *r;  /*�洢�ռ��ַ��r[0]���û������ڱ�������������*/
  int length;  /*˳���ĳ���*/
}SqList;

Status InitSqList(SqList *);  /*����һ����˳��� L*/
Status CreatSqList(SqList *) ;/*��������Ԫ�ظ��������������������*/
Status CopySqList(SqList,SqList *);
Status OutputSqList(SqList);  /*�������֮�������*/
int LT(KeyType ,KeyType);  /*�ж�����Ԫ��e1�Ƿ�С��e2*/
void Swap(RedType *,RedType *);/*����Ԫ��el��e2����*/
Status InsertSort (SqList *);  /*ֱ�Ӳ�������*/
void BInsertSort(SqList *);  /*�۰��������*/
void ShellInsert(SqList *, int);/*һ��ϣ����������*/
void ShellSort(SqList *, int [], int);/*ϣ������*/
Status BubbleSort(SqList *);  /*ð������*/
int Partition( SqList *, int ,int); /*һ�˿�������*/
void QSort(SqList *,int ,int);/*�� L�е�������L r[low. . high]���п�������*/
void QuickSort (SqList *);  /*��L���п�������*/
Status SelectSort (SqList *);  /*ֱ��ѡ������*/
void HeapAdjust(SqList *,int , int);/*����L.r[s]�Ĺؼ��֣�ʹL. r[s..m]�ɴ󶥶�*/
void HeapSort(SqList *);  /*������*/
Status Merge(SqList *,int ,int ,int);/*�� ���������������L. r[1ow. . mid]��L r[mid+1.. high]�鲢�����������L r[low. high]*/
void MSort(SqList *, int);  /*��L.rL..n)�� �˹龮����*/
Status MergeSort(SqList *); /*��L.r[1.. n)�Ե����϶�·�龮����*/

/********************* main ***************/
void main() {  /*�����ڲ�����ıȽ�*/
	SqList L[8],L_BAK; 
	int t;
	int dlta[MAXSIZE];
//	double duration;
	clock_t start, finish;

/*clock t���ڼ�ʱ*/
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
//����ϣ���������������da10.0.
	}
    	 		printf("\n Now is in InsertSort ......" );
    			CopySqList(L_BAK,&L[0]);
    			start = clock();
				InsertSort(&L[0]);
				finish = clock();
				duration[0] = (double) (finish - start) / CLK_TCK; /*ݔ����ľ��*/
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
		printf("                      ��  ��  ��  ��                  \n");
		printf(" \n");
		printf("		�Ƚϴ���        �ƶ�����        ����ʱ��      \n");
		printf("1. InsertSort	%d	%d	%lf\n",compare[0],move[0],duration[0]);
		printf("2. BinsertSort	%d	        %d	%lf\n",compare[1],move[1],duration[1]);
		printf("3. ShellSort	%d		%d		%lf\n",compare[2],move[2],duration[2]);
		printf("4. BubbleSott	%d	%d	%lf\n",compare[3],move[3],duration[3]);
		printf("5. QuicSort	%d		%d		%lf\n",compare[4],move[4],duration[4]);
		printf("6. SelectSort	%d		%d		%lf\n",compare[5],move[5],duration[5]);
		printf("7. HeapSort	%d		%d		%lf\n",compare[6],move[6],duration[6]);
		printf("8. MergeSort	%d		%d		%lf\n",compare[7],move[7],duration[7]);
	
}/*main*/


Status InitSqList(SqList *L){  /*����һ����˳���L*/
	L->r= (RedType *)malloc((MAXSIZE+1)*sizeof(RedType));
/*�����ڴ�*/
	if (!L->r)
 		exit(OVERFLOW);
	L->length=0;
	return OK;
}/*InitSqList*/
Status CreatSqList(SqList *L){ /*��������Ԫ�ظ��������������������*/
	int i;

/*�洢����ʧ�ܣ��˳�*//*�ձ���Ϊ0*/
	srand(time (NULL));
	printf("\nPlease Input the Number of Unsorted Data:" );
	scanf("%d", &L->length) ;

	for ( i=1; i<= L->length; i++ )
		L->r[i].key=rand();

/*���������������*/
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

/*�������֮�������*/
	printf("\nThe Length of SqList is:%d\n", L.length);
	printf(" \n\nThe Sorted Data is:\n"); 
	for ( i=1; i<= L. length; i++ )
		printf("%8d",L.r[i].key);
	printf("\n");
	return OK;
}/*0utputSqList*/

int LT(KeyType e1,KeyType e2){
	
 /*�ж�����Ԫ�� ol�Ƿ�С��e2*/
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
//��˳������۰��������
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
//��˳�����һ��ϣ���������򡣱��㷨�Ǻ�һ��ֱ�Ӳ���������ȣ�
//  1.ǰ���¼λ�õ�������dk,������1;
//2. r[0]ֻ���ݴ浥Ԫ,�����ڱ�����j<=0ʱ������λ�����ҵ�.
int i,j;
for( i=dk+1; i<= L->length; ++ i )
	if (LT(L->r[i].key, L->r[i-dk].key)) 
	{
	 //�轫L.r[i]�������������ӱ� 
	 	compare[2]++;
		L->r[0] = L->r[i];  //�ݴ���L.r[0]
		move[2]++;
		for (j=i-dk; j>0&& LT(L->r[0].key, L->r[j].key); j-=dk){
			L->r[j+dk] = L->r[j];  //��¼���ƣ����Ҳ���λ��
			compare[2]++;
			move[2]++;
		}
		move[2]++;
		L->r[j+dk] = L->r[0];  //����
	}
}// ShellInsert..

void ShellSort(SqList *L, int dlta[], int t) {
//����������dita[0..t- 1]��˳���L��ϣ������
	int k;
	for (k=0;k<t;++k)
		ShellInsert(L,dlta[k]); //- �� ����Ϊdlta[k]�Ĳ�������
}// ShellSort

/**************** 4. BubbleSort *****************/
Status BubbleSort(SqList *L) { /*ð ������*/
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
/*һ�w��������*/
int Partition(SqList *L,int low,int high)
{
//�ָ�������
	L->r[0] = L->r[low];
	int pivotkey = L->r[low].key;//һ�㽫˳����һ��Ԫ����Ϊ֧��
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
	L->r[low] = L->r[0];//��������λ��
	return low;
}

void QSort(SqList *L,int low,int high)
{
//ÿ���ӱ�Ŀ�������
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
/*һ�w��������*/
void HeapAdjust(SqList *H,int s,int m)
{
//�ѵ���������¼����ΪС����
	int j;
	RedType rc = H->r[s];//��ʱ�洢�����
	for(j=2*s; j<=m; j*=2)
	{
//���Ž���¼��С������ɸѡ	
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


Status Merge(SqList *L,int low,int mid,int high){/*�����������������L.r[low.. mid]��L. r[mid+1.. high]�鲢�����������L. r[1ow. . high]*/

	int i=low, j=mid+1, k=0;  /*����ֵ*/

    SqList L1;  /*L1�ݴ�L.r[low.mid] ��L. r[mid+1.. high]�鲢��Ľ��*/

    L1.r = (RedType *)malloc( (high-low+1)*sizeof (RedType)) ;/*�����ڴ�*/
	if (!L1.r)
		exit(OVERFLOW) ;  /*�洢����ʧ�ܣ��˳�*/

	while ( i<=mid & j<=high )   /*���������зǿ�ʱ��ȡ��С�������L1. r[k]��*/
	{
			L1.r[k++] = LT(L->r[i]. key,L->r[j]. key)? L->r[i++]:L->r[j++];
			compare[7]++;
	}
	while ( i<=mid)  /*���Ƶ�һ�������е�ʣ���¼��L1*/
	{
			L1. r[k++]=L->r[i++];
			move[7]++;
		}
    while ( j<=high)/*���Ƶڶ��������е�ʣ���¼��L1*/
	{	L1. r[k++]=L->r[j++];
		move[7]++;
	}
	for ( k=0, i=low; i<=high; k++,i++)
	{
		L->r[i]. key=L1. r[k]. key;
		move[7]++;
	} /*���鲢�� �����ƻ�L->r[low. . high]*/
}/*Merge*/

void MSort (SqList *L, int len) {/*��L. r[L.L. length]���˹鲢����*/
	int i;
	for ( i=1; i+2*len-1<=L->length; i=i+2*len )/*�鲢����Ϊlen���������ڵ�������*/
		Merge(L, i, i+len-1, i+2*len-1);
	if ( i+len-1<L->length )/*����һ�������У��������һ�����ȶ�С��lens����ʱ����i<l->length��i+em-1>L->lengthʱ����ʣ��һ���������ֿգ�����鲢*/
		Merge(L,i, i+len- 1,L->length); /*�鲢����� ��������*/
} /*MSort*/

Status MergeSort(SqList *L){ /*�� L r[1.. n]�Ե����϶�·�鲢����*/
	int len;
	if ( !L->length ){
		printf("The Sqlist is Empty! ");
		return ERROR;

	}
	for ( len=1; len<L->length; len*=2 ) /*���� ����len��nʱ��ֹ*/
		MSort(L,len);
	return OK;
}










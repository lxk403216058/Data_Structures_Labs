#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
#define NULLKEY -1
#define MAXSIZE 100
#define OK 1

typedef int Status;
typedef int KeyType;
typedef struct {
	KeyType key;
}ElemType;
typedef struct {
	ElemType *elem;
	int count;
	int sizeindex;
	int p;
}HashTable;

void Init_HashTable(HashTable *,int []);
void Destory_HashTable(HashTable *);
void Create_Prime(HashTable *,int []);
int Judge_Prime(int );
int Hash(int, HashTable *);
Status Search_Hash(HashTable *, KeyType , int *, int *,int []);
Status Search_Hash1(HashTable *, KeyType , int *, int *,int []);
Status InsertHash(HashTable *,ElemType ,int []);
Status InsertHash1(HashTable *,ElemType ,int []);
void Recreate_HashTable(HashTable *,int []);
void Recreate_HashTable1(HashTable *,int []);
void collision(int *, int, HashTable *,KeyType ,int []);
void collision1(int *, int, HashTable *,KeyType ,int []);
void Print_HashTable(HashTable ,int []);

int main() {
	int hashsize[5] = {16,30,50,80,100};
	HashTable h;
	ElemType e;
	int p,flag, k, c = 0;
	Init_HashTable(&h,hashsize);

	
	//printf("\n %d", h.p);
	printf("选择散列方法：\n1.线性散列\n2.二次散列\n");
	while(1){
		printf("请输入1或2：\n");
		scanf("%d",&flag);
		if (flag==1){
		while (1){
		      printf("请输入要插入哈希表的关键字(-2退出)：");
		      scanf("%d", &e.key);
		      if (e.key == -2)
			    break;
		      InsertHash(&h,e,hashsize);
	    }
		Print_HashTable(h,hashsize);
	    while (1){
			printf("\n请输入要查询的关键字(-2退出):");
		    scanf("%d", &k);
		if (k == -2)
			break;
		if (Search_Hash(&h, k, &p, &c, hashsize) == SUCCESS)
			printf("查找到的位置，值：%d，%d",p, h.elem[p].key);
		else
			printf("无该数据!\n");
	    }
		}else if(flag==2){
			while (1){
		        printf("请输入要插入哈希表的关键字(-2退出)：");
		        scanf("%d", &e.key);
		        if (e.key == -2)
			    break;
		        InsertHash1(&h,e,hashsize);
	        }
			Print_HashTable(h,hashsize);
	        while (1){
			    printf("\n请输入要查询的关键字(-2退出):");
		        scanf("%d", &k);
		    if (k == -2)
			   break;
		    if (Search_Hash1(&h, k, &p, &c, hashsize) == SUCCESS)
			   printf("查找到的位置，值：%d，%d",p, h.elem[p].key);
		    else
			   printf("无该数据!\n");
	        }
		}else
		   break;
	}
	Destory_HashTable(&h);

	return 0;
}

void Init_HashTable(HashTable *H,int hashsize[]) {
	int i;

	Create_Prime(H, hashsize);
	H->count = 0;
	H->sizeindex = 0;
	H->elem = (ElemType*)malloc(hashsize[H->sizeindex]*sizeof(ElemType));
	if (!H->elem)
		exit(0);
	for (i = 0; i <hashsize[H->sizeindex]; i++)
		H->elem[i].key = NULLKEY;
}

void Destory_HashTable(HashTable *H) {
	free(H->elem);
	H->count = 0;
	H->elem = NULL;
	H->sizeindex = 0;
}

void Print_HashTable(HashTable H,int hashsize[]) {
	int i;
	printf("哈希表,位置:\n");

	for (i = 0; i < hashsize[H.sizeindex]; i++) {
		if (H.elem[i].key != NULLKEY)
			printf("%d     %d\n", H.elem[i].key,i);
	}
	printf("\n");
}

void Create_Prime(HashTable *H,int hashsize[]) {
	int i;
	for (i = hashsize[H->sizeindex]; i > 3; i--)
		if (Judge_Prime(i)) {
			H->p = i;
			break;
		}
			
}

int Hash(int key, HashTable *H) {
	return key % H->p;
}

int Judge_Prime(int m) {
	int i;

	for (i = 2; i < m; i++) {
		if (m%i == 0)
			return 0;
	}

	return 1;
}

Status Search_Hash(HashTable *H, KeyType K, int *p, int *c,int hashsize[]) {

	(*p) = Hash(K, H);
	while (H->elem[*p].key != NULLKEY && H->elem[*p].key != K)
		collision(p, (*c)++,H,K ,hashsize);
	if (H->elem[*p].key = K)
		return SUCCESS;
	else
		return UNSUCCESS;
}

Status Search_Hash1(HashTable *H, KeyType K, int *p, int *c,int hashsize[]) {

	(*p) = Hash(K, H);
	while (H->elem[*p].key != NULLKEY && H->elem[*p].key != K)
		collision1(p, (*c)++,H,K ,hashsize);
	if (H->elem[*p].key = K)
		return SUCCESS;
	else
		return UNSUCCESS;
}

void collision(int *p, int c, HashTable *H,KeyType K,int hashsize[]) {
	*p = (Hash(K, H) + c) % hashsize[H->sizeindex];
}

void collision1(int *p, int c, HashTable *H, KeyType K, int hashsize[]) {
	*p = (int)(Hash(K, H) + pow(-1, c)*pow((c-1)/2+1,2)) % hashsize[H->sizeindex];
	while(*p<0)
	   *p = *p + hashsize[H->sizeindex];
}

Status InsertHash(HashTable *H, ElemType e,int hashsize[]){
	int c = 0,p=0;
	if (Search_Hash(H, e.key, &p, &c,hashsize))
		return DUPLICATE;
	else if (c < hashsize[H->sizeindex] / 2) {
		H->elem[p] = e;
		H->count++;
		return OK;
	}
	else {
		Recreate_HashTable(H, hashsize);
		return UNSUCCESS;
	}
}

Status InsertHash1(HashTable *H, ElemType e,int hashsize[]){
	int c = 0,p=0;
	if (Search_Hash1(H, e.key, &p, &c,hashsize))
		return DUPLICATE;
	else if (c < hashsize[H->sizeindex] / 2) {
		H->elem[p] = e;
		H->count++;
		return OK;
	}
	else {
		Recreate_HashTable1(H, hashsize);
		return UNSUCCESS;
	}
}

void Recreate_HashTable(HashTable *H,int hashsize[]) {
	int i, count = H->count;
	ElemType *p, *elem = (ElemType *)malloc(count*sizeof(ElemType));
	p = elem;
	printf("重建哈希表\n");
	for (i = 0; i < hashsize[H->sizeindex]; i++) {
		if ((H->elem + i)->key != NULLKEY)
			*p++ = *(H->elem + i);
	}
	H->count = 0;
	H->sizeindex++;
	p = (ElemType *)realloc(H->elem,hashsize[H->sizeindex]*sizeof(ElemType));
	if (!p)
		exit(0);
	H->elem = p;
	for (i = 0; i < hashsize[H->sizeindex]; i++)
		H->elem->key = NULLKEY;
	for (p= elem; p < elem + count; p++)
		InsertHash(H, *p ,hashsize);
	free(elem);
}

void Recreate_HashTable1(HashTable *H,int hashsize[]) {
	int i, count = H->count;
	ElemType *p, *elem = (ElemType *)malloc(count*sizeof(ElemType));
	p = elem;
	printf("重建哈希表\n");
	for (i = 0; i < hashsize[H->sizeindex]; i++) {
		if ((H->elem + i)->key != NULLKEY)
			*p++ = *(H->elem + i);
	}
	H->count = 0;
	H->sizeindex++;
	p = (ElemType *)realloc(H->elem,hashsize[H->sizeindex]*sizeof(ElemType));
	if (!p)
		exit(0);
	H->elem = p;
	for (i = 0; i < hashsize[H->sizeindex]; i++)
		H->elem->key = NULLKEY;
	for (p= elem; p < elem + count; p++)
		InsertHash1(H, *p ,hashsize);
	free(elem);
}


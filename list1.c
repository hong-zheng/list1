#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 双向带头循环链表
typedef int Type;
typedef struct Node{
	Type _data;
	struct Node* _prev;
	struct Node* _next;
}Node;
typedef struct List{
	Node* _header;
}List;
Node* createNode(Type data){
	Node* node = (Node*)malloc(sizeof(Node));
	node->_data = data;
	node->_prev = node->_next = NULL;
	return node;
}
void listInit(List* lst){
	// 创建一个头结点，构成循环节点
	lst->_header = createNode(0);

	// 带头双向循环空链表
	// 前驱与后驱都指向本身
	lst->_header->_prev = lst->_header;
	lst->_header->_next = lst->_header;
}

void listPushBack(List* lst,Type data){
	Node* node = createNode(data);
	Node* last = lst->_header->_prev;
	// last node header

	// 创建一个新的节点就改变4个指向
	// 如果是空链表其操作也一样
	last->_next = node;
	node->_prev = last;

	node->_next = lst->_header;
	lst->_header->_prev = node;
}
void listPopBack(List* lst){
	// 不能删头
	// 表示空链表，因此无数据可以删除
	if (lst->_header->_next == lst->_header){
		return;
	}
	Node* last = lst->_header->_prev;
	Node* prev = last->_prev;

	// 连接prev 与 _header
	prev->_next = lst->_header;
	lst->_header->_prev = prev;
	free(last);
}


void listPushFront(List* lst, Type data){
	Node* cur = createNode(data);
	Node* front = lst->_header->_next;

	// 是否为空链表并不影响
	cur->_next = front;
	front->_prev = cur;

	lst->_header->_next = cur;
	cur->_prev = lst->_header;
}
void listPopFront(List* lst){
	if (NULL == lst){
		return;
	}
	// 需要 删除第一个有效节点
	if (lst->_header == lst->_header->_next){
		return;
	}
	Node* front = lst->_header->_next;
	Node* next = front->_next;

	lst->_header->_next = next;
	next->_prev = lst->_header;
	free(front);
}

// 在位置pos插入，就是在其前面插入一个数据，不能将其删除
void listInsert(Node* pos, Type data){
	Node* cur = createNode(data);
	Node* prev = pos->_prev;

	// 对prev进行操作
	prev->_next = cur;
	cur->_prev = prev;

	// 对pos进行操作
	cur->_next = pos;
	pos->_prev = cur;
}

void listErase(Node* pos){
	// 删除当前位置节点
	//头结点不可删除
	if (pos == pos->_next){
		return; // 空表不能删除
	}
	Node* prev = pos->_prev;
	Node* next = pos->_next;
	free(pos);
	pos = NULL;
	prev->_next = next;
	next->_prev = prev;

}
void listDestory(List* lst){
	Node* cur = lst->_header->_next;
	while (cur != lst->_header){
		Node* next = cur->_next;
		free(cur);
		cur = next;
	}
	free(lst->_header);
	lst->_header = NULL;
}

void display(List* lst){
	Node* cur = lst->_header->_next;
	while (cur != lst->_header){
		printf("%d ",cur->_data);
		cur = cur->_next;
	}
	printf("\n");
}
void testList(){
	List lst;
	listInit(&lst);
	listPushBack(&lst, 1);
	display(&lst);

	listPushBack(&lst, 2);
	display(&lst);

	listPushBack(&lst, 3);
	display(&lst);

	listPushBack(&lst, 4);
	display(&lst);

	listPopBack(&lst);
	display(&lst);

	listPopBack(&lst);
	display(&lst);

	listPopBack(&lst);
	display(&lst);

	listPushFront(&lst, 9);
	display(&lst);

	listPushFront(&lst, 8);
	display(&lst);

	listPushFront(&lst, 7);
	display(&lst);

	listPushFront(&lst, 6);
	display(&lst);

	listPopFront(&lst);
	display(&lst);

	listPopFront(&lst);
	display(&lst);

	listPopFront(&lst);
	display(&lst);

	listInsert((&lst)->_header->_next,12);
	display(&lst);

}

int  main(){
	testList();
	system("pause");
	return 0;
}
//// 栈的实现
//
//// 单链表: pushFront popFront
//// 顺序表: pushBack popBack  优先选择 栈的实现基本上都是顺序表实现
////#pragma once
//// 顺序表实现栈
//typedef struct Stack{
//	Type* _array; 
//	size_t _size;
//	size_t _capacity;
//}Stack;
//void stackInit(Stack* st,size_t n){
//	st->_capacity = n;
//	st->_array = (Type*)malloc(sizeof(Type)*st->_capacity);
//	st->_size = 0;
//}
//
//void stackPush(Stack* st, Type data){
//	// 检查容量
//	if (st->_size == st->_capacity){
//		st->_capacity *= 2;
//		st->_array = (Type*)realloc(st->_array,sizeof(Type)*st->_capacity);
//	}
//	st->_array[st->_size++] = data;
//}
//void stackPop(Stack* st){
//	// 尾删
//	if (NULL == st){
//		return;
//	}
//	if (st->_size){
//		st->_size--;
//	}
//}
//
//Type stackTop(Stack* st){
//	return st->_array[st->_size-1];
//}
//size_t stackSize(Stack* st){
//	return st->_size;
//}
//int stackEmpty(Stack* st){
//	if (st->_size == 0){
//		return 1;
//	}
//	return 0;
//}
//
//
//void stackDestory(Stack* st){
//	free(st->_array);
//	st->_array = NULL;
//	st->_size = st->_capacity = 0;
//}
//void testStack(){
//	Stack st;
//	stackInit(&st,5);
//	stackPush(&st, 1);
//	stackPush(&st, 2);
//	stackPush(&st, 3);
//	stackPush(&st, 4);
//	stackPush(&st, 5);
//	stackPush(&st, 6);
//	stackPush(&st, 7);
//	stackPush(&st, 8);
//	while ( stackEmpty(&st) != 1){
//		printf("%d ",stackTop(&st));
//		stackPop(&st);
//	}
//}
//int main(){
//	testStack();
//
//	system("pause");
//	return 0;
//}
//// slist.h
//typedef int SLTDateType;
//typedef struct SListNode
//{
//	SLTDateType data;
//	struct SListNode* next;
//}SListNode;
////typedef struct SList{
////	struct SListNode* head;
////};
//// 动态申请一个节点
//SListNode* BuySListNode(SLTDateType x){
//	SListNode* head = (SListNode*)malloc(sizeof(SListNode));
//	head->data = x;
//	head->next = NULL;
//	return head;
//}
//// 单链表打印
//void SListPrint(SListNode* plist){
//	SListNode* cur = plist;
//	while (cur){
//		printf("%d ",cur->data);
//		cur = cur->next;
//	}
//	printf("\n");
//}
//// 单链表尾插
//void SListPushBack(SListNode** pplist, SLTDateType x){
//	if (NULL == *pplist){
//		return;
//	}
//	SListNode* cur = *pplist;
//	while (cur && cur->next){
//		cur = cur->next;
//	}
//	SListNode* newnode = BuySListNode(x);
//	cur->next = newnode;
//	newnode->next = NULL;
//}
//// 单链表的头插
//void SListPushFront(SListNode** pplist, SLTDateType x){
//	if (NULL == *pplist){
//		return;
//	}
//	SListNode* newnode = BuySListNode(x);
//	SListNode* cur = *pplist;
//	while (cur){
//		
//	}
//}
//// 单链表的尾删
//void SListPopBack(SListNode** pplist){
//
//}
//// 单链表头删
//void SListPopFront(SListNode** pplist){
//
//}
//// 单链表查找
//SListNode* SListFind(SListNode* plist, SLTDateType x){
//	return NULL;
//}
//// 单链表在pos位置之后插入x
//// 分析思考为什么不在pos位置之前插入？
//void SListInsertAfter(SListNode* pos, SLTDateType x){
//
//}
//// 单链表删除pos位置之后的值
//// 分析思考为什么不删除pos位置？
//void SListEraseAfter(SListNode* pos){
//
//}
//// 单链表的销毁
//void SListDestory(SListNode* plist){
//
//}
//void test1(){
//	SListNode* head = BuySListNode(1);
//	SListPushBack(&head, 2);
//	SListPushBack(&head, 3);
//	SListPushBack(&head, 4);
//	SListPushBack(&head, 5);
//	SListPushBack(&head, 6);
//	SListPrint(head);
//}
//
//int main(){
//
//	system("pause");
//	return 0;
//}
//// 快速排序
//// 返回中间结点位置
//int piv(int* arr,int l,int h){
//	int indx = arr[l];
//	while (l<h){
//		while (l<h && arr[h]>=indx){
//			h--;
//		}
//		arr[l] = arr[h];
//		while (l<h&&arr[l]<indx){
//			l++;
//		}
//		arr[h] = arr[l];
//	}
//	arr[l] = indx;
//	return l;
//}
//void QSort(int* arr, int l ,int h){
//	if (l<h){
//		int m = piv(arr,l,h);
//		QSort(arr, l, m - 1);
//		QSort(arr, m+1, h);
//	}
//}
//void QSORT(int* arr,int length){
//	QSort(arr, 0, length-1);
//}
//int main(){
//	int arr[] = {432,9,0,1,32,9,37,0,10,3,7,8,5,36};
//	QSORT(arr,sizeof(arr)/sizeof(arr[0]));
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]);i++){
//		printf("%d ",arr[i]);
//	}
//	system("pause");
//	return 0;
//}


//// 插入排序
//void insert_sort(int* arr,int length){
//	for (int i = 1; i < length;i++){
//		if (arr[i] < arr[i-1]){
//			int j = 0;
//			int cur = arr[i];
//			for (j = i - 1; i >= 0 && arr[j] > cur;j--){
//				arr[j + 1] = arr[j];
//			}
//			arr[j + 1] = cur;
//		}
//	}
//}
//// 希尔排序
//void shellSort(int* arr,int length){
//	int step = length / 2;
//	while (step>=1){
//		for (int i = step; i < length;i++){
//			if (arr[i] < arr[i-1]){
//				int j = 0;
//				int cur = arr[i];
//				for (j = i - step; j >= 0 && arr[j] > cur;j-=step){
//					arr[j + step] = arr[j];
//				}
//				arr[j + step] = cur;
//			}
//		}
//		step /= 2;
//	}
//}
//// 归并排序
//void merge(int* arr,int l,int m,int r){
//	int len = r - l + 1;
//	int* newArr = (int*)malloc(sizeof(int)*len);
//	int left = l;
//	int right = m+1;
//	int k = 0;
//	while (left<=m && right<=r){
//		if (arr[left] < arr[right]){
//			newArr[k++] = arr[left++];
//		}
//		else{
//			newArr[k++] = arr[right++];
//		}
//	}
//	while (left<=m){
//		newArr[k++] = arr[left++];
//	}
//	while (right<=r){
//		newArr[k++] = arr[right++];
//	}
//	memcpy(arr+l,newArr,sizeof(int)*len);
//	free(newArr);
//	newArr = NULL;
//}
//void chaifen(int* arr,int l,int r){
//	if (l == r){
//		return;
//	}
//	int m = l + (r - l) / 2;
//	chaifen(arr, l, m);
//	chaifen(arr, m+1, r);
//	merge(arr,l,m,r);
//}
//void MERGE(int* arr,int len){
//	chaifen(arr,0,len-1);
//}
//
//
//// 快速排序
//int piv(int* arr,int l,int h){
//	int cur = arr[l];
//	while (l<h){
//		while (l<h && cur<=arr[h]){
//			h--;
//		}
//		arr[l] = arr[h];
//		while (l<h && cur>arr[l]){
//			l++;
//		}
//		arr[h] = arr[l];
//	}
//	arr[l] = cur;
//	return l;
//}
//void QSort(int* arr,int l,int h){
//	if (l<h){
//		int pivindx = piv(arr, l, h);
//		QSort(arr, l, pivindx - 1);
//		QSort(arr, pivindx + 1, h);
//	}
//}
//void QSORT(int* arr,int len){
//	QSort(arr,0,len-1);
//}
//
//
//void move(char A,char B){
//	printf("%c -> %c\n",A,B);
//}
//
//void hanio(int n,char one,char two,char three){
//	if (1 == n){
//		move(one,three);
//	}
//	else
//	{
//		hanio(n - 1, one, three, two);
//		move(one, three);
//		hanio(n - 1, two, one, three);
//	}
//}
// 一轮快速排序的结果，返回中间对比值位置
//int piv(int* arr,int l,int h){
//	int indx = arr[l];
//	while (l<h){
//		while (l<h && arr[h]>=indx){
//			h--;
//		}
//		arr[l] = arr[h];
//		while (l<h && arr[l]<indx){
//			l++;
//		}
//		arr[h] = arr[l];
//	}
//	arr[l] = indx;
//	return l;
//}
//// 递归排序，直到中间为止
//void QSort(int* arr,int l,int h){
//	if (l<h){
//		int pivindx = piv(arr,l,h);
//		QSort(arr, l, pivindx - 1);
//		QSort(arr, pivindx+1,h);
//	}
//}
//void QSORT(int* arr,int len){
//	QSort(arr,0,len-1);
//}
////归并排序
//// 先归并
//void merge(int* arr,int l,int m,int r){
//	int len = r - l + 1;
//	int* newArr = (int*)malloc(sizeof(int)*len);
//	int k = 0;
//	int left = l;
//	int right = m + 1;
//	while (left<=m && right<=r){
//		if (arr[left] < arr[right]){
//			newArr[k++] = arr[left++];
//		}
//		else{
//			newArr[k++] = arr[right++];
//		}
//	}
//	while (left<=m){
//		newArr[k++] = arr[left++];
//	}
//	while (right<=r){
//		newArr[k++] = arr[right++];
//	}
//	memcpy(arr+l,newArr,sizeof(int)*len);
//	free(newArr);
//	newArr = NULL;
//}
//void chaifen(int* arr,int l,int r){
//	if (l == r){
//		return;
//	}
//	int m = l + (r - l) / 2;
//	chaifen(arr, l, m);
//	chaifen(arr, m+1, r);
//	merge(arr,l,m,r);
//}
//void MERGE(int* arr,int len){
//	chaifen(arr,0,len-1);
//}
//
//// 插入排序
//void insert(int* arr,int length){
//	for (int i = 1; i < length;i++){
//		if (arr[i] < arr[i-1]){
//			int j = 0;
//			int cur = arr[i];
//			for (j = i - 1; j >= 0 && arr[j] > cur;j--){
//				arr[j + 1] = arr[j];
//			}
//			arr[j + 1] = cur;
//		}
//	}
//}
////希尔排序
//void shellSort(int* arr,int length){
//	int step = length / 2;
//	while (step>=1){
//		for (int i = step; i < length;i++){
//			for (int j = 1; j < length;j++){
//				if (arr[j] < arr[j-1]){
//					int k = 0;
//					int cur = arr[j];
//					for (k = j - step; k >= 0 && cur < arr[k];k-=step){
//						arr[k + step] = arr[k];
//					}
//					arr[k + step] = cur;
//				}
//			}
//		}
//		step /= 2;
//	}
//}
//#define LEN 19
//#define MAXNUM 432
//void radix(int* arr,int length){
//	int tmp[MAXNUM+1];
//	memset(tmp,0,sizeof(int)*(MAXNUM+1));
//	for (int i = 0; i < length;i++){
//		tmp[arr[i]]++;
//	}
//	for (int i = 0; i < MAXNUM + 1;i++){
//		while (tmp[i]--){
//			printf("%d ",i);
//		}
//	}
//	printf("\n");
//}
//void bucket(int* arr,int length){
//	for (int i = 1; i < MAXNUM;i*=10){
//		int tmp[10][LEN];
//		memset(tmp, -1, sizeof(int)*LEN * 10);
//		for (int j = 0; j < length;j++){
//			int m = arr[j] / i % 10;
//			tmp[m][j] = arr[j];
//		}
//		int k = 0;
//		for (int i = 0; i < 10;i++){
//			for (int j = 0; j < LEN;j++){
//				if (-1 != tmp[i][j]){
//					arr[k++] = tmp[i][j];
//				}
//			}
//		}
//	}
//}
//// 选择排序
//void select(int* arr,int length){
//	for (int i = 0; i < length;i++){
//		int cur = arr[i];
//		int flag = -1;
//		for (int j = i + 1; j < length;j++){
//			if (arr[j] < cur){
//				cur = arr[j];
//				flag = j;
//			}
//		}
//		if (flag>0){
//			arr[flag] = arr[i];
//			arr[i] = cur;
//		}
//	}
//}
//int main(){
//	
//
//
//
//	int arr[] = {1,432,9,0,1,32,9,74,32,8,9,37,0,10,3,7,8,5,36};
//	select(arr, sizeof(arr) / sizeof(arr[0]));
//	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]);i++){
//		printf("%d ",arr[i]);
//	}
//	system("pause");
//	return 0;
//}
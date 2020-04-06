#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// ˫���ͷѭ������
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
	// ����һ��ͷ��㣬����ѭ���ڵ�
	lst->_header = createNode(0);

	// ��ͷ˫��ѭ��������
	// ǰ���������ָ����
	lst->_header->_prev = lst->_header;
	lst->_header->_next = lst->_header;
}

void listPushBack(List* lst,Type data){
	Node* node = createNode(data);
	Node* last = lst->_header->_prev;
	// last node header

	// ����һ���µĽڵ�͸ı�4��ָ��
	// ����ǿ����������Ҳһ��
	last->_next = node;
	node->_prev = last;

	node->_next = lst->_header;
	lst->_header->_prev = node;
}
void listPopBack(List* lst){
	// ����ɾͷ
	// ��ʾ��������������ݿ���ɾ��
	if (lst->_header->_next == lst->_header){
		return;
	}
	Node* last = lst->_header->_prev;
	Node* prev = last->_prev;

	// ����prev �� _header
	prev->_next = lst->_header;
	lst->_header->_prev = prev;
	free(last);
}


void listPushFront(List* lst, Type data){
	Node* cur = createNode(data);
	Node* front = lst->_header->_next;

	// �Ƿ�Ϊ��������Ӱ��
	cur->_next = front;
	front->_prev = cur;

	lst->_header->_next = cur;
	cur->_prev = lst->_header;
}
void listPopFront(List* lst){
	if (NULL == lst){
		return;
	}
	// ��Ҫ ɾ����һ����Ч�ڵ�
	if (lst->_header == lst->_header->_next){
		return;
	}
	Node* front = lst->_header->_next;
	Node* next = front->_next;

	lst->_header->_next = next;
	next->_prev = lst->_header;
	free(front);
}

// ��λ��pos���룬��������ǰ�����һ�����ݣ����ܽ���ɾ��
void listInsert(Node* pos, Type data){
	Node* cur = createNode(data);
	Node* prev = pos->_prev;

	// ��prev���в���
	prev->_next = cur;
	cur->_prev = prev;

	// ��pos���в���
	cur->_next = pos;
	pos->_prev = cur;
}

void listErase(Node* pos){
	// ɾ����ǰλ�ýڵ�
	//ͷ��㲻��ɾ��
	if (pos == pos->_next){
		return; // �ձ���ɾ��
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
//// ջ��ʵ��
//
//// ������: pushFront popFront
//// ˳���: pushBack popBack  ����ѡ�� ջ��ʵ�ֻ����϶���˳���ʵ��
////#pragma once
//// ˳���ʵ��ջ
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
//	// �������
//	if (st->_size == st->_capacity){
//		st->_capacity *= 2;
//		st->_array = (Type*)realloc(st->_array,sizeof(Type)*st->_capacity);
//	}
//	st->_array[st->_size++] = data;
//}
//void stackPop(Stack* st){
//	// βɾ
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
//// ��̬����һ���ڵ�
//SListNode* BuySListNode(SLTDateType x){
//	SListNode* head = (SListNode*)malloc(sizeof(SListNode));
//	head->data = x;
//	head->next = NULL;
//	return head;
//}
//// �������ӡ
//void SListPrint(SListNode* plist){
//	SListNode* cur = plist;
//	while (cur){
//		printf("%d ",cur->data);
//		cur = cur->next;
//	}
//	printf("\n");
//}
//// ������β��
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
//// �������ͷ��
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
//// �������βɾ
//void SListPopBack(SListNode** pplist){
//
//}
//// ������ͷɾ
//void SListPopFront(SListNode** pplist){
//
//}
//// ���������
//SListNode* SListFind(SListNode* plist, SLTDateType x){
//	return NULL;
//}
//// ��������posλ��֮�����x
//// ����˼��Ϊʲô����posλ��֮ǰ���룿
//void SListInsertAfter(SListNode* pos, SLTDateType x){
//
//}
//// ������ɾ��posλ��֮���ֵ
//// ����˼��Ϊʲô��ɾ��posλ�ã�
//void SListEraseAfter(SListNode* pos){
//
//}
//// �����������
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
//// ��������
//// �����м���λ��
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


//// ��������
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
//// ϣ������
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
//// �鲢����
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
//// ��������
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
// һ�ֿ�������Ľ���������м�Ա�ֵλ��
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
//// �ݹ�����ֱ���м�Ϊֹ
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
////�鲢����
//// �ȹ鲢
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
//// ��������
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
////ϣ������
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
//// ѡ������
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
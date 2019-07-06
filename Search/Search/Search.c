#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define LH +1//���
#define EH 0//�ȸ�
#define RH -1 //�Ҹ�

//����������
typedef struct BiTNode{
	int data;
	struct BiTNode *left;
	struct BiTNode *right;
}BitNode,*BiTree;
//ƽ�������
typedef struct BiTree{
	int data;
	int bf;
	struct BiTree *lchild;
	struct BiTree *rchild;
}BiNode,*BiNode_t;
//˳������
int Sequential_Search(int arr[], int key, int len){
	int i = 0;
	for (i = 0; i < len; i++){
		if (arr[i] == key){
			return i;
		}
	}
	return -1;
}
//��������-���ֲ���
int Binary_Search(int arr[], int key, int len){
	int left = 0;
	int right = len - 1;
	int quit = 0;
	while (!quit){
		int mid = (left + right) / 2;
		if (key == arr[mid]){
			return mid;
		}
		if (key < arr[mid]){
			right = mid - 1;
		}
		if (key>arr[mid]){
			left = mid + 1;
		}
	}
	return -1;
}
//�������-��ֵ����
int Insert_Search(int arr[], int key, int len){
	int left = 0;
	int right = len - 1;
	int quit = 0;
	while (!quit){
		int mid = left + ((key - arr[left]) / (arr[right] - arr[left]))*(arr[right] - arr[left]);
		if (key == arr[mid]){
			return mid;
		}
		if (key < arr[mid]){
			right = mid - 1;
		}
		if (key>arr[mid]){
			left = mid + 1;
		}
	}
	return -1;
}
//쳲���������
//int Fibonacci_Search(int arr[], int len, int key){
//	int low, high, mid, i, k;
//	low = 0;
//	high = len - 1;
//	k = 0;
//	
//}
//��������
//����
void Insert_Tree(BiTree *t, int num){
	BiTree s;
	if (*t == NULL){
		s = (BiTree)malloc(sizeof(BitNode));
		s->data = num;
		s->left = NULL;
		s->right = NULL;
		*t = s;
	}
	else{
		if ((*t)->data > num){
			Insert_Tree(&(*t)->left, num);
		}
		if ((*t)->data < num){
			Insert_Tree(&(*t)->right, num);
		}
	}
}
//������������
void Create_Tree(BiTree *t){
	int key;
	*t = NULL;
	printf("���������֣�\n");
	scanf("%d", &key);
	while (key != -1){
		Insert_Tree(t, key);
		printf("��������룺\n");
		scanf("%d", &key);
	}
}
//����
void Search_Tree(BiTree t, int key){
	if (key == t->data){
		printf("�ɹ��ҵ�:%d\n",t->data);
	}
	else if (key < t->data){
		Search_Tree(t->left, key);
	}
	else{
		Search_Tree(t->right, key);
	}
}
void Delet(BiTree *m){
	BiTree s, q;
	if ((*m)->right == NULL){
		q = *m;
		*m = (*m)->left;
		free(q);
	}
	else if ((*m)->left == NULL){
		q = *m;
		*m = (*m)->right;
		free(q);
	}
	else{
		q = *m;
		s = (*m)->left;
		while (s->right){
			q = s;
			s = s->right;
		}
		(*m)->data = s->data;
		if (q != *m){
			q->right = s->left;
		}
		else{
			q->left = s->left;
		}
		free(s);
	}
}
BiTree Delete_Tree(BiTree t, int key){
	BiTree bt;
	bt = t;
	if (bt == NULL){
		printf("���գ��޷�������\n");
	}
	else {
		if (key == bt->data){
			Delet(&bt);
			printf("��ɾ����\n");
		}
		else if (key < bt->data){
			Delete_Tree(bt->left, key);
		}
		else{
			Delete_Tree(bt->right, key);
		}
	}
	return t;
}
//ƽ�������_����
void R_Rotate(BiNode_t *bp){
	BiNode_t l;
	l = (*bp)->lchild;
	(*bp)->lchild = l->rchild;
	l->rchild = (*bp);
	*bp = l;
}
//ƽ�������_����
void L_Rotate(BiNode_t *bp){
	BiNode_t r;
	r = (*bp)->rchild;
	(*bp)->rchild = r->lchild;
	r->lchild = (*bp);
	(*bp) = r;
}
//��ƽ����ת����
void LeftBanlance(BiNode_t *bt){//����ú���ʱ��������Ѿ���ƽ�������������ϸ�����
	BiNode_t l, lr;
	l = (*bt)->lchild;
	switch (l->bf){
	case LH://��������bf������ͬ��
		(*bt)->bf = l->bf = EH;
		R_Rotate(bt);//ֻ��Ҫ�Ը������������
		break;
	case RH://�������������bf�෴����Ը��������������������жϣ�����������ת����ƽ��
		lr = l->rchild;
		switch(lr->bf){
		case LH:
			(*bt)->bf = RH;
			l->bf = EH;
			break;
		case EH:
			(*bt)->bf = l->bf = EH;
			break;
		case RH:
			(*bt)->bf = EH;
			l->bf = LH;
			break;
		}
		lr->bf = EH;
		L_Rotate(&(*bt)->lchild);//�ȶԸ�������������������
		R_Rotate(bt);//�ٶԸ�����������
	}
}
//��ƽ����ת����
void RightBanlance(BiNode_t *bt){//����ú���ʱ��������Ѿ���ƽ�������������ϸ�����
	BiNode_t r, rl;
	r = (*bt)->rchild;
	switch (r->bf){
	case LH://�������������bf�෴����Ը��������������������жϣ�����������ת����ƽ��
		rl =r->lchild;
		switch (rl->bf){
		case LH:
			(*bt)->bf = EH;
			r->bf = RH;
			break;
		case EH:
			(*bt)->bf = r->bf = EH;
			break;
		case RH:
			(*bt)->bf = LH;
			r->bf = EH;
			break;
		}
		rl->bf = EH;
		R_Rotate(&(*bt)->rchild);//�ȶԸ�������������������
		L_Rotate(bt);//�ٶԸ�����������
 		break;
	case RH://��������bf������ͬ��
		(*bt)->bf = r->bf = EH;
		L_Rotate(bt);//ֻ��Ҫ�Ը������������
		break;
	}
}
//ƽ�������_����
int InsertAVL(BiNode_t *bt, int e, int *taller){//taller��ӳ�Ƿ�������ݣ����Ƿ񳤸ߣ���Ϊ1���ʾ���볤�ߣ���Ϊ0���ʾδ���롣
	if (!*bt){//Ϊ��ǰ�½������ռ䣬�����ߣ���tallerΪ1
		*bt = (BiNode_t)malloc(sizeof(BiNode));
		(*bt)->data = e;
		(*bt)->lchild = (*bt)->rchild = NULL;
		(*bt)->bf = EH;
		*taller = 1;
	}
	else{
		if (e == (*bt)->data){//�����Ѵ��ں�e��ͬ�ؼ��ֵĽ�����ٲ���
			*taller = 0;
			return 0;
		}
		if (e < (*bt)->data){//�ڵ�ǰ�����������м���Ѱ��
			if (!InsertAVL(&(*bt)->lchild, e, taller)){//δ����
				return 0;
			}
			if (*taller){//�Ѳ�����������������������
				switch ((*bt)->bf){
				case LH://ԭ�����������������ߣ��ֲ�������������Ҫ��ƽ�⴦��
					LeftBanlance(bt);
					*taller = 0;
					break;
				case EH://ԭ�����������ȸߣ��ֲ�����������������
					(*bt)->bf = LH;
					*taller = 1;
					break;
				case RH://ԭ�����������������ߣ��ֲ��������������ȸ�
					(*bt)->bf = EH;
					*taller = 0;
					break;
				}
			}
		}
		else{
			if (!InsertAVL(&(*bt)->rchild, e, taller)){//δ����
				return 0;
			}
			if (*taller){//�Ѳ�����������������������
				switch ((*bt)->bf){
				case LH://ԭ�����������������ߣ��ֲ��������������ȸ�
					(*bt)->bf = EH;
					*taller = 0;
					break;
				case EH://ԭ�����������ȸߣ��ֲ�����������������
					(*bt)->bf = RH;
					*taller = 1;
					break;
				case RH://ԭ�����������������ߣ��ֲ�������������Ҫ����ƽ�⴦��
					RightBanlance(bt);
					*taller = 0;
					break;
				}
			}
		}
	}
	return 1;
}
//ƽ�������_����
void Create_BalanceTree(BiNode_t *bt){
	int i;
	int arr[] = { 12, 34, 65, 10, 3, 54, 6, 70, 4, 21 };
	int taller;
	int len = sizeof(arr) / sizeof(arr[0]);
	for (i = 0; i < len; i++){
		InsertAVL(bt, arr[i], &taller);//�������е�ÿ��Ԫ�ص��ò��뺯�����β����������
	}
}
//ɢ�б��ѵ���ʵ��
int main(){
	BiTree t;
	int i = 0;
	t = (BiTree)malloc(sizeof(BitNode));
	//�Ӽ����������빹������������
	Create_Tree(&t);
	//ֱ�����������е����ֹ�������������
	t = NULL;
	int arr[10] = { 12, 56, 32, 19, 10, 4, 67, 3, 21 };
	for (i = 0; i < 10; i++){
		Insert_Tree(&t, arr[i]);
	}
	BiNode_t bt = NULL;
	Create_BalanceTree(&bt);
	//����
	Search_Tree(t, 10);
	//ɾ��
	Delete_Tree(t, 10);
	/*Search_Tree(t, 5);*/
	system("pause");
	return 0;
}
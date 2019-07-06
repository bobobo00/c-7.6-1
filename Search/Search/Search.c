#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

#define LH +1//左高
#define EH 0//等高
#define RH -1 //右高

//二叉排序树
typedef struct BiTNode{
	int data;
	struct BiTNode *left;
	struct BiTNode *right;
}BitNode,*BiTree;
//平衡二叉树
typedef struct BiTree{
	int data;
	int bf;
	struct BiTree *lchild;
	struct BiTree *rchild;
}BiNode,*BiNode_t;
//顺序表查找
int Sequential_Search(int arr[], int key, int len){
	int i = 0;
	for (i = 0; i < len; i++){
		if (arr[i] == key){
			return i;
		}
	}
	return -1;
}
//有序表查找-二分查找
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
//有序查找-插值查找
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
//斐波那契查找
//int Fibonacci_Search(int arr[], int len, int key){
//	int low, high, mid, i, k;
//	low = 0;
//	high = len - 1;
//	k = 0;
//	
//}
//倒排索引
//插入
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
//创建二叉排序
void Create_Tree(BiTree *t){
	int key;
	*t = NULL;
	printf("请输入数字：\n");
	scanf("%d", &key);
	while (key != -1){
		Insert_Tree(t, key);
		printf("请继续输入：\n");
		scanf("%d", &key);
	}
}
//查找
void Search_Tree(BiTree t, int key){
	if (key == t->data){
		printf("成功找到:%d\n",t->data);
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
		printf("树空，无法操作！\n");
	}
	else {
		if (key == bt->data){
			Delet(&bt);
			printf("已删除！\n");
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
//平衡二叉树_右旋
void R_Rotate(BiNode_t *bp){
	BiNode_t l;
	l = (*bp)->lchild;
	(*bp)->lchild = l->rchild;
	l->rchild = (*bp);
	*bp = l;
}
//平衡二叉树_左旋
void L_Rotate(BiNode_t *bp){
	BiNode_t r;
	r = (*bp)->rchild;
	(*bp)->rchild = r->lchild;
	r->lchild = (*bp);
	(*bp) = r;
}
//左平衡旋转处理
void LeftBanlance(BiNode_t *bt){//进入该函数时即根结点已经不平衡是由左子树较高引起
	BiNode_t l, lr;
	l = (*bt)->lchild;
	switch (l->bf){
	case LH://左子树的bf与根结点同向
		(*bt)->bf = l->bf = EH;
		R_Rotate(bt);//只需要对根结点右旋即可
		break;
	case RH://左子树与根结点的bf相反，需对该右子树的左子树继续判断，进行两次旋转才能平衡
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
		L_Rotate(&(*bt)->lchild);//先对根结点的右子树进行左旋
		R_Rotate(bt);//再对根结点进行右旋
	}
}
//右平衡旋转处理
void RightBanlance(BiNode_t *bt){//进入该函数时即根结点已经不平衡是由右子树较高引起
	BiNode_t r, rl;
	r = (*bt)->rchild;
	switch (r->bf){
	case LH://右子树与根结点的bf相反，需对该右子树的左子树继续判断，进行两次旋转才能平衡
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
		R_Rotate(&(*bt)->rchild);//先对根结点的右子树进行右旋
		L_Rotate(bt);//再对根结点进行左旋
 		break;
	case RH://右子树的bf与根结点同向
		(*bt)->bf = r->bf = EH;
		L_Rotate(bt);//只需要对根结点左旋即可
		break;
	}
}
//平衡二叉树_插入
int InsertAVL(BiNode_t *bt, int e, int *taller){//taller反映是否插入数据，树是否长高，若为1则表示插入长高，若为0则表示未插入。
	if (!*bt){//为当前新结点申请空间，树长高，置taller为1
		*bt = (BiNode_t)malloc(sizeof(BiNode));
		(*bt)->data = e;
		(*bt)->lchild = (*bt)->rchild = NULL;
		(*bt)->bf = EH;
		*taller = 1;
	}
	else{
		if (e == (*bt)->data){//树中已存在和e相同关键字的结点则不再插入
			*taller = 0;
			return 0;
		}
		if (e < (*bt)->data){//在当前树的左子树中继续寻找
			if (!InsertAVL(&(*bt)->lchild, e, taller)){//未插入
				return 0;
			}
			if (*taller){//已插入左子树中且左子树长高
				switch ((*bt)->bf){
				case LH://原本左子树比右子树高，现插入左子树后需要左平衡处理
					LeftBanlance(bt);
					*taller = 0;
					break;
				case EH://原本左右子树等高，现插入左子树后树长高
					(*bt)->bf = LH;
					*taller = 1;
					break;
				case RH://原本右子树比左子树高，现插入左子树后树等高
					(*bt)->bf = EH;
					*taller = 0;
					break;
				}
			}
		}
		else{
			if (!InsertAVL(&(*bt)->rchild, e, taller)){//未插入
				return 0;
			}
			if (*taller){//已插入右子树中且右子树长高
				switch ((*bt)->bf){
				case LH://原本左子树比右子树高，现插入右子树后树等高
					(*bt)->bf = EH;
					*taller = 0;
					break;
				case EH://原本左右子树等高，现插入右子树后树长高
					(*bt)->bf = RH;
					*taller = 1;
					break;
				case RH://原本右子树比左子树高，现插入右子树，需要做右平衡处理
					RightBanlance(bt);
					*taller = 0;
					break;
				}
			}
		}
	}
	return 1;
}
//平衡二叉树_构建
void Create_BalanceTree(BiNode_t *bt){
	int i;
	int arr[] = { 12, 34, 65, 10, 3, 54, 6, 70, 4, 21 };
	int taller;
	int len = sizeof(arr) / sizeof(arr[0]);
	for (i = 0; i < len; i++){
		InsertAVL(bt, arr[i], &taller);//对数组中的每个元素调用插入函数依次插入二叉树。
	}
}
//散列表已单独实现
int main(){
	BiTree t;
	int i = 0;
	t = (BiTree)malloc(sizeof(BitNode));
	//从键盘依次输入构建二叉排序树
	Create_Tree(&t);
	//直接利用数组中的数字构建二叉排序树
	t = NULL;
	int arr[10] = { 12, 56, 32, 19, 10, 4, 67, 3, 21 };
	for (i = 0; i < 10; i++){
		Insert_Tree(&t, arr[i]);
	}
	BiNode_t bt = NULL;
	Create_BalanceTree(&bt);
	//查找
	Search_Tree(t, 10);
	//删除
	Delete_Tree(t, 10);
	/*Search_Tree(t, 5);*/
	system("pause");
	return 0;
}
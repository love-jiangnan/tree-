#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<stack>
using namespace std;
typedef struct SortTree {
	int data;//存放数据的数据域
	struct SortTree* left;//指针域 左指针
	struct SortTree* right;//指针域 右指针
}Node,*bitree;
/*全局变量*/
Node* root;//根节点

void Init(int);//初始化操作
void insert(int);//插入操作
void IsEmpty(Node* root)
void IsEmpty(Node* root)
int delete_node(Node*, int);
Node* prev_node(Node*, Node*, int);
bool search(Node* root, int key);

//递归
PreOrder(root)//前序
MidOrder(root)//中
BehOrder(root)//后
FloorPrint(root)//层
//非递归
_Preorder(root)//前
_Midorder(root)//中
_Postorder(root)//后

menu();//菜单
menu1();//选择展示的顺序；
int main(void);
#define STACK_INIT_SIZE 10000
#define OK
#define SUCCESS 1
#define ERROR 0

#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<stack>
using namespace std;
typedef struct SortTree {
    int data;//存放数据的数据域
    struct SortTree* left;//指针域 左指针
    struct SortTree* right;//指针域 右指针
}Node, * bitree;
/*全局变量*/
Node* root;//根节点
typedef int ElemType;
/*初始化根节点
int key : 根节点的值
*/

void Init(int key)
{
    root = (Node*)malloc(sizeof(Node));
    printf("\n请输入根结点的数据：");
    root->data = judge();
    root->left = NULL;
    root->right = NULL;
    printf("\n初始化根节点成功！\n");
}
bool IsInit(bitree root) {
    if (root == NULL) {
        printf("\n树未初始化，请先初始化！\n\n");
        return ERROR;
    }
    else if (root->data != NULL)return SUCCESS;

}
bool IsEmpty(bitree T) {
    if (T->left == NULL && T->right == NULL)return SUCCESS;
    else return ERROR;
}


void insert(int key)
{
    //定义一个临时指针 用于移动
    Node* temp = root;//方便移动 以及 跳出循环
    Node* prev = NULL;//定位到待插入位置的前一个结点
    if (temp == NULL)printf("未初始化根，请先初始化根");
    else while (temp != NULL)
    {
        prev = temp;
        if (key < temp->data)
        {
            temp = temp->left;
        }
        else if (key > temp->data)
        {
            temp = temp->right;
        }
        else
        {
            return;
        }
    }

    if (key < prev->data)
    {
        prev->left = (Node*)malloc(sizeof(Node));
        prev->left->data = key;
        prev->left->left = NULL;
        prev->left->right = NULL;
    }
    else
    {
        prev->right = (Node*)malloc(sizeof(Node));
        prev->right->data = key;
        prev->right->left = NULL;
        prev->right->right = NULL;
    }
    printf("插入节点成功");
    return;
}

/*查找元素key*/
bool search(Node* root, int key)
{
    while (root != NULL)
    {
        if (key == root->data)
            return SUCCESS;
        else if (key < root->data)
            root = root->left;
        else
            root = root->right;
    }
    return ERROR;
}
/*定位到待删除节点的前一个结点
Node* root 从根节点开始
Node* node 待删除的结点
int key 待删除数据
*/
Node* prev_node(Node* root, Node* node, int key)
{
    if (root == NULL || node == root)
    {
        return node;
    }
    else
    {
        if (root->left != NULL && root->left->data == key)
        {
            return root;
        }
        else if (root->right != NULL && root->right->data == key)
        {
            return root;
        }
        else if (key < root->data)
        {
            return prev_node(root->left, node, key);
        }
        else
        {
            return prev_node(root->right, node, key);
        }
    }
}
int delete_node(Node* node, int key)
{
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        if (node->data == key)
        {
            //当我执行删除操作 需要先定位到前一个结点
            Node* tempNode = prev_node(root, node, key);
            Node* temp = NULL;
            /*
            如果右子树为空 只需要重新连接结点
            叶子的情况也包含进去了 直接删除
            */
            if (node->right == NULL)
            {
                temp = node;
                node = node->left;
                /*为了判断 待删除结点是前一个结点的左边还是右边*/
                if (tempNode->left->data == temp->data)
                {
                    Node* free_node = temp;//释放用的指针
                    tempNode->left = node;
                    free(free_node);
                    free_node = NULL;
                }
                else
                {
                    Node* free_node = temp;//释放用的指针
                    tempNode->right = node;
                    free(free_node);
                    free_node = NULL;
                }
            }
            else if (node->left == NULL)
            {
                temp = node;
                node = node->right;
                if (tempNode->left->data == temp->data)
                {
                    Node* free_node = temp;//释放用的指针
                    tempNode->left = node;
                    free(free_node);
                    free_node = NULL;
                }
                else
                {
                    Node* free_node = temp;//释放用的指针
                    tempNode->right = node;
                    free(free_node);
                    free_node = NULL;
                }
            }
            else//左右子树都不为空
            {
                temp = node;
                /*往左子树 找最大值*/
                Node* left_max = node;//找最大值的临时指针
                left_max = left_max->left;//先到左孩子结点
                while (left_max->right != NULL)
                {
                    temp = left_max;
                    left_max = left_max->right;
                }
                node->data = left_max->data;
                if (temp != node)
                {
                    temp->right = left_max->left;
                    free(left_max);
                    left_max = NULL;
                }
                else
                {
                    temp->left = left_max->left;
                    free(left_max);
                    left_max = NULL;
                }
            }

        }
        else if (key < node->data)
        {
            delete_node(node->left, key);
        }
        else if (key > node->data)
        {
            delete_node(node->right, key);
        }
    }
    printf("\n删除结点成功\n");
    return SUCCESS;
}

//  递归-先序遍历
void PreOrder(bitree T) {
    if (!T)
        return;
    printf("%d ", T->data); //打印等操作
    PreOrder(T->left);
    PreOrder(T->right);
    return;
}

//  递归-中序遍历
void MidOrder(bitree T) {
    if (!T)
        return;
    if (T->left)
        MidOrder(T->left);
    printf("%d ", T->data);
    if (T->right)
        MidOrder(T->right);
    return;
}
//  递归-后序遍历
void BehOrder(bitree T) {
    if (!T)
        return;
    if (T->left)
        BehOrder(T->left);
    if (T->right)
        BehOrder(T->right);
    printf("%d ", T->data);
    return;
}


//  非递归-先序遍历
void _Preorder(bitree t) {
    Node* Stack[STACK_INIT_SIZE];
    int top = 0;						//创建栈
    Node* p = NULL;				//置空栈
    if (t != NULL) {
        Stack[top++] = t;
        while (top) {
            p = Stack[--top]; printf("%d ", p->data);
            if (p->right != NULL)
                Stack[top++] = p->right;
            if (p->left != NULL)
                Stack[top++] = p->left;
        }
        printf("\n");
    }
}

void _Midorder(bitree t)      //t为根指针
{
    Node* Stack[STACK_INIT_SIZE];//定义指针栈
    int top = 0;                  //置空栈
    do {
        while (t)               //根指针t表示的为非空二叉树
        {
            if (top == STACK_INIT_SIZE) exit(OVERFLOW);//栈已满,退出
            Stack[top++] = t;             //根指针进栈
            t = t->left;             //t移向左子树
        }   //循环结束表示以栈顶元素的指向为根结点的二叉树
        //的左子树遍历结束
        if (top)                    //为非空栈
        {
            t = Stack[--top];             //弹出根指针
            printf("%d ", t->data);    //访问根结点
            t = t->right;             //遍历右子树
        }
    } while (top || t); //父结点未访问，或右子树未遍历
}

void _Postorder(bitree t) {
    Node* Stack[STACK_INIT_SIZE];
    Node* pre = NULL;
    int flag, top = 0;
    if (t != NULL) {
        do {
            while (t != NULL) {
                Stack[top++] = t; t = t->left;
            }
            pre = NULL; flag = 1;
            while (top && flag) {
                t = Stack[top - 1];
                if (t->right == pre) {
                    printf("%d ", t->data); top--;  pre = t;
                }
                else { t = t->right; flag = 0; }
            }
        } while (top);
        printf("\n");
    }
}

void FloorPrint(bitree T)  //层序遍历
{
    bitree temp[100];   //创建pTreeNode指针类型的指针数组
    int in = 0;
    int out = 0;

    temp[in++] = T;  //先保存二叉树根节点

    while (in > out)
    {
        if (temp[out])
        {
            printf("%d ", temp[out]->data);
            temp[in++] = temp[out]->left;
            temp[in++] = temp[out]->right;
        }
        out++;
    }
}

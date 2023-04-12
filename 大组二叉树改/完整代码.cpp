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
ElemType judge() {
    char choose[10];
    int flag = 1;
    int len, i, j, k, n = 0;
    while (flag == 1) {
        cin >> choose;
        len = strlen(choose);
        for (i = 0; i < len; i++) {
            if (choose[i] < '0' || choose[i] > '9') {
                printf("\n输入数据有误（应整数），请重新输入：");
                break;
            }
            else if (i == strlen(choose) - 1)flag = 0;
        }
    }
    for (i = 0, k = 1; i < len; i++) {
        for (j = 0; j < len - 1 - i; j++) {
            k *= 10;
        }
        n += (choose[i] - '0') * k;//将char转化为int类型
        k = 1;
    }
    return n;
}
void operation() {
    system("pause");
    while (getchar() != '\n');
    system("cls");
}
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

void menu() {
    printf("----------1初始化根----------\n");
    printf("----------2判断根是否为空----\n");
    printf("----------3插入节点----------\n");
    printf("----------4删除节点----------\n");
    printf("----------5选择遍历方式------\n");
    printf("----------6退出--------------\n");

}
void menu1() {
    printf("7递归 / 8非递归");
    int c;
    c = judge();
    if (c > 8 || c < 7)printf("\n输入数据有误（请输入7-8），请重新输入：\n");
    switch (c) {
    case 7: {printf("9前序 / 10中序 / 11后序 / 12层序\n");
        c = judge();
        if (c > 12 || c < 9)printf("9前序 / 10中序 / 11后序 / 12层序\n输入数据有误（请输入9-12），请重新输入：\n");
        switch (c) {
        case 9:PreOrder(root); break;
        case 10:MidOrder(root); break;
        case 11:BehOrder(root); break;
        case 12:FloorPrint(root); break;
        }
    }
          break;
    case 8: {printf("13前序 / 14中序 / 15后序\n");
        c = judge();
        if (c > 15 || c < 13)printf("13前序 / 14中序 / 15后序\n输入数据有误（请输入13-15），请重新输入：\n");
        switch (c) {
        case 13:_Preorder(root); break;
        case 14:_Midorder(root); break;
        case 15:_Postorder(root); break;
        }
    }
    }
}
int k, h;
int main()
{
    short option;
    while (1) {
        menu();
        while (1) {
            option = judge();
            if (option > 6 || option < 0)printf("\n输入数据有误（请输入1-6），请重新输入：");
            else break;
        }
        switch (option) {
        case 1: {
            Init(h);
            operation();
            break;
        }
        case 2: {
            if (IsInit(root)) {//判断是否根节点为空
                if (IsEmpty(root))insert(h);
                else printf("\n当前二叉排序树非空，请进行插入操作!\n");
            }
            operation();
            break;
        }
        case 3: {if (IsInit(root)) {
            printf("\n请输入要插入的数据：");
            k = judge();
            insert(k);
        }
              operation();
              break;
        }
        case 4: {
            if (IsInit(root)) {
                printf("\n请输入要删除的数据：");
                k = judge();
                if (search(root, k)) {
                    if (IsEmpty(root))printf("\n该结点为根结点，不能删除根结点！\n\n");
                    else delete_node(root, k); //可以进行删除操作
                }
                else printf("\n该数据不存在！请重新输入要删除的结点!\n");
            }
            operation();
            break;
        }
        case 5: {
            if (IsInit(root)) {
                menu1();
            }
            operation();
            break; }
        case 6: {return 0; }
        }
    }
    return 0;
}
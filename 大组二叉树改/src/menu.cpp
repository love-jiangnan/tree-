void menu() {
    printf("----------1初始化根----------\n");
    printf("----------2判断根是否为空----\n");
    printf("----------3插入节点----------\n");
    printf("----------4删除节点----------\n");
    printf("----------5选择遍历方式------\n");
    printf("----------6退出--------------\n");
}
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
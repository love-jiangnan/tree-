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
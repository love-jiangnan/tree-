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
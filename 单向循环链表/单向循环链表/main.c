//
//  main.c
//  单向循环链表
//
//  Created by 徐鹏飞 on 2020/4/15.
//  Copyright © 2020 徐鹏飞. All rights reserved.
//

#include <stdio.h>
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct Node* LinkList;

/**
 循环链表创建
 1.第一次开始创建 2.已经创建，往里面新增数据
 判断是否第一次创建链表
 YES  -> 创建一个新节点，并使得新节点的next指向自身 (*L) -> next -> (*L);
 NO -> 找链表的尾节点，将尾节点的next = 新节点 ，新节点的next = ()
 
 */

int CreatList(LinkList *L) {
    int item;
    LinkList temp; //新节点
    LinkList target; //尾节点
    
    printf("输入节点的值，输入0结束\n");
    while (1) {
        scanf("%d",&item);
        if (item == 0) {
            break;
        }
        //如果输入的链表是空。则创建一个新的节点，使其next指针指向自己  (*head)->next=*head;
        if (*L == NULL) {
            *L = (LinkList)malloc(sizeof(Node));
            if (!L) {
                exit(0);
            }
            (*L)->data = item;
            (*L)->next = (*L);
        }
        else {
            //输入的链表不是空的，寻找尾节点，使尾节点的 next -> 新节点，新节点的 next -> 头节点(*L)
            for (target = *L; target->next != *L; target = target->next) {
                temp = (LinkList)malloc(sizeof(Node));
                if (!temp) {
                    return 0;
                }
                temp->data = item; //给新创建的节点赋值
                temp->next = *L; //新节点指向头节点
                target->next = temp; //尾节点指向新节点
            }
        }
        return 1;
    }
    
    return 1;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

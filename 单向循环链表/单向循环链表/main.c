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

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node{
    ElemType data;
    struct Node *next;
}Node;



typedef struct Node* LinkList;

/**
 1.循环链表创建
 1.第一次开始创建 2.已经创建，往里面新增数据
 判断是否第一次创建链表
 YES  -> 创建一个新节点，并使得新节点的next指向自身 (*L) -> next -> (*L);
 NO -> 找链表的尾节点，将尾节点的next = 新节点 ，新节点的next = ()
 
 */

Status CreatList(LinkList *L) {
    int item;
    LinkList temp = NULL; //新节点
    LinkList target = NULL; //尾节点
    
    printf("输入节点的值，输入0结束\n");
    while (1) {
        scanf("%d",&item);
        if (item == 0) break;
        //如果输入的链表是空。则创建一个新的节点，使其next指针指向自己  (*head)->next=*head;
        if (*L == NULL) {
            *L = (LinkList)malloc(sizeof(Node));
            if (!L) exit(0);
            (*L)->data = item;
            (*L)->next = (*L);
        }
        else {
            //输入的链表不是空的，寻找尾节点，使尾节点的 next -> 新节点，新节点的 next -> 头节点(*L)
            for (target = *L; target->next != *L; target = target->next);
            temp = (LinkList)malloc(sizeof(Node));
            
            if (!temp) return ERROR;
            
            temp->data = item; //给新创建的节点赋值
            temp->next = *L; //新节点指向头节点
            target->next = temp; //尾节点指向新节点
            
        }
    }
    
    return OK;
}

//2.遍历循环链表（循环链表的遍历最好用do while语句，因为头节点就有值）
void show(LinkList p){
    if (p == NULL) {
        printf("打印的链表为空\n");
        return;
    }else {
        LinkList temp;
        temp = p;//temp指向首节点
        do {
            printf("%5d",temp->data);
            temp = temp->next;
        } while (temp != p);//判断temp是不是指向首节点，是的话就遍历了一圈了
        printf("\n");
    }
}
//3.循环链表插入数据(在循环链表L中位置为place的地方插入数据num)
Status ListInsert(LinkList *L, int place, int num) {
    LinkList temp, target;
    int i;
    if (place == 1) {
        temp = (LinkList)malloc(sizeof(Node));//temp为首元节点
        if (temp == NULL) {
            return ERROR;
        }else {
            temp->data = num;//1.给新节点赋值
            
            for (target = *L; target->next != *L; target = target->next);//2.找到链表最后的节点：尾结点
            
            temp->next = (*L);//3.新结点的next指向头结点
            target->next = temp;//4.尾结点的next指向新结点
            *L = temp;//5.头指针指向新结点temp（临时新结点）
        }
    }else {
        
        temp = (LinkList)malloc(sizeof(Node));//temp为其他位置的结点
        if (temp == NULL) {
            return ERROR;//1.创建新结点temp,并判断是否创建成功,成功则赋值,否则返回ERROR;
        }
        temp->data = num;//2.给新节点赋值
        
        for (target = *L, i = 1; target->next != (*L) && i != place - 1; target = target->next, i++) ;//找到第place-1的结点target
        
        temp->next = target->next;//新结点的next指向插入位置前一个结点（i-1,即为target)的next
        target->next = temp;//插入位置前一个结点（i-1,即为target)的next 指向 新结点temp
        
    }
    
    return OK;
}
//4.循环链表删除元素（删除位置为place的元素）
Status LinkListDelete(LinkList *L, int place){
    LinkList temp, target;
    int i;
    temp = *L;//temp 指向链表首元结点
    if (temp == NULL) return ERROR;
   
    
    if (place == 1) {
        //①.如果删除到只剩下首元结点了，则直接将*L置空；
        if ((*L)->next == (*L)) {
            (*L) = NULL;
            return OK;
        }
        //②.链表还有很多数据，但删除的是首结点；
        for (target = *L; target != *L; target = target->next);//1.找到尾结点
        temp = *L;//保存即将要删除的首结点
        
        (*L) = (*L)->next;//头指针指向首结点的下一个结点
        target->next = (*L);//尾结点指向首结点
        
        free(temp);//释放原来的首结点
        
    }else {
        for (target = *L, i = 1; target->next != *L && i != place -1; i++, target = target->next);//找到位置为place-1的结点（即为要删除的结点的前一个结点）
        
        temp = target->next;//找到要删除的结点
        target->next = temp->next;//要删除的结点的前一个结点 的 next 指向 要删除的结点的next
        free(temp);//释放删除的结点
    }
    
    
    return OK;
}
//5.循环链表查询值
int findValue(LinkList L, int value) {
    int i = 1;
    LinkList p;
    p = L;
    //寻找链表中的结点data = value，当尾结点指向头结点就会跳出循环
    while (p->data != value && p->next != L) {
        i++;
        p = p->next;
    }
    //因为当尾结点指向头结点就会跳出循环，所以要额外增加一次判断尾结点的data = value
    if (p->next == L && p->data != value) {
        return ERROR;
    }

    return i;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    LinkList head;
    int place, num;
    int iStaus;
    
    iStaus = CreatList(&head);
    printf("原始链表：\n");
    show(head);
    
    printf("输入要插入的位置和数据用空格隔开：");
    scanf("%d %d",&place,&num);
    iStaus = ListInsert(&head, place, num);
    show(head);
    
    printf("输入要删除的位置：");
    scanf("%d",&place);
    LinkListDelete(&head, place);
    show(head);
    
    printf("输入你想查找的值:");
    scanf("%d",&num);
    place = findValue(head, num);
    if (place != -1) {
        printf("找到的值的位置是place = %d\n",place);
    }else {
        printf("没找到值\n");
    }
    
    
    return 0;
}

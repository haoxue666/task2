#include "priority_queue.h"

void priority_queue_init(Priority_queue* stk)
{//构造一个空优先队列
    stk->front = (PQNode* )malloc(sizeof(PQNode));
    stk->rear = (PQNode* )malloc(sizeof(PQNode));
    stk->front = stk->rear;
    if(!stk->front){
        exit(0);//储存分配失败
    }
    stk->size = 0;
    stk->front->next = NULL;
}

bool priority_queue_empty(Priority_queue* stk)
{//如果优先队列为空，则返回1，否则返回0
    if(stk->front == stk->rear){
        return 0;
    }
    else{
        return 1;
    }
}

int priority_queue_size(Priority_queue* stk)
{//返回队列中元素的个数   
    return stk->size;
}

void priority_queue_clear(Priority_queue* stk)
{//将优先队列重置为空队列
    while(stk->front){
        stk->rear = stk->front->next;
        free(stk->front);
        stk->front = stk->rear;
    }
}

void priority_queue_push(Priority_queue* stk, PRIORITY_QUEUE_TYPE value)
{//插入新元素
    int flag;
    PQNode* temp;
    PQNode* pre;
    PQNode* cur;
    temp = (PQNode* )malloc(sizeof(PQNode));
    if(!temp){
        exit(0);//储存分配失败
    }
    temp->data = value;
    temp->next = NULL;
    pre = stk->front;
    cur = stk->front->next;
    while(cur->next != NULL){
        pre = cur;
        cur = cur->next;
        if(cur->data < temp->data){
            pre->next = temp;
            temp->next = cur;
            stk->size ++;
            flag = 1;
            break;
        }
    }
    if(flag = 0){
        stk->rear->next = temp;
        stk->rear = temp;
    }
}

void priority_queue_pop(Priority_queue* stk)
{//如果优先队列不空，则删除对头元素
    PQNode* temp;
    if(priority_queue_empty(stk)){
        ;
    }
    else{
        temp = stk->front->next;
        stk->front->next = temp->next;
        if(stk->rear ==temp){
            stk->rear = stk->front;
        }
        stk->size --;
        free(temp);
    }
}

PRIORITY_QUEUE_TYPE priority_queue_top(Priority_queue* stk)
{//如果优先队列不空，则或得队头元素
    if(priority_queue_empty(stk)){
        return 0;
    }
    return (stk->front->next->data);
}

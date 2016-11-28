#include"queue.h"

void queue_init(Queue* que)
{//构造一个空队列
   que->front = (QNode* )malloc(sizeof(QNode));
   que->rear = (QNode* )malloc(sizeof(QNode));
   que->front = que->rear;
   if(!que->front){
        exit(0);//储存分配失败
   }
   que->front->next = NULL;
}

bool queue_empty(Queue* que)
{//如果队列为空队列，则返回1，否则返回0
   if(que->front == que->rear){
        return 1;
   }
   else{
        return 0;
   }
}

int queue_size(Queue* que)
{//返回队列中元素的个数
    QNode* temp;
    int n = 0;
    if(que->front == que->rear){
        return 0;
    }
    temp = que->front;
    while(temp != que->front){
        temp = temp->next;
        n ++;
    }
}
   
void queue_clear(Queue* que)
{//将队列重置为空队列
   while(que->front){
        que->rear = que->front->next;
        free(que->front);
        que->front = que->rear;
   } 
}
    
void queue_push(Queue* que, QUEUE_TYPE value)
{//插入新元素为新的队尾
    QNode* temp;
    temp = (QNode* )malloc(sizeof(QNode));
    if(!temp){
        exit(0);//储存分配失败
    }
    temp->data = value;
    temp->next = NULL;
    que->rear->next = temp;
    que->rear = temp;
}

void queue_pop(Queue* que)
{//如果队列不空，则删除队头元素
    QNode* temp;
    if(que->front == que->rear){
        ;
    }
    else{    
        temp = que->front->next;
        que->front->next = temp->next;
        if(que->rear == temp){
            que->rear == que->front;
        }
        free(temp);
    }
}

QUEUE_TYPE queue_top(Queue* que)
{//如果队列不空，则获得队头元素
    if(que->front == que->rear){
        return 0; 
    }
    return (que->front->next->data);
}

#include"list.h"

LIST_TYPE* list_ptr_at(List* lis)
{//返回线性表指针所指元素
    
}

bool list_empty(List* lis)
{//如果线性表为空表，则返回1，否则返回0
    if(lis->head == lis->tail){
        return 1;
    }
    else{
        return 0;
    }
}

int list_size(List* lis)
{//返回线性表中元素的个数
    return lis->len;    
}

void list_init(List* lis)
{//构造一个空线性表
    lis->head = (LNode* )malloc(sizeof(LNode));
    lis->tail = (LNode* )malloc(sizeof(LNode));
    lis->head = lis->tail;
    if(!lis->head){
        exit(0);//储存分配失败
    }
    lis->head->prior = NULL;
    lis->head->next = NULL;
    lis->len = 0;
}

void list_clear(List* lis)
{//将线性表重置为空表
    while(lis->head){
        lis->tail = lis->head->next;
        free(lis->head);
        lis->head = lis->tail;
        lis->len --;
    }
}

void list_insert(List* lis, ListIterator where, LIST_TYPE value)
{//在线性表的where位置插入新元素
    if(where.position > lis->len || where.position < 1){
        return;
    }
    LNode* temp;
    LNode* current;
    current = lis->head->next;
    temp = (LNode* )malloc(sizeof(LNode));
    temp->data = value;
    ListIterator* Lit;
    Lit->current = lis->head->next;
    Lit->position = 1;
    while(ListIterator_not_equal(where,*Lit)){
        current = current->next;
        ListIterator_self_increase(Lit);
    }
    current->prior->next = temp;
    temp->prior = current->prior;
    temp->next = current;
    current->prior = temp;
    lis->len ++;
}

void list_erase(List* lis, ListIterator where)
{//删除线性表where位置的元素
    if(where.position > lis->len || where.position < 1){
        return;
    }
    LNode* temp;
    temp = lis->head->next;
    ListIterator* Lit;
    Lit->current = lis->head->next;
    Lit->position = 1;
    while(ListIterator_not_equal(where,*Lit)){
        temp = temp->next;
        ListIterator_self_increase(Lit);
    }
    temp->prior->next = temp->next;
    temp->next->prior = temp->prior;
    free(temp);
    lis->len --;
    
}

void list_push_back(List* lis, LIST_TYPE value)
{//在线性表尾插入新的元素
    LNode* temp;
    temp = (LNode* )malloc(sizeof(LNode));
    if(!temp){
        exit(0);//储存分配失败
    }
    temp->data = value;
    temp->prior = lis->tail;
    temp->next = NULL;
    lis->tail->next = temp;
    lis->tail = temp;
    lis->len ++;
}

void list_pop_back(List* lis)
{//如果线性表不空，则删除表尾元素
    LNode* temp;
    if(lis->head == lis->tail)
    {
        ;
    }
    else{
        temp = lis->tail;
        lis->tail = temp->prior;
        lis->tail->next = NULL;
        free(temp);
    }
    lis->len --;
}

void list_push_front(List* lis, LIST_TYPE value)
{//在线性表头插入新元素
    LNode* temp;
    temp = (LNode* )malloc(sizeof(LNode));
    if(!temp){
        exit(0);//储存分配失败
    }
    temp->data = value;
    temp->prior = lis->head;
    temp->next = lis->head->next;
    lis->head->next = temp;
    lis->len ++;
}

void list_pop_front(List* lis)
{//如果线性表不空，则删除表头元素
    LNode* temp;
    if(lis->head == lis->tail)
    {
        ;
    }
    else{
        temp = lis->head->next;
        lis->head->next = temp->next;
        temp->next->prior = lis->head;
        free(temp);
    }
    lis->len --;
}

ListIterator list_begin(List* lis)
{//返回线性表头的迭代器
    ListIterator temp;
    temp.current = lis->head->next;
    temp.position = 1;
    return temp;
}

ListIterator list_end(List* lis)
{//返回线性表尾的迭代器
    ListIterator temp;
    temp.current = lis->tail;
    temp.position = lis->len;
    return temp;
}

void ListIterator_self_increase(ListIterator* pIter)
{//迭代器自增
    pIter->current = pIter->current->next;
    pIter->position ++;
}

void ListIterator_self_decrease(ListIterator* pIter)
{//迭代器自减
    pIter->current = pIter->current->prior;
    pIter->position --;
}

bool ListIterator_equal(ListIterator iter_a, ListIterator iter_b)
{//比较两个迭代器是否相等，相等返回1，否则返回O
    if(iter_a.current == iter_b.current && iter_a.position == iter_b.position){
        return 1;
    }
    else{
        return 0;
    }
}

bool ListIterator_not_equal(ListIterator iter_a, ListIterator iter_b)
{//比较两个迭代器是否不相等，不相等返回1，否则返回O
    if(iter_a.current != iter_b.current || iter_a.position != iter_b.position){
        return 1;
    }
    else{
        return 0;
    }

}

LIST_TYPE* list_get_data_ptr(ListIterator* iter)
{//返回迭代器所指元素
    return &(iter->current->data);
}

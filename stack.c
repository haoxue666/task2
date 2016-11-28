#include "stack.h"
#define STACK_INIT_SIZE 100 //储存空间初始分配量
#define STACKINCREMENT 10 //储存空间分配增量
void stack_init(Stack* stk)
{//构造一个空栈stk
    stk->base = (STACK_TYPE* )malloc(STACK_INIT_SIZE * sizeof(STACK_TYPE));
    if(!stk->base){
        exit(0);//储存分配失败
    }
    else{
        stk->top =stk->base;
        stk->stacksize = STACK_INIT_SIZE;
    }
    printf("Init stack successfully!\n");
}

bool stack_empty(Stack* stk)
{//如果栈为空栈，则返回1，否则返回0
   if(stk->top == stk->base){
        return 0;  
   }
   else{
        return 1;
   }
}

int stack_size(Stack* stk)
{//返回栈中元素的个数
    int n = 0;
    if(stk->top == stk->base){
        return 0;
    }
    STACK_TYPE* ptr;
    ptr = stk->top;
    while(ptr != stk->base)
    {
        *(ptr --);
        n ++;
    }
    return n;
}

void stack_clear(Stack* stk)
{//将栈清空
    if(stk->top == stk->base){
        printf("Stack is null,no need to clear.\n");
    }
    else{
        free(stk->base);
    }
}

void stack_push(Stack* stk, STACK_TYPE value)
{//插入新元素为新的栈顶元素
    if((stk->top - stk->base) >= stk->stacksize){
        stk->base = (STACK_TYPE* )realloc(stk->base,(stk->stacksize + STACKINCREMENT) * sizeof(STACK_TYPE));//栈满，追加储存空间

        if(!stk->base){
            exit(0);
        }
        stk->top = stk->base + stk->stacksize;
        stk->stacksize += STACKINCREMENT;
    }
    *(stk->top++) = value;
}

void stack_pop(Stack* stk)
{//如果栈不空，则删除栈顶元素
    if(stk->top == stk->base){
        printf("Stack is null,no need to pop\n");
    }
    else{
        *(stk->top --);
    }
}

STACK_TYPE stack_top(Stack* stk)
{//如果栈不空，则返回栈顶元素，否则返回0
    if(stk->top == stk->base){
        return 0;
    }
    else{
        return *(stk->top-1);
    }
}

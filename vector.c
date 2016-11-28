#include "vector.h"

#define VECTOR_INIT_SIZE 10
#define VECTORINCREMENT 2
void vector_init(Vector* vec)
{//初始化一个向量
    vec->base = (VECTOR_TYPE* )malloc(VECTOR_INIT_SIZE*sizeof(VECTOR_TYPE));
    if(!vec->base){
        exit(0);
    }
    vec->len = 0;
    vec->size = VECTOR_INIT_SIZE;
}

void vector_clear(Vector* vec)
{//清空向量
    if(!vec->base){
        return;
    }
    free(vec->base);
    vec->base = NULL;
}

VECTOR_TYPE* vector_ptr_at(Vector* vec)
{//返回指针所指元素
    return vec->base;
}

bool vector_empty(Vector* vec)
{//如果向量为空，则返回1，否则返回0
   if(vec->len == 0){
        return 1;
   }
   else{
        return 0;
   }
}

int vector_size(Vector* vec)
{
   return vec->len;
}

int vector_capacity(Vector* vec)
{
   return vec->size;
}

void vector_reserve(Vector* vec, int new_cap)
{//设置容量为new_cap
    VECTOR_TYPE* newbase;
    if(new_cap == vec->size){
        ;
    }
    else if(new_cap > vec->size || (new_cap < vec->size && new_cap >= vec->len)){
        newbase = (VECTOR_TYPE* )realloc(vec->base,new_cap*sizeof(VECTOR_TYPE));
        vec->base = newbase;
        vec->size = new_cap; 
    }
    else{
        VECTOR_TYPE* p;
        VECTOR_TYPE* q;
        q = &(vec->base[new_cap-1]);//q为插入位置
        for(p = &(vec->base[vec->len-1]); p >= q; --p){
            free(p);
        }
        newbase = (VECTOR_TYPE* )realloc(vec->base,new_cap*sizeof(VECTOR_TYPE));
        vec->base = newbase;
        vec->size = new_cap;  
    }
}

void vector_resize(Vector* vec, int new_size)
{//设置元素数量为new_size
   if(new_size == vec->len){
        ;
   }
   else if(new_size > vec->size){
        VECTOR_TYPE* newbase;
        newbase = (VECTOR_TYPE* )realloc(vec->base,new_size*sizeof(VECTOR_TYPE));
        vec->base = newbase;
        vec->size = new_size;
        vec->len = new_size;
   }
   else if(new_size > vec->len)
   {
       vec->len = new_size; 
   }
   else{
        VECTOR_TYPE* p;
        VECTOR_TYPE* q;
        q = &(vec->base[new_size-1]);//q为插入位置
        for(p = &(vec->base[vec->len-1]); p >= q; --p){
            free(p);
        }
        vec->len = new_size;  
   }
}

void vector_shrink_to_fit(Vector* vec)
{//将向量的容量更改为向量的长度大小
        VECTOR_TYPE* newbase;
        newbase = (VECTOR_TYPE* )realloc(vec->base,vec->len*sizeof(VECTOR_TYPE));
        vec->base = newbase;
        vec->size = vec->len;
}

void vector_insert(Vector* vec, int where, VECTOR_TYPE value)
{//在向量where位置之前插入新元素
    VECTOR_TYPE* p;
    VECTOR_TYPE* q;
    if(where < 1 || where > vec->len + 1){
        return;
    }
    if(vec->len >= vec->size){
        VECTOR_TYPE* newbase;
        newbase = (VECTOR_TYPE* )realloc(vec->base,(VECTOR_INIT_SIZE+VECTORINCREMENT)*sizeof(VECTOR_TYPE));
        vec->base = newbase;
        vec->size += VECTORINCREMENT; 
    }
    q = &(vec->base[where-1]);//q为插入位置
    for(p = &(vec->base[vec->len-1]); p >= q; --p){
        *(p+1) = *p;
    }
    *q = value;
    vec->len ++;
}

void vector_erase(Vector* vec, int where)
{//删除向量中第i个元素
    VECTOR_TYPE* p;
    VECTOR_TYPE* q;
    if(where < 1 || where > vec->len + 1){
        return;
    }
    p = &(vec->base[where-1]);
    q = vec->base + where - 1;//q为插入位置
    for(++p; p<=q; ++p){
        *(p-1) = *p;
    }
    vec->len --;    
}
//以下两个函数与插入删除较为相似，便不再赘述
void vector_push_back(Vector* vec, VECTOR_TYPE value)
{//在向量尾插入一个新元素
    
}

void vector_pop_back(Vector* vec)
{//向在向量尾删除一个元素
    
}

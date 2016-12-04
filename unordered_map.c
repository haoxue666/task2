#include "unordered_map.h"

#define HASH_INIT_SIZE 8

bool unordered_map_empty(Unordered_map* st)
{
    if(st->size == 0){
        return 0;
    }
    else{
        return 1;
    }
}

int unordered_map_size(Unordered_map* st)
{
    return (st->count);
}

void unordered_map_init(Unordered_map* st)
{
    st->hash_node = (HNode* )malloc(HASH_INIT_SIZE * sizeof(HNode));
    if(!st->hash_node)
    {
        exit(0);
    }
    st->size = HASH_INIT_SIZE;
    st->count = 0;
}

void unordered_map_clear(Unordered_map* st)
{
    HNode* cur = NULL;
    HNode* tmp = NULL;
    for(int i=0;i<st->size;++i)
    {
        cur = st->hash_node;
        while(cur->next)
        {
            tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(st->hash_node);
    return;
}

static int hashcode(long long key)
{
    key=(~key) + (key<<18);
    key=key ^ (key>>31);
    key=key * 21;
    key=key ^ (key>>11);
    key=key + (key<<6);
    key=key ^ (key>>22);
    return (int)key;
}


void unordered_map_insert(Unordered_map* st,UNORDERED_MAP_KEY key,UNORDERED_MAP_TYPE value)
{
    if(st->size * 0.75 < st->count){
        unordered_map_resize(st);
    }
    int index = hashcode(key);
    index=(index % st->size + st->size) % st->size;
    HNode *old_hash_node=st->hash_node;
    HNode *cur=old_hash_node;
    while(cur)
    {
        if(key == cur->key)
        {
            cur->data = value;
            return;
        }
        cur = cur->next;
    }
    HNode *new_node = (HNode*)malloc(sizeof(HNode));
    new_node->key = key;
    new_node->data = value;
    new_node->next = NULL;
    st->count += 1;
    if(old_hash_node != NULL)
        new_node->next = old_hash_node;
    st->hash_node = new_node;
    return;
}

void unordered_map_erase(Unordered_map* st,UNORDERED_MAP_KEY key)
{
    int index=hashcode(key);
    index=(index%st->size+st->size)%st->size;
    HNode* cur = st->hash_node;
    HNode* last = NULL;
    while(cur != NULL)
    {
        if(cur == NULL){
            return;
        }
        if(cur->key == key)
        {
            if(last == NULL){
                st->hash_node = cur->next;
            }
            else{
                last->next = cur->next;
            }
            free(cur);
            return;
        }
        last = cur;
        cur = cur->next;
    }
}

static void unordered_map_resize(Unordered_map* st)
{
    int old_size = st->size;
    st->size *= 2;
    st->count = 0;
    HNode* old_hash_node=st->hash_node;
    st->hash_node = (HNode* )calloc(st->size,sizeof(HNode*));
    for(int i = 0;i < old_size; ++i)
    {
        HNode* cur = old_hash_node;
        HNode* record;
        while(cur != NULL)
        {
            unordered_map_insert(st,cur->key,cur->data);
            record = cur;
            cur = cur->next;
            free(record);
        }
    }
    free(old_hash_node);
}

UNORDERED_MAP_TYPE* unordered_map_ptr_at(Unordered_map* st,UNORDERED_MAP_KEY key)
{
    int index = hashcode(key);
    index = (index % st->size + st->size) % st->size;
    HNode* cur = st->hash_node;
    if(cur == NULL)
        return NULL;
    while(cur != NULL)
    {
        if(cur->key == key)
            return &cur->data;
        cur = cur->next;
    }
    return NULL;
}

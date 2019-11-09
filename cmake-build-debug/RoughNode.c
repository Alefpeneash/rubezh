#include <pthread.h>
//#include "../../../../../usr/include/zconf.h"
//#include "../../../../../usr/include/pthread.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct RoughNode
{
    int key;
    int value;
    struct RoughNode* next;

} RoughNode;

typedef struct
{
    RoughNode* root;

} RoughList;

typedef struct
{
    int value;
    char exist;
} FindResult;

FindResult find(RoughList* list, int key)
{
    pthread_mutex_lock(&lock);

    RoughNode* tmpnode = list->root;
    FindResult* tmpval;
    tmpval->exist=0;
    tmpval->value=NULL;
    while(tmpnode->next && tmpnode->key )
    {
        tmpval->exist = 0;
        tmpnode = tmpnode->next;
        tmpval->value = tmpnode->value;
        tmpval->exist = 1;
    }
    pthread_mutex_unlock(&lock);
    return *tmpval;
}

char insert(RoughList* list, int key, int value)
{
    pthread_mutex_lock(&lock);

    RoughNode* newnode = (struct RoughNode*)malloc(sizeof(struct RoughNode));


    RoughNode* tmpnode = list->root;

    while(tmpnode->next)
    {
        if(tmpnode->key == key)
        {
            return 0;
        }

        tmpnode = tmpnode->next;
    }

    tmpnode->next = newnode;

    pthread_mutex_unlock(&lock);

    return 1;
}

char removenode(RoughList* list, int key)
{
    pthread_mutex_lock(&lock);

    RoughNode* tmpnode = list->root;
    RoughNode* prevnode = list->root;
    while(tmpnode->next && tmpnode->key!=key)
    {
        prevnode = tmpnode;
        tmpnode = tmpnode->next;
        prevnode->next = tmpnode->next;
    }

    pthread_mutex_unlock(&lock);
    return 0;
}

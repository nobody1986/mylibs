#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mymalloc.h"
#include "hash.h"
#include "btree.h"

HNode **initHNode() {
    HNode **root = (HNode **) mymalloc(sizeof (HNode*) * Hash_Size);
    return root;
}

void releaseHNode(HNode **root) {
    long hash_long = 0;
    HNode *tmp = NULL;
    HNode *tmp_tmp = NULL;
    for (hash_long = 0; hash_long < Hash_Size; ++hash_long) {
        tmp = *(root + hash_long);
        while (tmp != NULL) {
            tmp_tmp = tmp;
            tmp = tmp->next;
            myfree(tmp_tmp);
        }
    }
    myfree(root);
}

inline HNode* newHNode(unsigned char *s) {
    HNode *newNode = mymalloc(sizeof (HNode));
    newNode->data = NULL;
    newNode->next = NULL;
    newNode->sting = s;
    return newNode;
}

long hash(unsigned char *key) {
    int i = 0;
    int len = strlen(key);
    long hash = 0;
    for (i = 0; i < len; ++i) {
        hash += 33 * (hash + key[i]) + i;
    }
    return hash % Hash_Size;
}

void* findFromHash(HNode **root, unsigned char *key) {
    long hash_long = hash(key);
    HNode *tmp = *(root + hash_long);
    //printf("p:%p\n",tmp);
    if (tmp == NULL) {
        return NULL;
    }
    while (tmp != NULL) {
        if (strcmp(tmp->sting, key) == 0) {
            return tmp->data;
        }
        tmp = tmp->next;
    }
    return NULL;
}

HNode* setToHash(HNode **root, unsigned char *key, void *value) {
    long hash_long = hash(key);
    HNode *tmp = *(root + hash_long);
    if (tmp == NULL) {
        //printf("p1:%p\n",tmp);
        tmp = newHNode(key);
        tmp->data = value;
        tmp->sting = key;
        *(root + hash_long) = tmp;
        return tmp;
    }
    while (tmp != NULL) {
        if (strcmp(tmp->sting, key) == 0) {
            tmp->data = value;
            return tmp;
        }
        if (tmp->next == NULL) {
            tmp->next = newHNode(key);
            tmp->next->data = value;
            tmp->next->sting = key;
            return tmp->next;
        }
        tmp = tmp->next;
    }
}
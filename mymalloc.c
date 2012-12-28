#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include <string.h>
#include "mymalloc.h"


int malloc_size[10] = {16, 64, 128, 256, 512, 1024, 2048, 3072, 4096, 1048568};
mem_block *root = NULL;

void init() {
    root = (mem_block*) malloc(sizeof (mem_block));
    root->block = (unsigned char*) malloc(MEM_BLOCK_SIZE);
    root->fitSize = 16;
    root->size = root->fitSize + sizeof (int) * 2;
    root->block_count = MEM_BLOCK_SIZE / root->size;
    root->free = root->block_count;
    root->block_used = (unsigned char*) malloc(sizeof (unsigned char) * root->block_count);
    root->used = 0;
    root->next = NULL;
    root->prev = NULL;
}

inline int isFull(mem_block* m) {
    return m->free == 0 ? 1 : 0;
}

inline int isUsed(int i, mem_block* m) {
    return *(m->block_used + i) == 1;
}

inline void useBlock(int i, mem_block* m) {
    *(m->block_used + i ) = 1;
}

inline void freeBlock(int i, mem_block* m) {
    *(m->block_used + i ) = 0;
}

inline void* getBlock(int i, mem_block* m) {
    return (void*) (m->block+ i * m->size / sizeof (unsigned char));
}

void destroy() {
    if (root == NULL) {
        return;
    }
    mem_block* tmp = root;
    while (tmp->next != NULL) {
        if (tmp->prev != NULL) {
            free(tmp->prev->block);
            free(tmp->prev->block_used);
            free(tmp->prev);
        }
        tmp = tmp->next;
    }
    free(tmp);
    free(tmp->block);
    free(tmp->block_used);
}

inline int getFitSize(int size) {
    int i = 0;
    for (i = 0; i < 10; ++i) {
        if (malloc_size[i] >= size) {
            return malloc_size[i];
        }
    }
    return -1;
}

mem_block* createNewBlock(int fitSize) {
    mem_block *tmp = root;
    mem_block *newBlock = (mem_block*) malloc(sizeof (mem_block));
    newBlock->block = (unsigned char*) malloc(MEM_BLOCK_SIZE);
    //printf("start %p\n",newBlock->block);
    newBlock->fitSize = fitSize;
    newBlock->size = newBlock->fitSize + sizeof (int) * 2;
    newBlock->block_count = MEM_BLOCK_SIZE / newBlock->size;
    newBlock->free = newBlock->block_count;
    newBlock->block_used = (unsigned char*) malloc(sizeof (unsigned char) * newBlock->block_count);
    newBlock->used = 0;
    newBlock->next = NULL;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    newBlock->prev = tmp;
    tmp->next = newBlock;
    return newBlock;
}

void* mymalloc(size_t size) {
    if (root == NULL) {
        init();
    }
    int fitSize = getFitSize(size);
    mem_block* tmp = root;
    int* p_fitSize = NULL;
    int i = 0;
    if (fitSize == -1) {
        return NULL;
    }
    while (tmp != NULL) {
        if (tmp->fitSize == fitSize && !isFull(tmp)) {
            for (i = 0; i < tmp->block_count; ++i) {
                if (!isUsed(i, tmp)) {
                    tmp->used += 1;
                    tmp->free -= 1;
                    useBlock(i, tmp);
                    p_fitSize = (int*) getBlock(i, tmp);
                    //printf("getBlock %p\n",p_fitSize);
                    *p_fitSize = tmp->fitSize;
                    *(p_fitSize + 1) = i;
                    //memset(p_fitSize ,0,size);
                    *(p_fitSize + size/sizeof(int)) = 0;
                    return (void*) (p_fitSize + 2);
                }
            }
        }
        tmp = tmp->next;
    }
    tmp = createNewBlock(fitSize);
    tmp->used += 1;
    tmp->free -= 1;
    useBlock(0, tmp);
    p_fitSize = (int*) getBlock(0, tmp);
    *p_fitSize = tmp->fitSize;
    *(p_fitSize + 1) = 0;
    //memset(p_fitSize ,0,size);
   // printf("getBlock %p\n",p_fitSize);
    *(p_fitSize + size/sizeof(int)) = 0;
    return (void*) (p_fitSize + 2);
}

void myfree(void* p) {
    if (root == NULL) {
        return;
    }
    int* p2t = (int*) p;
    int* p_fitSize = p2t - 2;
    int fitSize = *p_fitSize;
    int position = *(p_fitSize + 1);
    mem_block* tmp = root;
    //printf("%d %d %p %p\n",fitSize,position,p,p_fitSize);
    while (tmp != NULL) {
        if (tmp->fitSize == fitSize) {
            if (p_fitSize == getBlock(position, tmp)) {
                tmp->used -= 1;
                tmp->free += 1;
                freeBlock(position, tmp);
                break;
            }
        }
        tmp = tmp->next;
    }
}

void print_used() {
    if (root == NULL) {
        init();
    }
    mem_block* tmp = root;
    int i = 0;
    while (tmp != NULL) {
        printf("block %d: fitSize: %d , used: %d , free: %d\n", i, tmp->fitSize, tmp->used, tmp->free);
        tmp = tmp->next;
        ++i;
    }
}
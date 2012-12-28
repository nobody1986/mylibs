/* 
 * File:   mymalloc.h
 * Author: mo
 *
 * Created on 2011年12月8日, 下午11:23
 */

#ifndef MYMALLOC_H
#define	MYMALLOC_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MEM_BLOCK_SIZE 1024 * 1024  * 2

typedef struct  mb{
    unsigned char* block;
    int size;
    int fitSize;
    int block_count;
    struct  mb *prev;
    struct  mb *next;
    int free;
    int used;
    unsigned char* block_used;
}  mem_block;


void* mymalloc(size_t); 
void myfree(void*); 
void destroy();
void print_used();

#ifdef	__cplusplus
}
#endif

#endif	/* MYMALLOC_H */



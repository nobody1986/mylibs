/* 
 * File:   hash.h
 * Author: mo
 *
 * Created on 2011年12月14日, 下午11:49
 */

#ifndef HASH_H
#define	HASH_H

#ifdef	__cplusplus
extern "C" {
#endif

#define Hash_Size 4999

typedef struct HashNode{
    void* data;
    unsigned char *sting;
    struct HashNode *next;
} HNode;

typedef HNode** HMap;
HNode** initHNode();
void* findFromHash(HNode **root,unsigned char *key);
HNode* setToHash(HNode **root,unsigned char *key,void *value);
void releaseHNode(HNode **root);


#ifdef	__cplusplus
}
#endif

#endif	/* HASH_H */


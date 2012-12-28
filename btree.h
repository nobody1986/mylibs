/* 
 * File:   btree.h
 * Author: mo
 *
 * Created on 2011年12月13日, 下午9:55
 */

#ifndef BTREE_H
#define	BTREE_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct treeNode{
    void *data;
    struct treeNode* children[255] ;
} node;

node*  newNode();
node* addToTree(node* root,unsigned char *s,void* data);
void *findFromTree(node* root ,unsigned char *s);


#ifdef	__cplusplus
}
#endif

#endif	/* BTREE_H */


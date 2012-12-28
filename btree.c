#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mymalloc.h"
#include "btree.h"

inline node*  newNode(){
    node* newNode = (node*)mymalloc(sizeof(node));
    int i =0;
    newNode->data = NULL;
    //newNode->children ;
    for(i = 0 ;i < 255;++i){
        newNode->children[i] = NULL;
    }
    return newNode;
}

node* addToTree(node* root,unsigned char *s,void* data){
    int slen = strlen(s);
    int i = 0;
    node* tmp = root;
    node* tmp_tmp = root;
    int n = 0;
    for(i = 0;i < slen;++i){
        n = *(s + i);
        tmp_tmp = tmp->children[n];
        if(tmp_tmp == NULL){
            tmp_tmp = newNode();
            tmp->children[n] = tmp_tmp;
        }
        tmp = tmp_tmp;
    }
    tmp->data = data;
    return tmp;
}

void *findFromTree(node* root ,unsigned char *s){
    int slen = strlen(s);
    int i = 0;
    node* tmp = root;
    node* tmp_tmp = root;
    int n = 0;
    for(i = 0;i < slen;++i){
        n = *(s + i);
        tmp_tmp = tmp->children[n];
        if(tmp_tmp == NULL){
            return NULL;
        }
        tmp = tmp_tmp;
    }
    return tmp->data;
}
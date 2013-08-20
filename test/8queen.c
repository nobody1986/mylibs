/* 
 * File:   8queen.c
 * Author: Administrator
 *
 * Created on 2013年8月20日, 下午9:06
 */

#include <stdio.h>
#include <stdlib.h>
#include <mymalloc.h>
#include <btree.h>
#include <hash.h>
#include <stack.h>

typedef struct {
    int width;
    int height;
    unsigned char *place;
    Stack *step;
} World;

World *createWorld(int width,int height){
    World *w = (World*)mymalloc(sizeof(World));
    w->place = (unsigned char*)mymalloc(sizeof(unsigned char) * width * height);
    w->width = width;
    w->height = height;
    w->step = initStack();
    return w;
}

void try(World *w ,int x , int y){
    if(x == w->width || y == w->height){
        return;
    }
    
}


/*
 * 
 */
int main(int argc, char** argv) {
    
    return (EXIT_SUCCESS);
}


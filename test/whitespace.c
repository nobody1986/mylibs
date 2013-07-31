/* 
 * File:   whitespace.c
 * Author: Administrator
 *
 * Created on 2013年7月30日, 下午12:01
 */

#include <stdio.h>
#include <stdlib.h>
#include <mymalloc.h>
#include <btree.h>
#include <hash.h>


#define LF '\n'
#define SPACE ' '
#define TAB '\t'
/*
 * 
 */
int main(int argc, char** argv) {
int* pi= NULL;
char* s = NULL;
print_used();
pi = mymalloc(sizeof(int));
print_used();
myfree(pi);
HNode** root = initHNode();
//node* root = newNode();
printf("%d\n",sizeof(HNode));
int i = 0;
print_used();
for(i=0;i<5000;++i){
s = (char*)mymalloc(sizeof(char) * i * 2);
myfree(s);
    /*
        addToTree(root,"hello","xxxxsaasd");
        findFromTree(root,"hello");
        addToTree(root,"asdadadssadasd","xsadsadxxxsaasd");
        printf(findFromTree(root,"asdadadssadasd"));*/
setToHash(root,"hello","Hello word!");
 //printf("%s\n",findFromHash(root,"hello"));
}
print_used(); 
destroy();
return (EXIT_SUCCESS);
}



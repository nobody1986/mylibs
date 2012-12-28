/* 
 * File:   var.h
 * Author: mo
 *
 * Created on 2011年12月13日, 下午9:58
 */

#ifndef VAR_H
#define	VAR_H

#ifdef	__cplusplus
extern "C" {
#endif



enum ValType{
    FLOAT,
    INT,
    CHAR,
    STRING,
    POINT
};
enum FuncType{
    USERDEFINE,
    NATIVE
};

typedef struct varia{
    enum ValType type;
    union value {
        float valFloat;
        int valInt;
        char valChar;
        char *valString;
        void *valPoint;
    };
} Var;

typedef struct function{
    enum FuncType type;
    int argc;
    void* argv;
    void* local;
    void* body;
} Func;

#ifdef	__cplusplus
}
#endif

#endif	/* VAR_H */

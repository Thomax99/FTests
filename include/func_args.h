#ifndef FUNCARGS

    #define  FUNCARGS 1

    #define INTTYPE 1
    #define FLOATTYPE 2
    #define STRINGTYPE 3

    #include "ftests_structures.h"

    ftests_function_t * ftests_function_initializer(char * name, char * retValue, char * returnType) ;
    void ftests_function_free(ftests_function_t * func) ;

    void getFunctionReturnType(char * dst, ftests_function_t * func) ;
    char *  getFunctionTest(ftests_function_t * func) ;
    void ftests_function_make_arguments(ftests_function_t * func, char ** args, int nb_args) ;
#endif
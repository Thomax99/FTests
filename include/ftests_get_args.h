#ifndef FTESTARGSH

    #define  FTESTARGSH 1

    #define INTTYPE 1
    #define FLOATTYPE 2
    #define STRINGTYPE 3

    #include "main.h"

    ftests_args_t * alloc_args() ;

    void free_args(ftests_args_t * args) ;
    void get_args(ftests_args_t * args, int argc, char ** argv) ;

#endif
#ifndef FTESTARGSH

    #define  FTESTARGSH 1

    #include "main.h"

    ftests_args_t * alloc_args() ;

    void free_args(ftests_args_t * args) ;
    void get_args(ftests_args_t * args, int argc, char ** argv) ;

#endif
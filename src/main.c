#include <stdio.h>
#include "ftests_get_args.h"
#include "tests.h"
#include "main.h"



int main(int argc, char * argv[]) {
    ftests_args_t * args =  alloc_args() ;

    get_args(args, argc, argv) ;

    int ret = ftests_test_main(args) ;

    switch (ret){
        case WELLTERMINATEDRETURN :
            fprintf(stderr, "[SUCCESS]\n") ;
            break ;
        case TIMEOUTRETURN :
            fprintf(stderr, "[TIMEOUT ERROR]\n") ;
            break ;
        case SIGNALRETURN :
            fprintf(stderr, "[EXCEPTION ERROR]\n") ;
            break ;
        case ANORMALCODERETURN :
            fprintf(stderr, "[ANORMAL RETURN ERROR]\n") ;
            break ;
        case OUTPUTPROBLEMRETURN :
            fprintf(stderr, "[OUTPUT ERROR]\n") ;
            break ;
        case COMPILATIONERRORRETURN :
            fprintf(stderr, "[COMPILATION ERROR]\n") ;
            break ;
        case ANORMALFUNCTIONRETURNERROR :
            fprintf(stderr, "[FUNCTION RETURN ERROR]\n") ;
            break ;
        default :
            fprintf(stderr, "ERROR\n") ;
            break ;
    }

    free_args(args) ;
    return 0 ;
}
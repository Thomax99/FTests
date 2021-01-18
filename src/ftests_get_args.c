
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "utilitaries.h"

ftests_args_t * alloc_args(){
    ftests_args_t * args = malloc(sizeof(ftests_args_t)) ;
    if (args == NULL){
        fprintf(stderr, "error allocating options. Crash out.") ;
        exit(1) ;
    }
    return args ;
}

void free_args(ftests_args_t * args){
    if (args == NULL){
        //maybe an error
        fprintf(stderr, "error : you try to free a null arg") ;
        return ;
    }
    free(args) ;
}

void get_args(ftests_args_t * args, int argc, char ** argv){
    //recup of first arg
    if (argc < 2){
        fprintf(stderr, "need a program name\n") ;
        usage() ;
        exit(1) ;
    }
    args->programName = argv[1] ;
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "--timeEnabled") == 0){
            //we have a time value
            args->testTimeRequired = 1 ;
            if (i+1 >= argc){
                //error
                fprintf(stderr, "you have to give a time after enabling the time\n") ;
                usage() ;
                exit(1) ;
            }
            char * endPtr ;
            long time = strtol(argv[i+1], &endPtr, 10) ;
            if (*endPtr != '\0'){
                fprintf(stderr, "the time has to be valid : %s is not valid\n", argv[i+1]) ;
                usage() ;
                exit(1) ;
            }
            args->maxTimeRequired = time ;
        }
        else if (strcmp(argv[i], "--enableReturnCode") == 0){
            args->testReturnCodeRequired = 1 ;
            if (i+1 >= argc){
                //error
                fprintf(stderr, "you have to give a return code after enabling the test of return code\n") ;
                usage() ;
                exit(1) ;
            }
            char * endPtr ;
            long code = strtol(argv[i+1], &endPtr, 10) ;
            if (*endPtr != '\0'){
                fprintf(stderr, "the return code has to be valid : %s is not valid\n", argv[i+1]) ;
                usage() ;
                exit(1) ;
            }
            args->normalCode = code ;
        }
        else if (strcmp(argv[i], "--args") == 0){
            args->arguments_enabled = 1 ;
            args->arguments_program = argv+i ;
            break ; // after --args, there is no arguments for the code
        }
        else if (strcmp(argv[i], "--testOutput") == 0){
            args->testOutputRequired = 1 ;
            if (i+1 >= argc){
                //error
                fprintf(stderr, "you have to give an output file after enabling the test of output\n") ;
                usage() ;
                exit(1) ;
            }
            args->outputFilename = argv[i+1] ;
        }
    }
}
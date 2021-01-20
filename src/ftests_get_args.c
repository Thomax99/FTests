
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "utilitaries.h"
#include "ftests_get_args.h"

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
    free(args->func) ;
    free(args) ;
}

void get_args(ftests_args_t * args, int argc, char ** argv){
    //recup of first arg
    if (argc < 2 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-f") != 0)){
        fprintf(stderr, "first argument has to be -c or -f\n") ;
        usage() ;
        exit(1) ;
    }
    if (argc < 3){
        fprintf(stderr, "need a program name\n") ;
        usage() ;
        exit(1) ;
    }
    args->programName = argv[2] ;
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-c") == 0){
            args->compilatedProgramTest = 1 ;
        }
        else if (strcmp(argv[i], "-f") == 0){
            args->functionProgramTest = 1 ;
        }
        else if (strcmp(argv[i], "--function") == 0){
            if (args->compilatedProgramTest){
                fprintf(stderr, "you can't give a function parameter with the option -c\n") ;
                usage() ;
                exit(1) ;
            }
            if (argc < i+4){
                fprintf(stderr, "you have to give a function name, a type and a value after --function\n") ;
                usage() ;
                exit(1) ;
            }
            args->func = ftests_function_initializer(argv[i+1], argv[i+3], argv[i+2]) ;
        }
        else if (strcmp(argv[i], "--timeEnabled") == 0){
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
            if (args->functionProgramTest){
                fprintf(stderr, "you can't give a return code parameter with the option -f\n") ;
                usage() ;
                exit(1) ;
            }
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
            if (args->compilatedProgramTest){
                args->arguments_enabled = 1 ;
                args->arguments_program = argv+i ;
            }
            else {
                int nb_args_staying = argc - i-1 ;
                if (nb_args_staying&1){
                    fprintf(stderr, "For testing a function with arguments, you need to give for each argument a pear value type\n") ;
                    usage() ;
                    exit(1) ;
                }
                if (args->func != NULL){
                    ftests_function_make_arguments(args->func, argv+i+1, nb_args_staying) ;
                }
            }

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
    if (args->compilatedProgramTest && args->functionProgramTest){
        fprintf(stderr, "you can't test at the same time a program and a function\n") ;
        usage() ;
        exit(1) ;
    }
    if (args->functionProgramTest && args->func == NULL){
        fprintf(stderr, "with -f option, you need to give the argument --function\n") ;
        usage() ;
        exit(1) ;
    }
}
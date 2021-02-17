
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
    for(int i = 0; i < args->nb_function_to_test; i++){
        ftests_function_free(args->funcs[i]) ;
    }
    free(args->funcs) ;
    free(args) ;
}

void get_args(ftests_args_t * args, int argc, char ** argv){
    //recup of first arg
    if (argc < 2 || (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-f") != 0 && strcmp(argv[1], "-x") != 0)){
        fprintf(stderr, "first argument has to be -c or -f or -x\n") ;
        usage() ;
        exit(1) ;
    }
    if (argc < 3){
        fprintf(stderr, "need a program name\n") ;
        usage() ;
        exit(1) ;
    }
    int passAnalyze = 0;
    // if the first argument is -x, we have a variable function testing
    args->programName = argv[2] ;
    if (strcmp(argv[1], "-x") == 0){
        passAnalyze = 1 ;
        if (argc < 5){
            fprintf(stderr, "need a function to test and a correct function to compare\n") ;
            usage() ;
            exit(1) ;
        }
        args->functionVariableTested = 1 ;
        args->funcVar = malloc(sizeof(ftests_function_variable_t)) ;
        args->funcVar->function_name = argv[3] ;
        args->funcVar->correct_function_name = argv[4] ;
        args->funcVar->arguments = malloc(sizeof(ftests_function_argument_variable_t)) ;
        ftests_function_argument_variable_t * start = malloc(sizeof(ftests_function_argument_variable_t)), *last = start, * unlast = NULL ; ;
        for(int i = 5; i < argc; i+=3){
            if (i+1 >= argc || i+2 >= argc){
                fprintf(stderr, "The variable arguments has to be triolets ...\n") ;
                usage() ;
                exit(1) ;
            }
            char * endPtr ;
            long min = strtol(argv[i], &endPtr, 10) ;
            if (*endPtr != '\0'){
                fprintf(stderr, "the min has to be valid : %s is not valid\n", argv[i]) ;
                usage() ;
                exit(1) ;
            }
            long max = strtol(argv[i+1], &endPtr, 10) ;
            if (*endPtr != '\0'){
                fprintf(stderr, "the max has to be valid : %s is not valid\n", argv[i+1]) ;
                usage() ;
                exit(1) ;
            }
            long step = strtol(argv[i+2], &endPtr, 10) ;
            if (*endPtr != '\0'){
                fprintf(stderr, "the step has to be valid : %s is not valid\n", argv[i+2]) ;
                usage() ;
                exit(1) ;
            }
            if (min > max){
                fprintf(stderr, "min has to be inferior than max\n") ;
                usage() ;
                exit(1) ;
            }
            if (step <= 0){
                fprintf(stderr, "step has to be positive\n") ;
                usage() ;
                exit(1) ;
            }
            last->max = max ; last->min = min ; last->step = step ;
            last->next_arg = malloc(sizeof(ftests_function_argument_variable_t)) ;
            unlast = last ;
            last = last->next_arg ;
        }
        if (start != last){
            args->funcVar->arguments = start ;
        }
        free(last) ;
        unlast->next_arg = NULL ;
    }
    for (int i = 0; i < argc && !passAnalyze ; i++){
        if (strcmp(argv[i], "-c") == 0){
            args->compilatedProgramTest = 1 ;
        }
        else if (strcmp(argv[i], "-f") == 0){
            args->functionProgramTest = 1 ;
            args->nb_function_to_test = 0 ;
            args->nb_max_function = 10 ;
            args->funcs = malloc(sizeof(ftests_function_t *) *args->nb_max_function) ;
        }
        else if (strcmp(argv[i], "--function") == 0){
            if (args->compilatedProgramTest){
                fprintf(stderr, "you can't give a function parameter with the option -c\n") ;
                usage() ;
                exit(1) ;
            }
            if (argc < i+3){
                fprintf(stderr, "you have to give at least a function name, and a return type --function\n") ;

            }
            if (strcmp(argv[i+2], "void") != 0 && argc < i+4){
                fprintf(stderr, "you have to give a function name, a type and a value after --function\n") ;
                usage() ;
                exit(1) ;
            }
            if (args->nb_function_to_test == args->nb_max_function){
                args->nb_function_to_test*=2 ;
                args->funcs = realloc(args->funcs, sizeof(ftests_function_t *) *args->nb_function_to_test) ;
            }
            int nb_args_to_jump ;
            args->funcs[args->nb_function_to_test] = ftests_function_initializer(argv[i+1], argv[i+3], argv[i+2], &nb_args_to_jump) ; //function creation

            // now we have to make the arguments
            int nb_args = 0 ;
            i+=nb_args_to_jump ;
            for(; i < argc && (strcmp(argv[i], "--endFunc")!=0); i++){
                //we have arguments
                nb_args++ ;
            }
            if (nb_args&1){
                fprintf(stderr, "For testing a function with arguments, you need to give for each argument a pear (value type)\n") ;
                usage() ;
                exit(1) ;
            }
            ftests_function_make_arguments(args->funcs[args->nb_function_to_test++], argv+i-nb_args, nb_args) ;
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
        else if (strcmp(argv[i], "--repeatTest") == 0){
            //we have a to repeat the test value
            fprintf(stderr, "here\n") ;
            args->repeatedTestRequired = 1 ;
            if (i+1 >= argc){
                //error
                fprintf(stderr, "you have to give a number after enabling the repeating of tests\n") ;
                usage() ;
                exit(1) ;
            }
            char * endPtr ;
            long times = strtol(argv[i+1], &endPtr, 10) ;
            if (*endPtr != '\0'){
                fprintf(stderr, "the repeating value has to be valid : %s is not valid\n", argv[i+1]) ;
                usage() ;
                exit(1) ;
            }
            args->timesRepeatTest = times ;
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
                fprintf(stderr, "The option --args is impossible with function testing\n") ;
                usage() ;
                exit(1) ;
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
    if (args->functionProgramTest && args->funcs == NULL){
        fprintf(stderr, "with -f option, you need to give the argument --function\n") ;
        usage() ;
        exit(1) ;
    }
}
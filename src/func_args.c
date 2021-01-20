#include "func_args.h"
#include "utilitaries.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN strlen("char * ") //the max size of a type is 10

ftests_function_t * ftests_function_initializer(char * name, char * retValue, char * returnType){
    ftests_function_t * value = malloc(sizeof(ftests_function_t)) ;
    value->name = name ;
    if (strcmp(returnType, "int") == 0){
        value->returntype = INTTYPE ;
    }
    else if (strcmp(returnType, "float") == 0){
        value->returntype = FLOATTYPE ;
    }
    else if (strcmp(returnType, "string") == 0){
        value->returntype = STRINGTYPE ;
    }
    else {
        fprintf(stderr, "you have to give a return type in {int, float, string}\n") ;
        usage() ;
        exit(1) ;
    }

    if (value->returntype == STRINGTYPE){
        value->value = retValue ;
    }
    else if (value->returntype == INTTYPE){
        char * endPtr ;
        strtol(retValue, &endPtr, 10) ;
        if (*endPtr != '\0'){
        fprintf(stderr, "the return value has to be valid : %s is not valid\n", retValue) ;
        usage() ;
        exit(1) ;
        }
        value->value = retValue ;
    }
    else{
        char * endPtr ;
        strtod(retValue, &endPtr) ;
        if (*endPtr != '\0'){
            fprintf(stderr, "the return value has to be valid : %s is not valid\n", retValue) ;
            usage() ;
            exit(1) ;
        }
        value->value = retValue ;
    }
    value->nb_arguments = 0 ;
    return value ;
}

void ftests_function_make_arguments(ftests_function_t * func, char ** args, int nb_args){
    func->nb_arguments = nb_args/2 ;
    func->arguments = malloc(nb_args*sizeof(ftests_function_argument_t)) ;
    for(int i = 0; i < func->nb_arguments; i++){
        (func->arguments+i)->value = args[2*i] ;
        if (strcmp(args[2*i+1], "int") == 0 || strcmp(args[i+1], "float") == 0){
            (func->arguments+i)->isString = 0 ;
        }
        else if (strcmp(args[2*i+1], "string") == 0 ){
            (func->arguments+i)->isString = 1 ;
        }
        else {
            fprintf(stderr, "the arguments given at a function have the shape argument {int|float|string}\n") ;
            usage() ;
            exit(1) ;
        }
    }

}

void ftests_function_free(ftests_function_t * func){
    if (func != NULL){
        if (func->nb_arguments > 0) free(func->arguments) ;
        free(func) ;
    }
}

void getFunctionReturnType(char * dst, ftests_function_t * func){

    if (func->returntype == INTTYPE){
        sprintf(dst, "int ") ;
    }
    else if (func->returntype == FLOATTYPE){
        sprintf(dst, "float ") ;
    }
    else {
        sprintf(dst, "char * ") ;
    }
}

char * mystrncat(char * dst, char * src, int size_to_write, int * max_size, int * act_size){

    if (*act_size+size_to_write >= *max_size) {
        (*max_size)*=2 ;
        dst = realloc(dst, *max_size) ;
    }
    strncat(dst, src, size_to_write) ;
    act_size+=size_to_write ;
    return dst ;
}

void makeArguments(char * dst, ftests_function_argument_t * arguments, int nb_arguments, int * max_size, int * act_size){
    for(int i = 0 ; i < nb_arguments ; i++){
        if ((arguments+i)->isString){
            char arg_string[strlen("\"\"")+strlen((arguments+i)->value)+1] ;
            sprintf(arg_string, "\"%s\"", (arguments+i)->value) ;
            mystrncat(dst, arg_string, strlen(arg_string),max_size,act_size) ;
        }
        else {
            char arg_string[strlen((arguments+i)->value)+1] ;
            sprintf(arg_string, "%s", (arguments+i)->value) ;
            mystrncat(dst, arg_string, strlen(arg_string),max_size,act_size) ;
        }
        if (i+1 < nb_arguments )
            mystrncat(dst, ", ", strlen(", "),max_size,act_size) ;
    }
}


char * getFunctionTest(ftests_function_t * func){
    int size = 128, act_size = 0 ;
    char * dst = malloc(size*sizeof(char)) ;
    if (func->returntype == INTTYPE || func->returntype == FLOATTYPE){
        char func_call[strlen("test = (")+strlen(func->name)+ 1] ;
        sprintf(func_call, "test = (%s(", func->name) ;
        mystrncat(dst, func_call, strlen(func_call), &size, &act_size) ;
        makeArguments(dst, func->arguments, func->nb_arguments, &size, &act_size) ;
        char valueTest[strlen(") == ")+strlen(func->value)+strlen(");\n")] ;
        sprintf(valueTest, ") == %s);\n", func->value) ;
        mystrncat(dst,valueTest, strlen(valueTest), &size, &act_size) ;
    }
    else {
        char func_call[strlen("test = (strcmp(")+strlen(func->name)+ 2] ;
        sprintf(func_call, "test = (strcmp(%s(", func->name) ;
        mystrncat(dst, func_call, strlen(func_call), &size, &act_size) ;
        makeArguments(dst, func->arguments, func->nb_arguments, &size, &act_size) ;
        char valueTest[strlen("), \"")+strlen(func->value)+strlen("\") == 0);\n")] ;
        sprintf(valueTest, "), \"%s\") == 0);\n", func->value) ;
        mystrncat(dst,valueTest, strlen(valueTest), &size, &act_size) ;
    }
    return dst ;
}
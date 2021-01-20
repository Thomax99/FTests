
#include <stdio.h>
#include <stdlib.h>
#include "utilitaries.h"
#include "string.h"

void usage(){
    fprintf(stderr, "[SOMETHING GOING WRONG]\n") ;
    fprintf(stderr, "[USAGE] ") ;
    fprintf(stderr, "ftests -{c|f} {programName|fileName} [-option1 [option1Value] -option2 [option2Value] ... ] [--args arg1 arg2 ...]\n") ;
    fprintf(stderr, "the first argument has to be -c or -f\n") ;
    fprintf(stderr, "if the first argument is -c, the second argument has to be a valid compilated program\n") ;
    fprintf(stderr, "if the first argument is -f, the second argument has to be a valid c file\n") ;
    fprintf(stderr, "options could be :\n") ;
    fprintf(stderr, " [--timeEnabled time] : stop the test after time seconds\n") ;
    fprintf(stderr, " [--enableReturnCode code] : test if the return code of the program is code (useful just if the first argument is -c)\n") ;
    fprintf(stderr, " [--testOutput output] : test if the standard output of the program or the function is the same than the one which is given on the file output\n") ;
    fprintf(stderr, "In case that the first argument is -c, you can give arguments to the program by specifying --args and after give arguments\n") ;
    fprintf(stderr, " [--function func {int|float|string} retValue [typeArg1 arg1 typeArg2 arg2 ] --endFunc] tests the function func in the c file given previously (only if the argument is -f). You have to give after a return type (nothing else than int, float or string) and a retValue corresponding to the type given. You also can give arguments to the function with give a type and an arguments or more. You have to finish with the arguments --endFunc\n") ;
    fprintf(stderr, "---********************************---\n") ;
    fprintf(stderr, "show if all is good or the type of error. This framework tests also currents exceptions\n") ;

}

void change_char(char input, char * dst){
    switch(input){
        case('\n') :
            sprintf(dst, "Newline") ;
            break ;
        case('\a') :
            sprintf(dst, "Alert") ;
            break ;
        case('\b') :
            sprintf(dst, "Backspace") ;
            break ;
        case('\t') :
            sprintf(dst, "Horizontal tab") ;
            break ;
        case('\v') :
            sprintf(dst, "Vertical tab") ;
            break ;
        case('\r') :
            sprintf(dst, "Carriage return") ;
            break ;
        case(' ') :
            sprintf(dst, "Space") ;
            break ;
        default :
            sprintf(dst, "%c", input) ;
            break ;
    }
}

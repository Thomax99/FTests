
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
    fprintf(stderr, "In case that the first argument is -c, you can give to the program by specifying --args and after give arguments\n") ;
    fprintf(stderr, "---********************************---\n") ;
    fprintf(stderr, "show if all is good or the type of error. This framework tests also currents exceptions\n") ;

}

char * change_char(char input){
    char * ret = malloc(sizeof(char)*20) ;
    switch(input){
        case('\n') :
            sprintf(ret, "Newline") ;
            break ;
        case('\a') :
            sprintf(ret, "Alert") ;
            break ;
        case('\b') :
            sprintf(ret, "Backspace") ;
            break ;
        case('\t') :
            sprintf(ret, "Horizontal tab") ;
            break ;
        case('\v') :
            sprintf(ret, "Vertical tab") ;
            break ;
        case('\r') :
            sprintf(ret, "Carriage return") ;
            break ;
        case(' ') :
            sprintf(ret, "Space") ;
            break ;
        default :
            sprintf(ret, "%c", input) ;
            break ;
    }
    return ret ;
}

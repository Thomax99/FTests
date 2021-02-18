#include <stdio.h>

char * func(char * str, int integer){
    printf("%s \n", str) ;
    return str ;
}

int func2(char * str, int integer){
    printf("%s \n", str) ;
    return integer ;
}

void func3(){
    printf("coucou\n") ;
}

int func4(int a, int b){
    return a + b ;
}

int func5(int a, int b){
    return a - b ;
}
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    for(int i = 0; i < argc; i++){
        printf("%s ", argv[i]) ;
    }
    printf("\naucun problème\n") ;
    printf("aucun problème\n") ;
    return 0 ;
}

int func(){
    return 3 ;
}
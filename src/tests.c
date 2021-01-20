#include "main.h"
#include "tests.h"
#include "ftests_get_args.h"
#include "utilitaries.h"
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

jmp_buf env ;
int pid_son = 0 ;
int son_time_out = 0 ;

void handler(int signal){
    if (pid_son == 0) {
        fprintf(stderr, "too small time out\n") ;
        exit(1) ;
    }
    son_time_out = 1 ; //notify that the son has been timed out
    kill(pid_son, SIGSTOP) ;
}


int ftests_test_main(ftests_args_t * args){

    if (args->functionProgramTest){
        //we have to make a file and compile it

        int fd = open("./tmp1.c", O_WRONLY|O_CREAT|O_TRUNC, 0660) ; //we create the file needed
        if (fd == -1){
            perror("creating file for function testing") ;
            exit(1) ;
        }
        char header[strlen("#include \" \"\n #include <string.h>\n ")+strlen(args->programName)+3] ;
        sprintf(header, "#include \"%s\"\n #include <string.h>\n", args->programName) ;

        write(fd, header, strlen(header)) ;

        char * firstLine = "\nint main(){\n" ;
        write(fd, firstLine, strlen(firstLine)) ;
        char * sLine = getFunctionTest(args->func) ;
        write(fd, sLine, strlen(sLine)) ;
        free(sLine) ;
        char *fLine ="return test ;\n}" ;
        write(fd, fLine, strlen(fLine)) ;
        close(fd) ;

        //remove("./tmp1.c") ;
        fprintf(stderr, "___  GCC COMPILATION PROCESSING ...  ___\n") ;
        int pid = fork() ;
        if(!pid){
            //son : we're going to compilate the program here
            execlp("gcc", "gcc", "./tmp1.c", "-o", "tmp1", "-Werror", NULL) ;
            perror("function testing file compilation error : ") ;
            exit(2) ;
        }
        int status, compilationError = 0 ;
        waitpid(pid, &status, 0) ;
        fprintf(stderr, "___ ... END OF GCC COMPILATION  ___\n\n\n") ;
        if (WEXITSTATUS(status) != 0){
            fprintf(stderr, "function error : the compilation of %s on the file %s is impossible\n", args->func->name, args->programName) ;
            compilationError = 1 ;
        }
        args->programName = "./tmp1" ;

        // if the return code of the program is 0, there is no problem, else the function doesn't return the good thing
        args->testReturnCodeRequired = 1;
        args->normalCode = 0 ;

        remove("./tmp1.c") ;
        if (compilationError){
            remove ("./tmp1") ;
            return COMPILATIONERRORRETURN ;
        }

    }

    struct sigaction sa_old ;
    if (args->testTimeRequired){
        struct sigaction sa ;
        sa.sa_flags = 0 ;
        sa.sa_handler = &handler ;
        sigemptyset(&sa.sa_mask) ;
        sigaction(SIGALRM, &sa, &sa_old) ;
        alarm(args->maxTimeRequired) ;
    }
    int tube[2] ; //the pipe in which we're going to test the output of the program
    if (args->testOutputRequired) pipe(tube) ; //we make it just if the outputTest is required, to don't make not useful systems calls
    fprintf(stderr, "PROGRAM EXECUTION\n\n")  ;
    pid_son = fork() ;
    if (!pid_son){
        //son
        if (args->testOutputRequired){
            close(tube[0]) ;
            dup2(tube[1], 1) ;
            close(tube[1]) ;
        }
        if (args->arguments_enabled){
            *(args->arguments_program) = args->programName ; //uggly manip but we ensure that this is good : args are not the first argument : there is the first argument --args before ...
            execvp(args->programName, args->arguments_program) ;
        }
        else
            execlp(args->programName, args->programName, NULL) ;
        perror("execution problem : ") ;
        exit(1) ;
    }
    int outputProblem = 0, sizeProblem = 0 ;
    if (args->testOutputRequired){
        //we test the output
        close(tube[1]) ;
        int fd = open(args->outputFilename, O_RDONLY) ;
        if (fd == -1){
            perror("output file problem : ") ;
            exit(1) ;
        }
        char c1, c2 ; int size_output_file = lseek(fd, 0, SEEK_END), nb_char_read = 0 ;
        lseek(fd, 0, SEEK_SET) ;
        while(read(tube[0], &c1, 1) > 0){
            if (nb_char_read >= size_output_file){
                sizeProblem = 1 ;
                fprintf(stderr, "output problem : the program write too much on the ouput : the size of the output file is %d\n", size_output_file) ;
                break ;
            }
            read(fd, &c2, 1) ;
            if (c1 != c2){
                outputProblem = 1;
                char getCharNormal[20], getCharOutput[20] ;
                change_char(c2, getCharNormal) ;
                change_char(c1, getCharOutput) ;
                fprintf(stderr, "output problem : the program write the char %s instead of the char %s at the position %d\n", getCharOutput, getCharNormal, nb_char_read) ;
                break ;
            }
            nb_char_read++ ;
        }
        if (nb_char_read < size_output_file && !outputProblem){
            sizeProblem = 1 ;
            fprintf(stderr, "output problem : the program write too few on the ouput : the size of the output file is %d\n", size_output_file) ;
        }
        close(tube[0]) ; close(fd) ;
    }
    int status ;
    waitpid(pid_son, &status, 0) ;
    fprintf(stderr, "\nEND OF PROGRAM EXECUTION\n\n\n")  ;
    if (args->functionProgramTest) remove("./tmp1") ;
    if (outputProblem || sizeProblem){
            return OUTPUTPROBLEMRETURN ;
        }
    if (son_time_out){
        //the program has been killed by the test
        fprintf(stderr, "timeout -> the deadline of %ld seconds is missed\n", args->maxTimeRequired) ;
        return TIMEOUTRETURN ;
    }
    if (WIFSIGNALED(status)){
        //a signal has occured
        switch (WTERMSIG(status)){
            case SIGSEGV :
                fprintf(stderr, "memory error -> illegal access to memory\n") ;
                break ;
            case SIGSTKFLT :
                fprintf(stderr, "stack error -> stack is empty or full\n") ;
                break ;
            case SIGFPE :
                fprintf(stderr, "arithmetic error -> an illegal calculation occured\n") ;
                break ;
            case SIGILL :
                fprintf(stderr, "instruction error -> an illegal instruction has been made\n") ;
                break ;
            default :
                fprintf(stderr, "unknow stopping signal : %s\n", strsignal(WTERMSIG(status))) ;
                break ;
        }
        return SIGNALRETURN ;
    }
    if (args->testReturnCodeRequired){
        // we have to test the return code
        if (WEXITSTATUS(status) != args->normalCode){
            if (args->functionProgramTest){
                // the function doesn't return the good thing
                fprintf(stderr, "function error -> your function %s doesn't return %s as you want\n", args->func->name, args->func->value) ;
                return ANORMALFUNCTIONRETURNERROR ;
            }
            fprintf(stderr, "return code -> the program has returned %d while it should have return %d\n", WEXITSTATUS(status), args->normalCode) ;
            return ANORMALCODERETURN ;
        }
    }
    return WELLTERMINATEDRETURN ;
}

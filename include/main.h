#ifndef MAINH

    #define MAINH 1

    #define OUTPUTPROBLEMRETURN -4
    #define ANORMALCODERETURN -3
    #define TIMEOUTRETURN -2
    #define SIGNALRETURN -1
    #define WELLTERMINATEDRETURN 0
    /**
     * @brief The structure that stores all the arguments of a test
     */
    typedef struct {
        int testReturnCodeRequired ;
        int programTested ;
        int functionTested ;
        int normalCode ;
        int testOutputRequired ;
        char * outputFilename ;
        int testTimeRequired ; // to know if we have to manage a time testing
        long maxTimeRequired ;
        char * programName ; //the name of the program
        int arguments_enabled ;
        char ** arguments_program ;
    } ftests_args_t ; //type used 

#endif
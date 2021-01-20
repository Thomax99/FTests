#ifndef STRUCTURESH
    #define STRUCTURESH

    typedef struct {
        char * value ;
        int isString ;
    }  ftests_function_argument_t ;

    typedef struct {
        int returntype ;
        char * name ;
        char * value ;
        int nb_arguments ;
        ftests_function_argument_t * arguments ;
    } ftests_function_t ;


    /**
     * @brief The structure that stores all the arguments of a test
     */
    typedef struct {
        int compilatedProgramTest ;
        int functionProgramTest ;
        int testReturnCodeRequired ;
        int programTested ;
        int functionTested ;
        int normalCode ;
        int testOutputRequired ;
        char * outputFilename ;
        ftests_function_t * func ;
        int testTimeRequired ; // to know if we have to manage a time testing
        long maxTimeRequired ;
        char * programName ; //the name of the program
        int arguments_enabled ;
        char ** arguments_program ;
    } ftests_args_t ; //type used 
#endif
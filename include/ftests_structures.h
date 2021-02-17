#ifndef STRUCTURESH
    #define STRUCTURESH

    typedef struct {
        char * value ;
        int isString ;
    }  ftests_function_argument_t ;

    typedef struct favt{
        int min ;
        int max ;
        int step ;
        struct favt * next_arg ;
    }   ftests_function_argument_variable_t ;

    typedef struct {
        char * function_name ;
        char * correct_function_name ;
        ftests_function_argument_variable_t * arguments ;
    } ftests_function_variable_t ;

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
        int functionVariableTested ;
        int normalCode ;
        int testOutputRequired ;
        char * outputFilename ;
        ftests_function_t ** funcs ;
        ftests_function_variable_t * funcVar ;
        int nb_function_to_test ;
        int nb_max_function ;
        int testTimeRequired ; // to know if we have to manage a time testing
        long maxTimeRequired ;
        int repeatedTestRequired ; // to know if we have to make the test more than one time
        long timesRepeatTest ;
        char * programName ; //the name of the program
        int arguments_enabled ;
        char ** arguments_program ;
    } ftests_args_t ; //type used 
#endif
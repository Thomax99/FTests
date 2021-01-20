# FTests

## Project

The idea of this project is to make a simple-to-use framework of tests in C

## Compilated program testing

The framework gives some facilities to make test on a compilated program

The first argument that you have to give is ```-c```. After you have to give the name of the compilated program.

You can give the option ```--enableReturnCode code```, to test the return code of the the given program.

You can also give the option ```--args arg1 arg2 arg3 ...``` to give some arguments to the program.

### Example

```bash
./ftests -c ./test_file --enableReturnCode 0 --args val1 val2
```

## Function testing

Also, this framework allow a programmer to make tests on not compilated functions.

The first argument that you have to give is ```-c```. After you have yo give the name of the c file which contains the function. For the moment, you cannot test a function which is on a file which contains a main function. Later, we will implement this functionnality.

To test a function, you have to give a function with the option ```--function funcName retType retValue```, with funcName the name of the function, retType the return tyepe of the function, in {int, float, string} and retValue the theoretic return of the function, with regards to the retTYpe and the arguments given.

You can also give arguments to a function to test it by specifying after the retValue arguments like ```--function funcName retType retValue arg1 typeArg1 --endArgs arg2 typeArg2 ...```. This will give to the function in first the argument arg1 of type typeArg1 in second the argument arg2 of type typeArg2, etc. It is required to ptu at the end of the arguments the parameter ```--endArgs```. With this, you can test several functions at the same time by specifying several ```--function ...``` options.

### Example

```bash
./ftests -c ./file.c --function hello int 4 --args bonjour string 1 int
```

## General options

Some options could be given each for ```-f``` or ```-c``` options. Those are :

- ```--timeEnabled time``` for stopping the test after time seconds
- ```--testOutput output``` for testing the output of the program on the standard output with the file named output


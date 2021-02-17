# FTests

## Project

The idea of this project is to make a simple-to-use framework of tests in C.

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

Also, this framework allow a programmer to make tests on not compilated functions. To enable this capacity, you need gcc on your computer and you need to can launch gcc with the line-command ```gcc```

The first argument that you have to give is ```-f```. After you have yo give the name of the c file which contains the function. For the moment, you cannot test a function which is on a file which contains a main function. Later, we will implement this functionnality.

To test a function, you have to give a function with the option ```--function funcName retType retValue```, with funcName the name of the function, retType the return tyepe of the function, in {int, float, string} and retValue the theoretic return of the function, with regards to the retTYpe and the arguments given.

You can also give arguments to a function to test it by specifying after the retValue arguments like ```--function funcName retType retValue arg1 typeArg1 arg2 typeArg2 ...```. This will give to the function in first the argument arg1 of type typeArg1 in second the argument arg2 of type typeArg2, etc. It is required to put at the end of the arguments the parameter ```--endFunc```. With this, you can test several functions at the same time by specifying several ```--function ...``` options.

- ```--repeatTest x``` for testing the program x times.

### Example

```bash
./ftests -f ./file.c --function hello int 4 bonjour string 1 int --endFunc
```

## Function comparing

In case that you have a function that you know it returns the good value, and which have the same skeleton than your function, you can launch a comparaison between the two functions and lauch it on variable arguments with integer type varying between 0 and 100 with a step of 2.

You have to give in first argument the ```-x``` parameter.

After, you give the file of the function (without main function on it) directly the function name, and the correct function name. You give after the triolets of (min max step) which are going to be given on the order. 

### Example

```bash
./ftests -x ./file.c function correctFunction 0 100 2 1 201 3
```

## General options

Some options could be given each for ```-f``` or ```-c``` options. Those are :

- ```--timeEnabled time``` for stopping the test after time seconds
- ```--testOutput output``` for testing the output of the program on the standard output with the file named output


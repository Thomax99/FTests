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

## General options

Some options could be given each for ```-f``` or ```-c``` options. Those are :

- ```--timeEnabled time``` for stopping the test after time seconds
- ```--testOutput output``` for testing the output of the program on the standard output with the file named output

.. TO DETAIL ...

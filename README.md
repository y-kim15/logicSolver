# CS2002 Practical 4 - Logic Solver

This repository contains the source code, report and output files for Practical 4 of module CS2002 C Programming. 

### Overview
This practical involved creating a program fulfilling the functionalities of a logic
solver, which creates and prints a truth table for logic formulas. This can be used to prove boolean algebras and to solve logic puzzles. The program required capability of validation check of input arguments and the format in which formula was written. All input formula should be written in postfix notation and the program will generate outputs of formula interpretation for all possible combinations of binary values of the symbols. 

Practial-Logic-Report is the summary report submitted at the time detailing design and implementation decisions and results generated by the solver which is also improved as an additional task of the practical. The full output of every input run is saved in output.txt files. The overall mark of this practical received was 20/20.


### Instructions
As a prerequisite of compiling and runnig the program, `make` and `gcc` should be installed. Makefile contains possible commands that can be run. 

The key executable files to create are `ttable` and `ttable2`. 

    make 

The above will simply run the first configuration on the Makefile which will generate both. Running the generated executable files will accept arguments in the following way. 

````` 
usage: ./ttable N F1

Description:

    N  number of symbols in the formula
    F1 input formula written in postfix notation in single quotes

`````

Example use case of 
`````
./ttable 2 'ab|-'
````` 
will generate the following output

`````
a b : ab|- : Result
===================
0 0 :   01 :   1
0 1 :   10 :   0
1 0 :   10 :   0
1 1 :   10 :   0
`````

### Extension 
The fuctionality of logic solver is improved as an extended work for this practical by introducing `ttable2`.


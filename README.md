# Bust-Language-Compiler
The project is designing and prototyping a compiler for the my own programming language called __"Bust"__.
The purpose of the project is to build a programming language help the beginners to learn the basic concept of programming with simplified grammar and syntax.
Currently, the project has already successfully implemented __reader, scanner, and parser__.

## Project Specification
The program is able to compile the program with  __".bs"__ extension. To do that, you can find and use the binary code under bin directory by command prompt with parameters of the compiler mode and .bs file.
For example:
./Bust.exe R Hello_World.bs to read all the characters from the .bs file
./Bust.exe S Hello_World.bs to scan all the keywords from the .bs file
./Bust.exe P Hello_World.bs to parse all the code from the .bs file

## Project Design and Implementations
So far, the project has successfully implemented the Reader, Scanner, and Parser for the compiler.

### Reader
The reader will dynamically allocate the memory to read all the characters from the Bust file, the status of reading such as stop reading will be determined by the Byte flag.
![image](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Reader.png)

### Scanner
The Scanner will recognize all the keywords from .bs file such as print! by the regular expression, transition table, and automaton implementation. The scanner will keep going through every character and find its corresponding type until the end of the file.
![image](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Scanner.png)

__Regular Expression Design__
![image](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Regular%20Expression.png)

__Automaton Design__
![image](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Automaton.png)

__Transition Table Deisgn__
![image](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Transition%20Table.png)

### Parser
The parser will analyze the lexical and syntactic correctness of all the scanned code recersivly. The errors from the code will be reported passing the correct syntax after parsing.
![parser](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Parser.png)

## About project:
 - The project is C-based, all the implementations of the features are by C language
 - The project supports compilation with CMake, if you want to compile the program yourself, make sure CMake version is 3.8 or higher
 - If you are intersted in 'Bust' programming language, please check the documentations directories to see the detailed specification.

## Upcoming feature:
 - Implementation of the functionalities of keywords


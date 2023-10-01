# Bust-Language-Compiler

The project is designing and prototyping a compiler for the programming language called "Bust"
If you are intersted in the features and its implementation such as automaton, transition table, please take a look at documentation directory

About project:
 - The project is C-based, all the implementations of the features are by C language
 - The project supports compilation with CMake

Features of the Compiler:
  - Reader: The reader is able to dynamically allocate the memory to read all the characters from the Bust file
  - Scanner: The scanner is able to recongnize all the keywords of the Bust Language
  - Parser: The parser is able to do the lexical and syntactic analyzing, the parser will report the error and pass the correct syntax

Upcoming feature:
  Implementation of the functionalities of keywords

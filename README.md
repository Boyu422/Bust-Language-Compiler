# Bust Language Compiler

The **Bust Language Compiler** is a project aimed at designing and prototyping a compiler for a custom programming language called **Bust**. This language is designed to help beginners learn the fundamental concepts of programming with simplified grammar and syntax. 

The project currently has successfully implemented key components of the compiler: the **Reader**, **Scanner**, and **Parser**.

## Project Overview

The Bust compiler processes files with the `.bs` extension. You can use the compiled binary found in the `bin` directory to compile `.bs` files through the command line by specifying the mode of operation and the file.

### Usage Examples
- To **read** all characters from a `.bs` file:
  ```bash
  ./Bust.exe R Hello_World.bs
  ```
- To **scan** and identify keywords:
  ```bash
  ./Bust.exe S Hello_World.bs
  ```
- To **parse** the code and check for syntactic correctness:
  ```bash
  ./Bust.exe P Hello_World.bs
  ```

## Design and Implementation

### Reader
The **Reader** component dynamically allocates memory to read all the characters from a Bust file. The reading process is controlled by a byte flag that determines when to stop reading.
![Reader Component](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Reader.png)

### Scanner
The **Scanner** identifies all keywords within the `.bs` file, such as `print!`, using regular expressions, a transition table, and an automaton. The Scanner processes each character sequentially until the end of the file, categorizing them based on their type.

#### Regular Expression Design
![Regular Expression](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Regular%20Expression.png)

#### Automaton Design
![Automaton](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Automaton.png)

#### Transition Table Design
![Transition Table](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Transition%20Table.png)

### Parser
The **Parser** recursively analyzes the lexical and syntactic correctness of the scanned code. Any errors found during parsing are reported, while syntactically correct code is passed forward.
![Parser Component](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/Parser.png)

## Project Details
- The project is implemented in **C**.
- It supports compilation via **CMake** (version 3.8 or higher is required).
- Detailed specifications of the **Bust** language are available in the `documentations` directory.

## Testing
To test the functionality of the compiler, several Bust example files and BAT scripts are available under the `input` directory. You can use the provided BAT scripts (`A12`, `A22`, or `A32`) to test the **Reader**, **Scanner**, and **Parser**. Check the errors and outputs to evaluate the compilation results.
![Testing Files](https://github.com/Boyu422/Bust-Language-Compiler/blob/main/iamges/testing%20files.png)

## Future Features
- Implementation of the functionalities for Bust language keywords.

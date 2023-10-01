/*
************************************************************
* Code version: 3
* Author: Boyu Li
************************************************************

###################################################
#                                                 #
#    BOYU		        @@@@@@@				LI    #
#                  @@-----------@@                #
#               @@@@|  B U S T  |@@@@             #
#            @@@@@@@@-----------@@@@@@@@          #
#         @@@@@@@@@@@@@  @@@@@@@   @@@@@@@        #
#       @@@@@@@@@@@@@      @@@       @@@@@@       #
#     @@@@@@@    @@@@@    @@@@       @@@@@@@@     #
#    @@@@@@@       @@@@@ @@@@@@@    @@@@@@@@@@    #
#   @@@@@@@        @@@@@ @@@@@ @@@@@@    @@@@@@   #
#  @@@@@@@@@@    @@             @@@@      @@@@@@  #
#  @@@@@@@@@@@@@@@  @@@@@  @@@@  @@@@   @@    @@  #
# @@@@@@@@@@@@@@@   @@@@@ @@@@@   @@@@@@@@@    @@ #
# @@@@@      @@@@   @@@ @@@ @@@   @@@@    @@@@@@@ #
# @@@@        @@@@  @@@ @@@ @@@   @@@      @@@@@@ #
#  @@@@     @@@@@@@              @@@@@    @@@@@@  #
#  @@@@@@@@@@@     @@@  @@@   @@@    @@@@@@@@@@   #
#   @@@@@@@@@@@   @@@ @@@@@@ @@@@@    @@@@@@@@@   #
#    @@@@@@@@@@@@@@@ @@@@@@    @@@@@@@@@@@@@@@    #
#     @@@@@@@@@       @@@        @@@@@@@@@@@      #
#       @@@@@@         @@         @@@@@@@@@       #
#         @@@@@       @@@@@     @@@@@@@@@         #
#            @@@@@@@@@@@@@@@@@@@@@@@@@            #	
#               @@@@@@@@@@@@@@@@@@@               #
#  COMPILERS        @@@@@@@@@@@        BUST	      #
#                                                 #
###################################################
*/

/*
************************************************************
* File name: parser.h
* Compiler: MS Visual Studio 2022
* Date: Sep 01 2022
* Purpose: This file is the main header for Parser (.h)
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef READER_H_
#include "Reader.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token			lookahead;
extern BufferReader*	stringLiteralTable;
extern i64		line;
extern Token			tokenizer();
extern String		keywordTable[KWT_SIZE];
static i64		syntaxErrorNumber = 0;

#define STR_LANGNAME	"Bust"
#define LANG_WRTE		"print"
#define LANG_READ		"read_line("
#define LANG_MAIN		"main("
#define LANG_FUNC		"fn"


/* Constants */
enum KEYWORDS {
	NO_ATTR = -1,
	KW_i64,		
	KW_f64,		
	KW_bool,		
	KW_String,		
	KW_char,	
	KW_NULL,	
	KW_if,		
	KW_else,		
	KW_while,	
	KW_fn,
	KW_return,
	KW_true,
	KW_false,
	KW_let
};

#define NUM_BNF_RULES 36

/* Parser */
typedef struct parserData {
	i64 parsHistogram[NUM_BNF_RULES];	/* Number of BNF Statements */
} ParserData, * pParsData;

/* Number of errors */
i64 numParserErrors;

/* Scanner data */
ParserData psData;

/* Function definitions */
bust_void startParser();
bust_void matchToken(i64, i64);
bust_void syncErrorHandler(i64);
bust_void printError();
bust_void printBNFData(ParserData psData);

/* List of BNF statements */
enum BNF_RULES {
	BNF_error,										/*  0: Error token */
	BNF_codeSession,								/*  1 */
	BNF_comment,									/*  2 */
	BNF_dataSession,								/*  3 */
	BNF_optionalStatements,							/*  5 */
	BNF_outputStatement,							/*  6 */
	BNF_outputVariableList,							/*  7 */
	BNF_program,									/*  8 */
	BNF_parameterSession,							/*  9 */
	BNF_statement,									/*  10 */
	BNF_statements,									/* 11 */
	BNF_statementsPrime,							/* 12 */	
	BNF_parameterVarListDeclarations,
	BNF_varListDeclarations,
	BNF_whileStatement,
	BNF_inputStatement,
	BNF_varListDeclaration,
	BNF_assignmentStatement,
	BNF_assignmentExpression,
	BNF_arithmeticExpression,
	BNF_arithmeticExpressionDeclaration,
	BNF_IntListDeclaration,
	BNF_FloatListDeclaration,
	BNF_StringListDeclaration,
	BNF_datatypeDeclaration,
	BNF_arithmeticExpressionDeclarationPrime,
	BNF_logicalExpression,
	BNF_logicalExpressionDeclaration,
	BNF_logicalExpressionDeclarationPrime,
	BNF_conditionalExpression,
	BNF_inputVariableList,
	BNF_varListDeclarationPrime
};


static String BNFStrTable[NUM_BNF_RULES] = {
	"BNF_error",
	"BNF_codeSession",
	"BNF_comment",
	"BNF_dataSession",
	"BNF_optVarListDeclarations",
	"BNF_optionalStatements",
	"BNF_outputStatement",
	"BNF_outputVariableList",
	"BNF_program",
	"BNF_parameterSession",
	"BNF_statement",
	"BNF_statements",
	"BNF_statementsPrime",
	"BNF_parameterVarListDeclarations",
	"BNF_varListDeclarations",
	"BNF_whileStatement",
	"BNF_inputStatement",
	"BNF_varListDeclaration",
	"BNF_assignmentStatement",
	"BNF_assignmentExpression",
	"BNF_arithmeticExpression",
	"BNF_arithmeticExpressionDeclaration",
	"BNF_IntListDeclaration",
	"BNF_FloatListDeclaration",
	"BNF_StringListDeclaration",
	"BNF_datatypeDeclaration",
	"BNF_arithmeticExpressionDeclarationPrime",
	"BNF_logicalExpression",
	"BNF_logicalExpressionDeclaration",
	"BNF_logicalExpressionDeclarationPrime",
	"BNF_conditionalExpression",
	"BNF_outputVariableList",
	"BNF_outputVariableListPrime",
	"BNF_outputVariableLists",
	"BNF_inputVariableList",
	"BNF_varListDeclarationPrime",
};



bust_void codeSession();
bust_void comment();
bust_void optVarListDeclarations();
bust_void optionalStatements();
bust_void outputStatement();
bust_void outputVariableList();
bust_void program();
bust_void parameterSession();
bust_void statement();
bust_void statements();
bust_void statementsPrime();
bust_void parameterVarListDeclarations();
bust_void varListDeclarations();
bust_void whileStatement();
bust_void ifStatement();
bust_void inputStatement();
bust_void varListDeclaration();
bust_void assignmentStatement();
bust_void assignmentExpression();
bust_void arithmeticExpression();
bust_void arithmeticExpressionDeclaration();
bust_void IntListDeclaration();
bust_void FloatListDeclaration();
bust_void StringListDeclaration();
bust_void datatypeDeclaration();
bust_void arithmeticExpressionDeclarationPrime();
bust_void logicalExpression();
bust_void logicalExpressionDeclaration();
bust_void logicalExpressionDeclarationPrime();
bust_void conditionalExpression();
bust_void outputVariableList();
bust_void outputVariableListPrime();
bust_void outputVariableLists();
bust_void inputVariableList();
bust_void varListDeclarationPrime();
#endif

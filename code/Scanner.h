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
* File name: Scanner.h
* Compiler: MS Visual Studio 2022
* Date: May 01 2022
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 20  /* variable identifier length */
#define ERR_LEN 40  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1  /* Value for run-time error */

/* Define the number of tokens */
#define NUM_TOKENS 22

/* Define Token codes - Create your token classes */
enum TOKENS {
	ERR_T,		/*  0: Error token */
	MNID_T,		/*  1: Method name identifier token (start: &) */
	INL_T,		/*  2: Integer literal token */
	STR_T,		/*  3: String literal token */
	LPR_T,		/*  4: Left parenthesis token */
	RPR_T,		/*  5: Right parenthesis token */
	LBR_T,		/*  6: Left brace token */
	RBR_T,		/*  7: Right brace token */
	KW_T,		/*  8: Keyword token */
	EOS_T,		/*  9: End of statement (semicolon) */
	RTE_T,		/* 10: Run-time error token */
	SEOF_T,		/* 11: Source end-of-file token */
	CMT_T,		/* 12: Comment token */
    FLL_T,      /* 13: Float literal token */
    VAR_T,      /* 14: Variable literal token */
    PER_T,      /* 15: Period literal token */
    REL_T,      /* 16: Relational Operator token */
    ARI_T,      /* 17: Arithmetic Operator token */
    ASS_T,      /* 18: Assignment Token*/
    UND_T,       /* 19: Underscore Token*/
    LOG_T,      /* 20: Logical Operator Token*/
	COL_T
};

/* Define the list of keywords */
static String tokenStrTable[NUM_TOKENS] = {
	"ERR_T",
	"MNID_T",
	"INL_T",
	"STR_T",
	"LPR_T",
	"RPR_T",
	"LBR_T",
	"RBR_T",
	"KW_T",
	"EOS_T",
	"RTE_T",
	"SEOF_T",
	"CMT_T",
    "FLL_T",      /* 13: Float literal token */
    "VAR_T",      /* 14: Variable literal token */
    "PER_T",      /* 15: Period literal token */
    "REL_T",      /* 16: Relational Operator token */
    "ARI_T",      /* 17: Arithmetic Operator token */
    "ASS_T",      /* 18: Assignment Token*/
         "UND_T",       /* 19: Underscore Token*/
         "LOG_T",
		 "COL_T"
};

/*  Operators token attributes */
typedef enum ArithmeticOperators { OP_ADD, OP_SUB, OP_MUL, OP_DIV, OP_POW } AriOperator;
typedef enum RelationalOperators { OP_EQ, OP_NE, OP_GT, OP_LT } RelOperator;
typedef enum LogicalOperators { OP_AND, OP_OR, OP_NOT } LogOperator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_255 } EofOperator;
typedef enum AssignmentOperator { OP_ASS } AssOperator;

/* Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
	i64 codeType;      /* integer attributes accessor */
	AriOperator arithmeticOperator;		/* arithmetic operator attribute code */
	RelOperator relationalOperator;		/* relational operator attribute code */
	LogOperator logicalOperator;		/* logical operator attribute code */
	EofOperator seofType;				/* source-end-of-file attribute code */
    AssOperator assignmentOperator;     /* Assignment operator attribute code */
	i64 intValue;						/* integer literal attribute (value) */
	i64 keywordIndex;					/* keyword index in the keyword table */
	i64 contentString;				/* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
	f64 floatValue;					/* floating-point literal attribute (value) */
	bust_char idLexeme[VID_LEN + 1];		/* variable identifier token attribute */
	bust_char errLexeme[ERR_LEN + 1];		/* error token attribite */
} TokenAttribute;

/* Should be used if no symbol table is implemented */
typedef struct idAttibutes {
	bust_byte flags;			/* Flags information */
	union {
		i64 intValue;				/* Integer value */
		f64 floatValue;			/* Float value */
		String stringContent;		/* String value */
	} values;
} IdAttibutes;

/* Token declaration */
typedef struct Token {
	i64 code;				/* token code */
	TokenAttribute attribute;	/* token attribute */
	IdAttibutes   idAttribute;	/* not used in this scanner implementation - for further use */
} Token;

/* Scanner */
typedef struct scannerData {
	i64 scanHistogram[NUM_TOKENS];	/* Statistics of chars */
} ScannerData, * pScanData;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF

/*  Special case tokens processed separately one by one in the token-driven part of the scanner:
 *  LPR_T, RPR_T, LBR_T, RBR_T, EOS_T, SEOF_T and special chars used for tokenis include _, & and ' */

/* Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '.'
#define CHRCOL3 '_'
#define CHRCOL5 '\n'
#define CHRCOL6 '\"'
#define CHRCOL8 '('

/* These constants will be used on VID / MID function */
#define MNID_SUF '('
#define COMM_SYM '/'

/* Error states and illegal state */
#define ESNR	13		/* Error state with no retract */
#define ESWR	14		/* Error state with retract */
#define FS		100		/* Illegal state */

 /* State transition table definition */
#define NUM_STATES		15
#define CHAR_CLASSES	9

/*  Transition table - type of states defined in separate table */
static i64 transitionTable[NUM_STATES][CHAR_CLASSES] = {
/*    [A-z],[0-9],    _,    &,   \', SEOF,    #, other
	   L(0), D(1), U(2), M(3), Q(4), E(5), C(6),  O(7) */
	{     3, 6, ESNR, ESNR,    12, ESWR,	  10, ESNR, ESNR},	// S0: NOAS
	{     1,    1,    1,    1,	  1,    2,   1,    1,   1},	// S1: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,  FS},	// S2: ASNR (MVID)
	{    3,   3,   4,   3,   4,   4,	 4,   4,    5},	// S3: ASWR (KEY)
	{     FS,    FS,    FS,    FS,    FS, FS,	  FS,    FS, FS},	// S4: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS},	// S5: ASNR (SL)
	{     7,    6,    8,    7,    7, 7,	  7,    7,  7},	// S6: NOAS
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS, FS},	// S7: ASNR (COM)
	{    9,   8,   9,   9,   9,   9,	 9,   9, 9},	// S8: ASNR (ES)
	{    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,  FS},
    {       10, 10, 10, 10, 10, 10, 11, 10, 10},// S9: ASWR (ER)
    {    FS,   FS,   FS,   FS,   FS,   FS,	 FS,   FS,  FS},
    {ESNR, ESNR, ESNR, ESNR, 1, ESNR, ESNR, ESNR, ESNR},
};

/* Define accepting sta     tes types */
#define NOFS	0		/* not accepting state */
#define FSNR	1		/* accepting state with no retract */
#define FSWR	2		/* accepting state with retract */

/*  Define list of acceptable states */
static i64 stateType[NUM_STATES] = {
	NOFS, /* 00 */
	NOFS, /* 01 */
	FSNR, /* 02 (MID) - Methods */
	NOFS, /* 03 (KEY) */
	FSWR, /* 04 */
	FSNR, /* 05 (SL) */
	NOFS, /* 06 */
	FSWR, /* 07 (COM) */
	NOFS, /* 08 (Err1 - no retract) */
	FSWR,  /* 09 (Err2 - retract) */
    NOFS,
        FSNR,
        NOFS,
        FSNR,
        FSWR
};


/* Static (local) function  prototypes */
i64			startScanner(ReaderPointer psc_buf);
static i64	nextClass(bust_char c);					/* character class function */
static i64	nextState(i64, bust_char);		/* state machine function */
bust_void			printScannerData(ScannerData scData);
Token tokenizer(bust_void);
/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(String lexeme);

/* Declare accepting states functions */
Token funcSL	(String lexeme);
Token funcIL	(String lexeme);
Token funcID	(String lexeme);
Token funcCMT   (String lexeme);
Token funcKEY	(String lexeme);
Token funcErr	(String lexeme);
Token funcVAR   (String lexeme);
Token funcFL    (String lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/*  Define final state table */
static PTR_ACCFUN finalStateTable[NUM_STATES] = {
	NULL,		/* -    [00] */
	NULL,		/* -    [01] */
    funcCMT,		/* MNID	[02] */
	NULL,	/* KEY  [03] */
	funcID,		/* -    [04] */
	funcID,		/* SL   [05] */
	NULL,		/* -    [06] */
	funcIL,	/* COM  [07] */
    NULL,
    funcFL,
    NULL,
    funcSL,
    NULL,
    funcErr,
    funcErr
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/*  Define the number of Keywords from the language */
#define KWT_SIZE 14

/*  Define the list of keywords */
static String keywordTable[KWT_SIZE] = {
	"i64",		/* KW00 */
	"f64",		/* KW01 */
	"bool",		/* KW02 */
	"String",		/* KW03 */
	"char",	/* KW04 */
	"NULL",		/* KW05 */
	"if",		/* KW06 */
	"else",		/* KW07 */
	"while",	/* KW08 */
    "fn",
    "return",
    "true",
    "false",
    "let"
};

/* NEW SECTION: About indentation */

/*
 * Scanner attributes to be used (ex: including: intendation data
 */

#define INDENT '\t'  /* Tabulation */

/*  Should be used if no symbol table is implemented */
typedef struct languageAttributes {
	bust_char indentationCharType;
	i64 indentationCurrentPos;
	/* Include any extra attribute to be used in your scanner (OPTIONAL and FREE) */
} LanguageAttributes;

/* Number of errors */
i64 numScannerErrors;

/* Scanner data */
ScannerData scData;

#endif

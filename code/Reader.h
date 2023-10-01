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
* File name: Reader.h
* Compiler: MS Visual Studio 2022
* Course: CST 8152 ?Compilers, Lab Section: [011, 012]
* Assignment: A12.
* Date: May 01 2023
* Professor: Paulo Sousa
* Purpose: This file is the main header for Reader (.h)
************************************************************
*/

/*
 *.............................................................................
 * MAIN ADVICE:
 * Please check the "TODO" labels to develop your activity.
 *.............................................................................
 */


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#define READER_H_

/* TIP: Do not change pragmas, unless necessary .......................................*/
/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */
/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer reader) */
enum READER_MODE {
	MODE_FIXED = 'F', /* Fixed mode (constant size) */
	MODE_ADDIT = 'A', /* Additive mode (constant increment to be added) */
	MODE_MULTI = 'M'  /* Multiplicative mode (constant increment to be multiplied) */
};

/* Constants about controls (not need to change) */
#define READER_ERROR		(-1)						/* General error message */
#define READER_TERMINATOR	'\0'							/* General EOF */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* You should add your own constant definitions here */
#define READER_MAX_SIZE	INT_MAX-1	/* maximum capacity */ 

#define READER_DEFAULT_SIZE			250		/* default initial buffer reader capacity */
#define READER_DEFAULT_INCREMENT	10		/* default increment factor */

/* Add your bit-masks constant definitions here - Defined for BOA */
/* BITS                                (7654.3210) */
#define READER_DEFAULT_FLAG 0x00 	/* (0000.0000)_2 = (000)_10 */
#define SET_BIT3	0x08
#define SET_BIT2	0x04
#define SET_BIT1	0x02
#define SET_BIT0	0x01

#define RESET_BIT3	0xF7
#define RESET_BIT2	0xFB
#define RESET_BIT1	0xFD
#define RESET_BIT0	0xFE

#define CHK_BIT3	0x08
#define CHK_BIT2	0x04
#define CHK_BIT1	0x02
#define CHK_BIT0	0x01

#define NCHAR				128			/* Chars from 0 to 127 */

#define CHARSEOF			(-1)		/* EOF Code for Reader */

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (SOFIA) .................................. */

/* TODO: Adjust datatypes */

/* Offset declaration */
typedef struct offset {
	i64 mark;			/* the offset to the mark position (in chars) */
	i64 read;			/* the offset to the get a char position (in chars) */
	i64 wrte;			/* the offset to the add chars (in chars) */
} Offset;

/* Buffer structure */
typedef struct bufferReader {
	String	content;			/* pointer to the beginning of character array (character buffer) */
	i64	size;				/* current dynamic memory size (in bytes) allocated to character buffer */
	i64	increment;			/* character array increment factor */
	i64	mode;				/* operational mode indicator */
	bust_byte	flags;				/* contains character array reallocation flag and end-of-buffer flag */
	Offset		offset;				/* Offset / position field */
	i64	histogram[NCHAR];	/* Statistics of chars */
	i64	numReaderErrors;	/* Number of errors from Reader */
} BufferReader, * ReaderPointer;

/* FUNCTIONS DECLARATION:  .................................. */
/* General Operations */
ReaderPointer	readerCreate		(i64, i64, i64);
ReaderPointer	readerAddChar		(ReaderPointer const, bust_char);
bool		readerClear		    (ReaderPointer const);
bool		readerFree		    (ReaderPointer const);
bool		readerIsFull		(ReaderPointer const);
bool		readerIsEmpty		(ReaderPointer const);
bool		readerSetMark		(ReaderPointer const, i64);
i64		readerPrint		    (ReaderPointer const);
i64		readerLoad			(ReaderPointer const, FILE* const);
bool		readerRecover		(ReaderPointer const);
bool		readerRetract		(ReaderPointer const);
bool		readerRestore		(ReaderPointer const);
/* Getters */
bust_char		readerGetChar		(ReaderPointer const);
String		readerGetContent	(ReaderPointer const, i64);
i64		readerGetPosRead	(ReaderPointer const);
i64		readerGetPosWrte	(ReaderPointer const);
i64		readerGetPosMark	(ReaderPointer const);
i64		readerGetSize		(ReaderPointer const);
i64		readerGetInc		(ReaderPointer const);
i64		readerGetMode		(ReaderPointer const);
bust_byte		readerGetFlags		(ReaderPointer const);
i64		readerPrintStat		(ReaderPointer const);
i64		readerNumErrors		(ReaderPointer const);

#endif

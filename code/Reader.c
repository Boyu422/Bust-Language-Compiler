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
***********************************************************
* File name: Reader.c
* Compiler: MS Visual Studio 2022
* Date: May 01 2023
* Purpose: This file is the main code for Buffer/Reader (A12)
************************************************************
*/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef READER_H_
#include "Reader.h"
#endif

/*
***********************************************************
* Function name: readerCreate
* Purpose: Creates the buffer reader according to capacity, increment
	factor and operational mode ('f', 'a', 'm')
* Author: Svillen Ranev / Paulo Sousa
* History/Versions: S22
* Called functions: calloc(), malloc()
* Parameters:
*   size = initial capacity
*   increment = increment factor
*   mode = operational mode
* Return value: bPointer (pointer to reader)
* Algorithm: Allocation of memory according to inicial (default) values.
* TODO ......................................................
*	- Adjust datatypes for your LANGUAGE.
*   - Use defensive programming
*	- Check boundary conditions
*	- Check flags.
*************************************************************
*/

ReaderPointer readerCreate(i64 size, i64 increment, i64 mode) {
	ReaderPointer readerPointer;
	/*  Defensive programming */
	if (size < 0 || size > READER_DEFAULT_SIZE || increment < 0)
		return NULL;
	/* Adjust the values according to parameters */
	if (!size) {
		size = READER_DEFAULT_SIZE;
		increment = READER_DEFAULT_INCREMENT;
	}
	if (!increment) {
		mode = MODE_FIXED;
	}
	if (mode != MODE_ADDIT && mode != MODE_FIXED && mode != MODE_MULTI) {
		return NULL;
	}
	readerPointer = (ReaderPointer)calloc(1, sizeof(BufferReader));
	if (!readerPointer) {
		return NULL;
	}
	readerPointer->content = (String)malloc(size);
	/* Defensive programming */
	if (!readerPointer->content) {
		return NULL;
	}
	/* Initialize the histogram */
	for (int i = 0; i < NCHAR; i++) {
		readerPointer->histogram[i] = 0;
	}
	readerPointer->size = size;
	readerPointer->increment = increment;
	readerPointer->mode = mode;
	/* Initialize flags */
	readerPointer->flags = READER_DEFAULT_FLAG;
	/* The created flag must be signalized as EMP */
	readerPointer->flags |= SET_BIT2;
	return readerPointer;
}


/*
***********************************************************
* Function name: readerAddChar
* Purpose: Adds a char to buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   ch = char to be added
* Return value:
*	readerPointer (pointer to Buffer Reader)
*************************************************************
*/

ReaderPointer readerAddChar(ReaderPointer const readerPointer, bust_char ch) {
	String tempReader = NULL;
	i64 newSize = 0;
	/* Defensive programming */
	if (!readerPointer) {
		return NULL;
	}

	if (ch < 0 || ch >= NCHAR) {
		readerPointer->numReaderErrors++;
		return NULL;
	}
	/*Reset Realocation */
	readerPointer->flags &= RESET_BIT1;
	/* Test the inclusion of chars */
	if (readerPointer->offset.wrte * (i64)sizeof(bust_char) < readerPointer->size) {
		/* This buffer is NOT full */
	} else {
		/* Reset Full flag */
		readerPointer->flags &= RESET_BIT3;
		switch (readerPointer->mode) {
		case MODE_FIXED:
			return NULL;
		case MODE_ADDIT:
			/* Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* Defensive programming */
			if (newSize >= READER_MAX_SIZE || newSize < 0) {
				return NULL;
			}
			break;
		case MODE_MULTI:
			/* Adjust new size */
			newSize = readerPointer->size + readerPointer->increment;
			/* Defensive programming */
			if (newSize >= READER_MAX_SIZE || newSize < 0) {
				return NULL;
			}
			break;
		default:
			return NULL;
		}
		/*  New reader allocation */
		tempReader = realloc(readerPointer->content, newSize);
		/* Defensive programming */
		if (!tempReader) {
			return NULL;
		}
		/* Check Relocation */
		if (tempReader != readerPointer->content) {
			readerPointer->flags |= SET_BIT1;
		}
		readerPointer->content = tempReader;
		readerPointer->size = newSize;
	}
	/* Add the char */
	readerPointer->content[readerPointer->offset.wrte++] = ch;
	/* Updates histogram */
	readerPointer->histogram[ch]++;
	return readerPointer;
}

/*
***********************************************************
* Function name: readerClear
* Purpose: Clears the buffer reader
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerClear(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer) {
		return BUST_FALSE;
	}
	/* Adjust flags original */
	readerPointer->flags = READER_DEFAULT_FLAG;
	readerPointer->offset.mark = 0;
	readerPointer->offset.read = 0;
	readerPointer->offset.wrte = 0;
	return BUST_TRUE;
}

/*
***********************************************************
* Function name: readerFree
* Purpose: Releases the buffer address
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerFree(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return BUST_FALSE;
	}
	/* Free pointers */
	free(readerPointer->content);
	free(readerPointer);
	return BUST_TRUE;
}

/*
***********************************************************
* Function name: readerIsFull
* Purpose: Checks if buffer reader is full
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerIsFull(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return BUST_FALSE;
	}
	/* Check flag if buffer is FUL */
	if (!readerPointer->flags == CHK_BIT3) {
		return BUST_TRUE;
	}
	return BUST_FALSE;
}


/*
***********************************************************
* Function name: readerIsEmpty
* Purpose: Checks if buffer reader is empty.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerIsEmpty(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return BUST_FALSE;
	}
	/* Check flag if buffer is EMP */
	if (!readerPointer->flags == CHK_BIT2) {
		return BUST_TRUE;
	}
	return BUST_FALSE;
}

/*
***********************************************************
* Function name: readerSetMark
* Purpose: Adjust the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   mark = mark position for char
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerSetMark(ReaderPointer const readerPointer, i64 mark) {
	/* Defensive programming */
	if (!readerPointer || mark < 0 || mark > readerPointer->offset.wrte) {
		return BUST_FALSE;
	}
	/* Adjust mark */
	readerPointer->offset.mark = mark;
	return BUST_TRUE;
}


/*
***********************************************************
* Function name: readerPrint
* Purpose: Prints the string in the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of chars printed.
*************************************************************
*/
i64 readerPrint(ReaderPointer const readerPointer) {
	i64 cont = 0;
	bust_char c;
	/* Defensive programming (including invalid chars) */
	if (!readerPointer) {
		return READER_ERROR;
	}
	c = readerGetChar(readerPointer);
	if (c < 0 || c > 127) {
		return READER_ERROR;
	}
	/* Check flag if buffer EOB has achieved */
	while (cont < readerPointer->offset.wrte) {
		if (readerPointer->flags == CHK_BIT0)
			break;
		cont++;
		printf("%c", c);
		c = readerGetChar(readerPointer);
	}
	return cont;
}

/*
***********************************************************
* Function name: readerLoad
* Purpose: Loads the string in the buffer with the content of
	an specific file.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   fileDescriptor = pointer to file descriptor
* Return value:
*	Number of chars read and put in buffer.
*************************************************************
*/
i64 readerLoad(ReaderPointer const readerPointer, FILE* const fileDescriptor) {
	i64 size = 0;
	bust_char c;
	/* Defensive programming */
	if (!readerPointer || !fileDescriptor) {
		return READER_ERROR;
	}
	c = (bust_char)fgetc(fileDescriptor);
	while (!feof(fileDescriptor)) {
		if (!readerAddChar(readerPointer, c)) {
			ungetc(c, fileDescriptor);
			return READER_ERROR;
		}
		c = (char)fgetc(fileDescriptor);
		size++;
	}
	/* Defensive programming */
	if (size < 0 || size > READER_MAX_SIZE) {
		return READER_ERROR;
	}
	return size;
}


/*
***********************************************************
* Function name: readerRecover
* Purpose: Rewinds the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value
*	Boolean value about operation success
*************************************************************
*/
bool readerRecover(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return BUST_FALSE;
	}
	/* Recover positions */
	readerPointer->offset.mark = 0;
	readerPointer->offset.read = 0;
	return BUST_TRUE;
}


/*
***********************************************************
* Function name: readerRetract
* Purpose: Retracts the buffer to put back the char in buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerRetract(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer || readerPointer->offset.read <= 0) {
		return BUST_FALSE;
	}
	/* Retract (return 1 pos read) */
	readerPointer->offset.read--;
	return BUST_TRUE;
}


/*
***********************************************************
* Function name: readerRestore
* Purpose: Resets the buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Boolean value about operation success
*************************************************************
*/
bool readerRestore(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return BUST_FALSE;
	}
	/* Restore positions (read/mark) */
	readerPointer->offset.read = readerPointer->offset.mark;
	return BUST_TRUE;
}


/*
***********************************************************
* Function name: readerGetChar
* Purpose: Returns the char in the getC position.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Char in the getC position.
*************************************************************
*/
bust_char readerGetChar(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/*  Check condition to read/wrte */
	if (readerPointer->offset.read == readerPointer->offset.wrte) {
		/* Set EOB flag */
		readerPointer->flags |= SET_BIT0;
		return READER_TERMINATOR;
	}
	/* Reset EOB flag */
	readerPointer->flags &= RESET_BIT0;
	return readerPointer->content[readerPointer->offset.read++];
}


/*
***********************************************************
* Function name: readerGetContent
* Purpose: Returns the pointer to String.
* Parameters:
*   readerPointer = pointer to Buffer Reader
*   pos = position to get the pointer
* Return value:
*	Position of string char.
*************************************************************
*/
String readerGetContent(ReaderPointer const readerPointer, i64 pos) {
	/* Defensive programming */
	if (!readerPointer) {
		return NULL;
	}
	/*  Return content (string) */
	if (pos >= 0 && pos < readerPointer->offset.wrte) {
		return readerPointer->content + pos;
	}
	return NULL;
}



/*
***********************************************************
* Function name: readerGetPosRead
* Purpose: Returns the value of getCPosition.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The read position offset.
*************************************************************
*/
i64 readerGetPosRead(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/*  Return read */
	return readerPointer->offset.read;
}


/*
***********************************************************
* Function name: readerGetPosWrte
* Purpose: Returns the position of char to be added
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Write position
*************************************************************
*/
i64 readerGetPosWrte(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/*  Return wrte */
	return readerPointer->offset.wrte;
}


/*
***********************************************************
* Function name: readerGetPosMark
* Purpose: Returns the position of mark in the buffer
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Mark position.
*************************************************************
*/
i64 readerGetPosMark(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* Return mark */
	return readerPointer->offset.mark;
}


/*
***********************************************************
* Function name: readerGetSize
* Purpose: Returns the current buffer capacity
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Size of buffer.
*************************************************************
*/
i64 readerGetSize(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* Return size */
	return readerPointer->size;
}

/*
***********************************************************
* Function name: readerGetInc
* Purpose: Returns the buffer increment.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	The Buffer increment.
*************************************************************
*/
i64 readerGetInc(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/*  Return increment */
	return readerPointer->increment;
}

/*
***********************************************************
* Function name: readerGetMode
* Purpose: Returns the operational mode
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Operational mode.
*************************************************************
*/
i64 readerGetMode(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/*  Return mode */
	return readerPointer->mode;
}


/*
***********************************************************
* Function name: readerGetFlags
* Purpose: Returns the entire flags of Buffer.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Flags from Buffer.
*************************************************************
*/
bust_byte readerGetFlags(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/*  Return flags */
	return readerPointer->flags;
}



/*
***********************************************************
* Function name: readerPrintStat
* Purpose: Shows the char statistic.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value: (Void)
*************************************************************
*/
i64 readerPrintStat(ReaderPointer const readerPointer) {
	/*  Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	int count = 0;
	for (int i = 0; i < NCHAR; i++) {
		if (readerPointer->histogram[i] > 0) {
			count++;
		}
	}
	return count;
	/*  Print the histogram */
}

/*
***********************************************************
* Function name: readerNumErrors
* Purpose: Returns the number of errors found.
* Parameters:
*   readerPointer = pointer to Buffer Reader
* Return value:
*	Number of errors.
*************************************************************
*/
i64 readerNumErrors(ReaderPointer const readerPointer) {
	/* Defensive programming */
	if (!readerPointer) {
		return READER_ERROR;
	}
	/* Returns the number of errors */
	return readerPointer->numReaderErrors;
}

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
* File name: Compilers.h
* Date: May 01 2023
* Author: Boyu Li
* Purpose: This file defines the functions called by main function.
* Function list: mainReader(), mainScanner(), mainParser().
*************************************************************/

#ifndef COMPILERS_H_
#define COMPILERS_H_

#define DEBUG 0

/* Language name */
#define STR_LANGNAME	"Bust"

/* Logical constants - adapt for your language */
#define BUST_TRUE  1
#define BUST_FALSE 0

/*
------------------------------------------------------------
Data types definitions
NOTE: Some types may not be directly used by your language,
		but they can be necessary for conversions.
------------------------------------------------------------
*/

/* typedefs */
typedef char			bust_char;
typedef char*			String;
typedef int				i64;
typedef float			f64;
typedef void			bust_void;

typedef unsigned char	bool;
typedef unsigned char	bust_byte;

typedef long			bust_long;
typedef double			bust_doub;

/*
------------------------------------------------------------
Programs:
1: Reader - invokes MainReader code
2: Scanner - invokes MainScanner code
3: Parser - invokes MainParser code
------------------------------------------------------------
*/
enum PROGRAMS {
	PGM_READER	= 'R',
	PGM_SCANNER = 'S',
	PGM_PARSER	= 'P'
};

/*
------------------------------------------------------------
Main functions signatures
(Code will be updated during next assignments)
------------------------------------------------------------
*/
i64 mainReader(i64 argc, String* argv);
i64 mainScanner(i64 argc, String* argv);
i64 mainParser(i64 argc, String* argv);

bust_void printLogo();

#endif

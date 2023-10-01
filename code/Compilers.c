/*
************************************************************
* Code version: 3
* Author: Boyu Li
************************************************************
###################################################
#                                                 #
#    ALGONQUIN         @@@@@@@         COLLEGE    #
#                  @@-----------@@                #
#               @@@@|  M O L D  |@@@@             #
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
#  COMPILERS        @@@@@@@@@@@        2023-S     #
#                                                 #
###################################################
*/

/*
************************************************************
* File name: compilers.c
* Compiler: MS Visual Studio 2022
* Date: May 01 2023
* Purpose: This file is the main program of Compilers Project
* Function list: main().
************************************************************
*/


#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif


/*
***********************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver F22
* Called functions: mainReader(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
*************************************************************
*/

i64 main(int argc, char** argv) {
	i64 i;
	bust_char option;
	printLogo();
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%c%s%c%s%c%s", "OPTIONS:\n* [",
			PGM_READER, "] - Reader\n* [",
			PGM_SCANNER, "] - Scanner\n* [",
			PGM_PARSER, "] - Parser\n");
		return EXIT_FAILURE;
	}
	option = argv[1][0];
	switch (option) {
	case PGM_READER:
		printf("%s%c%s", "\n[Option '", PGM_READER, "': Starting READER .....]\n\n");
		mainReader(argc, argv);
		break;
	case PGM_SCANNER:
		printf("%s%c%s", "\n[Option '", PGM_SCANNER, "': Starting SCANNER ....]\n\n");
		mainScanner(argc, argv);
		break;
	case PGM_PARSER:
		printf("%s%c%s", "\n[Option '", PGM_PARSER, "': Starting PARSER .....]\n\n");
		mainParser(argc, argv);
		break;
	
	default:
		printf("%s%c%s%c%s%c%s", "* OPTIONS:\n- [",
			PGM_READER, "] - Reader\n- [",
			PGM_SCANNER, "] - Scanner\n- [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}

/*
***********************************************************
* Function name: printLogo
* Purpose: Print Logo
* History/Versions: Ver S23
* Called functions: -
* Parameters: -
* Return value: (Null)
* Algorithm: -
*************************************************************
*/
bust_void printLogo() {
	printf(
		"%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
		"\t###################################################\n",
		"\t#                                                 #\n",
		"\t#    BOYU              @@@@@@@         LI         #\n",
		"\t#                  @@-----------@@                #\n",
		"\t#               @@@@|  B U S T  |@@@@             #\n",
		"\t#            @@@@@@@@-----------@@@@@@@@          #\n",
		"\t#         @@@@@@@@@@@@@  @@@@@@@   @@@@@@@        #\n",
		"\t#       @@@@@@@@@@@@@      @@@       @@@@@@       #\n",
		"\t#     @@@@@@@    @@@@@    @@@@       @@@@@@@@     #\n",
		"\t#    @@@@@@@       @@@@@ @@@@@@@    @@@@@@@@@@    #\n",
		"\t#   @@@@@@@        @@@@@ @@@@@ @@@@@@    @@@@@@   #\n",
		"\t#  @@@@@@@@@@    @@             @@@@      @@@@@@  #\n",
		"\t#  @@@@@@@@@@@@@@@  @@@@@  @@@@  @@@@   @@    @@  #\n",
		"\t# @@@@@@@@@@@@@@@   @@@@@ @@@@@   @@@@@@@@@    @@ #\n",
		"\t# @@@@@      @@@@   @@@ @@@ @@@   @@@@    @@@@@@@ #\n",
		"\t# @@@@        @@@@  @@@ @@@ @@@   @@@      @@@@@@ #\n",
		"\t#  @@@@     @@@@@@@              @@@@@    @@@@@@  #\n",
		"\t#  @@@@@@@@@@@     @@@  @@@   @@@    @@@@@@@@@@   #\n",
		"\t#   @@@@@@@@@@@   @@@ @@@@@@ @@@@@    @@@@@@@@@   #\n",
		"\t#    @@@@@@@@@@@@@@@ @@@@@@    @@@@@@@@@@@@@@@    #\n",
		"\t#     @@@@@@@@@       @@@        @@@@@@@@@@@      #\n",
		"\t#       @@@@@@         @@         @@@@@@@@@       #\n",
		"\t#         @@@@@       @@@@@     @@@@@@@@@         #\n",
		"\t#            @@@@@@@@@@@@@@@@@@@@@@@@@            #\n",
		"\t#               @@@@@@@@@@@@@@@@@@@               #\n",
		"\t#  COMPILERS        @@@@@@@@@@@        BUST	     #\n",
		"\t#                                                 #\n",
		"\t###################################################\n"
	);
}

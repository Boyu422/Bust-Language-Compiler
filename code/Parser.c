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
* File name: Parser.c
* Compiler: MS Visual Studio 2022
* Date: Sep 01 2022
* Purpose: This file contains all functionalities from Parser.
* Function list: (...).
************************************************************
*/


#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/* Parser data */
extern ParserData psData; /* BNF statistics */

/*
************************************************************
 * Process Parser
 ***********************************************************
 */

bust_void startParser() {
	i64 i = 0;
	for (i = 0; i < NUM_BNF_RULES; i++) {
		psData.parsHistogram[i] = 0;
	}
	/* Proceed parser */
	lookahead = tokenizer();
	if (lookahead.code != SEOF_T) {
		program();
	}
	matchToken(SEOF_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}


/*
 ************************************************************
 * Match Token
 ***********************************************************
 */
bust_void matchToken(i64 tokenCode, i64 tokenAttribute) {
	i64 matchFlag = 1;
	switch (lookahead.code) {
	case KW_T:
		if (lookahead.attribute.codeType != tokenAttribute)
			matchFlag = 0;
	default:
		if (lookahead.code != tokenCode)
			matchFlag = 0;
	}
	if (matchFlag && lookahead.code == SEOF_T)
		return;
	if (matchFlag) {
		lookahead = tokenizer();
		if (lookahead.code == ERR_T) {
			printError();
			lookahead = tokenizer();
			syntaxErrorNumber++;
		}
	}
	else
		syncErrorHandler(tokenCode);
}

/*
 ************************************************************
 * Syncronize Error Handler
 ***********************************************************
 */
bust_void syncErrorHandler(i64 syncTokenCode) {
	printError();
	syntaxErrorNumber++;
	while (lookahead.code != syncTokenCode) {
		if (lookahead.code == SEOF_T)
			exit(syntaxErrorNumber);
		lookahead = tokenizer();
	}
	if (lookahead.code != SEOF_T)
		lookahead = tokenizer();
}

/*
 ************************************************************
 * Print Error
 ***********************************************************
 */
bust_void printError() {
	extern numParserErrors;			/* link to number of errors (defined in Parser.h) */
	Token t = lookahead;
	printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
	printf("*****  Token code:%3d Attribute: ", t.code);
	switch (t.code) {
	case ERR_T:
		printf("*ERROR*: %s\n", t.attribute.errLexeme);
		break;
	case SEOF_T:
		printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
		break;
	case MNID_T:
		printf("MNID_T:\t\t%s\t\n", t.attribute.idLexeme);
		break;
	case STR_T:
		printf("STR_T: %s\n", readerGetContent(stringLiteralTable, t.attribute.contentString));
		break;
	case KW_T:
		printf("KW_T: %s\n", keywordTable[t.attribute.codeType]);
		break;
	case LPR_T:
		printf("LPR_T\n");
		break;
	case RPR_T:
		printf("RPR_T\n");
		break;
	case LBR_T:
		printf("LBR_T\n");
		break;
	case RBR_T:
		printf("RBR_T\n");
		break;
	case EOS_T:
		printf("NA\n");
		break;
	default:
		printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
		numParserErrors++; // Updated parser error
	}
}

/*
 ************************************************************
 * Program statement
 * BNF: <program> -> main& { <opt_statements> }
 * FIRST(<program>)= {MNID_T (main&)}.
 ***********************************************************
 */
bust_void program() {
	/* Update program statistics */
	psData.parsHistogram[BNF_program]++;
	/* Program code */
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case KW_T:
		if (lookahead.attribute.codeType == KW_fn) {
			matchToken(KW_T, KW_fn);
			matchToken(MNID_T, NO_ATTR);
			printf("%s%s\n", STR_LANGNAME, ": Main Method parsed");
			parameterSession();
			codeSession();
			break;
		}
		else {
			printError();
		}
	case SEOF_T:
		; // Empty
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/*
 ************************************************************
 * comment
 * BNF: comment
 * FIRST(<comment>)= {CMT_T}.
 ***********************************************************
 */
bust_void comment() {
	psData.parsHistogram[BNF_comment]++;
	matchToken(CMT_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Comment parsed");
}

/*
 ************************************************************
 * dataSession
 * BNF: <dataSession> -> data { <opt_varlist_declarations> }
 * FIRST(<program>)= {KW_T (KW_data)}.
 ***********************************************************
 */

bust_void parameterSession() {
	psData.parsHistogram[BNF_dataSession]++;
	parameterVarListDeclarations();
	matchToken(RPR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Parameter Session parsed");
}

bust_void parameterVarListDeclarations() {
	switch (lookahead.code) {
	case VAR_T:
		varListDeclarations();
		datatypeDeclaration();
		break;
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Parameter Variable List Declarations parsed");
}

/*
 ************************************************************
 * codeSession statement
 * BNF: <codeSession> -> code { <opt_statements> }
 * FIRST(<codeSession>)= {KW_T (KW_code)}.
 ***********************************************************
 */
bust_void codeSession() {
	psData.parsHistogram[BNF_codeSession]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	default:
		matchToken(LBR_T, NO_ATTR);
		optionalStatements();
		matchToken(RBR_T, NO_ATTR);
		printf("%s%s\n", STR_LANGNAME, ": Code Session parsed");
	}
}


/*
 ************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *				KW_T(KW_while), MNID_T(print&), MNID_T(input&) }
 ***********************************************************
 */
bust_void optionalStatements() {
	psData.parsHistogram[BNF_optionalStatements]++;
	switch (lookahead.code) {
	case CMT_T:
		comment();
	case RBR_T:
		break;
	case VAR_T:
	case KW_T:
	case MNID_T:
		statements();
	default:
		; // Empty
	}
	printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*
 ************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if),
 *		KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
bust_void statements() {
	psData.parsHistogram[BNF_statements]++;
	statement();
	statementsPrime();
	printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*
 ************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T, 
 *		KW_T(KW_if), KW_T(KW_while), MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
bust_void statementsPrime() {
	psData.parsHistogram[BNF_statementsPrime]++;
	switch (lookahead.code) {
	case RBR_T:
		break;
	case MNID_T:
	case KW_T:
	case VAR_T:
		statements();
		break;
	default:
		; //empty string
	}
}

/*
 ************************************************************
 * Single statement
 * BNF: <statement> -> <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { IVID_T, FVID_T, SVID_T, KW_T(KW_if), KW_T(KW_while),
 *			MNID_T(input&), MNID_T(print&) }
 ***********************************************************
 */
bust_void statement() {
	psData.parsHistogram[BNF_statement]++;
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_let:
			matchToken(KW_T, KW_let);
			varListDeclarations();
			datatypeDeclaration();
			matchToken(EOS_T, NO_ATTR);
			break;
		case KW_while:
			matchToken(KW_T, KW_while);
			whileStatement();
			break;
		break;
		case KW_if:
			matchToken(KW_T, KW_if);
			ifStatement();
			break;
		break;
		default:
			printError();
		}
	case MNID_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_READ, 9) == 0) {
			inputStatement();
		}
		break;
	case VAR_T:
		if (strncmp(lookahead.attribute.idLexeme, LANG_WRTE, 5) == 0) {
			outputStatement();
		}
		else {
			varListDeclaration();
			matchToken(ASS_T, NO_ATTR);
			assignmentStatement();
			matchToken(EOS_T, NO_ATTR);
		}
		break;
	default:
		printError();
	}
	printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

bust_void assignmentStatement() {
	assignmentExpression();
	printf("%s%s\n", STR_LANGNAME, ": Assignment statement parsed");
}

bust_void assignmentExpression() {
	arithmeticExpression();
	printf("%s%s\n", STR_LANGNAME, ": Assignment expression parsed");
}

bust_void arithmeticExpression() {
	arithmeticExpressionDeclaration();
	arithmeticExpressionDeclarationPrime();
	printf("%s%s\n", STR_LANGNAME, ": Arithmetic expression parsed");
}

bust_void arithmeticExpressionDeclaration() {
	switch (lookahead.code)
	{
	case ARI_T:
		switch (lookahead.attribute.arithmeticOperator)
		{
		case OP_ADD:
			printf("%s%s\n", STR_LANGNAME, ": Additive expression parsed");
			break;
		case OP_SUB:
			printf("%s%s\n", STR_LANGNAME, ": Subtraction expression parsed");
			break;
		case OP_MUL:
			printf("%s%s\n", STR_LANGNAME, ": Multiplicative expression parsed");
			break;
		case OP_DIV:
			printf("%s%s\n", STR_LANGNAME, ": Division expression parsed");
			break;
		case OP_POW:
			printf("%s%s\n", STR_LANGNAME, ": Power expression parsed");
			break;
		}
		matchToken(ARI_T, NO_ATTR);
		break;
	default:
		;
	}
	switch (lookahead.code)
	{
	case VAR_T:
		varListDeclaration();
		break;
	case INL_T:
		IntListDeclaration();
		break;
	case FLL_T:
		FloatListDeclaration();
		break;
	case STR_T:
		StringListDeclaration();
		break;
	default:
		printError();
	}
}

bust_void arithmeticExpressionDeclarationPrime() {
	switch (lookahead.code)
	{
	case ARI_T:
		arithmeticExpression();
		printf("%s%s\n", STR_LANGNAME, ": Primary arithmetic expression parsed");
		break;
	default:
		;
	}
}

bust_void ifStatement() {
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case KW_true:
			printf("%s%s\n", STR_LANGNAME, ": True expression parsed");
			matchToken(KW_T, KW_true);
			break;
		case KW_false:
			printf("%s%s\n", STR_LANGNAME, ": False expression parsed");
			matchToken(KW_T, KW_false);
			break;
		default:
			printError();
		}
		break;
	default:
		logicalExpression();
	}
	codeSession();
	printf("%s%s\n", STR_LANGNAME, ": Then statement parsed");
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case KW_else:
			matchToken(KW_T, KW_else);
			codeSession();
			printf("%s%s\n", STR_LANGNAME, ": Else statement parsed");
			break;
		default:
			;
		}
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": If statement parsed");
}

bust_void whileStatement() {
	switch (lookahead.code)
	{
	case KW_T:
		switch (lookahead.attribute.codeType)
		{
		case KW_true:
			printf("%s%s\n", STR_LANGNAME, ": True expression parsed");
			matchToken(KW_T, KW_true);
			break;
		case KW_false:
			printf("%s%s\n", STR_LANGNAME, ": False expression parsed");
			matchToken(KW_T, KW_false);
			break;
		default:
			printError();
		}
		break;
	default:
		logicalExpression();
	}
	codeSession();
	printf("%s%s\n", STR_LANGNAME, ": While loop statement parsed");
}

bust_void logicalExpression() {
	logicalExpressionDeclaration();
	logicalExpressionDeclarationPrime();
	printf("%s%s\n", STR_LANGNAME, ": Logical expression parsed");
}

bust_void logicalExpressionDeclaration() {
	switch (lookahead.code)
	{
	case LOG_T:
		switch (lookahead.attribute.arithmeticOperator)
		{
		case OP_NOT:
			printf("%s%s\n", STR_LANGNAME, ": Not logical expression parsed");
			break;
		default:
			printError();
		}
		matchToken(LOG_T, NO_ATTR);
		break;
	default:
		;
	}

	conditionalExpression();
	printf("%s%s\n", STR_LANGNAME, ": Conditional expression parsed");

}

bust_void logicalExpressionDeclarationPrime() {
	switch (lookahead.code)
	{
	case LOG_T:
		switch (lookahead.attribute.arithmeticOperator)
		{
		case OP_AND:
			printf("%s%s\n", STR_LANGNAME, ": And logical expression parsed");
			matchToken(LOG_T, NO_ATTR);
			logicalExpression();
			break;
		case OP_OR:
			printf("%s%s\n", STR_LANGNAME, ": Or logical expression parsed");
			matchToken(LOG_T, NO_ATTR);
			logicalExpression();
			break;
		default:
			printError();
		}
		break;
	default:
		;
	}
}

bust_void conditionalExpression() {
	switch (lookahead.code)
	{
	case VAR_T:
		varListDeclaration();
		break;
	case INL_T:
		IntListDeclaration();
		break;
	case FLL_T:
		FloatListDeclaration();
		break;
	case STR_T:
		StringListDeclaration();
		break;
	default:
		printError();
	}

	switch (lookahead.code)
	{
	case REL_T:
		switch (lookahead.attribute.arithmeticOperator)
		{
		case OP_EQ:
			printf("%s%s\n", STR_LANGNAME, ": Equal conditional expression parsed");
			break;
		case OP_NE:
			printf("%s%s\n", STR_LANGNAME, ": Not equal conditional expression parsed");
			break;
		case OP_GT:
			printf("%s%s\n", STR_LANGNAME, ": Greater than conditional expression parsed");
			break;
		case OP_LT:
			printf("%s%s\n", STR_LANGNAME, ": Less than conditional expression parsed");
			break;
		}
		matchToken(REL_T, NO_ATTR);
		break;
	default:
		printError();
	}

	switch (lookahead.code)
	{
	case VAR_T:
		varListDeclaration();
		break;
	case INL_T:
		IntListDeclaration();
		break;
	case FLL_T:
		FloatListDeclaration();
		break;
	case STR_T:
		StringListDeclaration();
		break;
	default:
		printError();
	}

}

/*
 ************************************************************
 * Output Statement
 * BNF: <output statement> -> print& (<output statementPrime>);
 * FIRST(<output statement>) = { MNID_T(print&) }
 ***********************************************************
 */
bust_void outputStatement() {
	psData.parsHistogram[BNF_outputStatement]++;
	matchToken(VAR_T, NO_ATTR);
	matchToken(LOG_T, NO_ATTR);
	matchToken(LPR_T, NO_ATTR);
	outputVariableLists();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

bust_void outputVariableLists() {
	outputVariableList();
	outputVariableListPrime();
	printf("%s%s\n", STR_LANGNAME, ": Output variable lists parsed");
}



/*
 ************************************************************
 * Output Variable List
 * BNF: <opt_variable list> -> <variable list> | ϵ
 * FIRST(<opt_variable_list>) = { IVID_T, FVID_T, SVID_T, ϵ }
 ***********************************************************
 */
bust_void outputVariableList() {
	psData.parsHistogram[BNF_outputVariableList]++;
	switch (lookahead.code) {
	case STR_T:
		matchToken(STR_T, NO_ATTR);
		break;
	case VAR_T:
		matchToken(VAR_T, NO_ATTR);
		break;
	default:
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Output variable list parsed");
}

bust_void outputVariableListPrime() {
	switch (lookahead.code)
	{
		case CMT_T:
		matchToken(CMT_T, NO_ATTR);
		switch (lookahead.code)
		{
		case STR_T:
		case VAR_T:
			outputVariableLists();
			break;
		default:
			printError();
		}
		break;
	default:
		;
	}
}

bust_void inputStatement() {
	matchToken(MNID_T, NO_ATTR);
	inputVariableList();
	matchToken(RPR_T, NO_ATTR);
	matchToken(EOS_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}

bust_void inputVariableList() {
	switch (lookahead.code) {
	case VAR_T:
		varListDeclarations();
		break;
	default:
		printError();
		;
	}
	printf("%s%s\n", STR_LANGNAME, ": Input variable list parsed");
}

bust_void varListDeclarations() {
	varListDeclaration();
	varListDeclarationPrime();
	printf("%s%s\n", STR_LANGNAME, ": Variable List Declarations parsed");
}

bust_void varListDeclaration() {
	matchToken(VAR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Variable Identifier parsed");
	printf("%s%s\n", STR_LANGNAME, ": Variable List Declaration parsed");
}

bust_void varListDeclarationPrime() {
	switch (lookahead.code)
	{
	case CMT_T:
		matchToken(CMT_T, NO_ATTR);
		if (lookahead.code == VAR_T)
			varListDeclarations();
		else {
			printError();
		}
		break;
	default:
		;
	}
}

bust_void IntListDeclaration() {
	matchToken(INL_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Integer Identifier parsed");
}

bust_void FloatListDeclaration() {
	matchToken(FLL_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": Float Identifier parsed");
}

bust_void StringListDeclaration() {
	matchToken(STR_T, NO_ATTR);
	printf("%s%s\n", STR_LANGNAME, ": String Identifier parsed");
}

bust_void datatypeDeclaration() {
	matchToken(COL_T, NO_ATTR);
	switch (lookahead.code) {
	case KW_T:
		switch (lookahead.attribute.codeType) {
		case KW_i64:
			matchToken(KW_T, KW_i64);
			printf("%s%s\n", STR_LANGNAME, ": Int Variable List Declaration parsed");
			break;
		case KW_f64:
			matchToken(KW_T, KW_f64);
			printf("%s%s\n", STR_LANGNAME, ": Float Variable List Declaration parsed");
			break;
		case KW_bool:
			matchToken(KW_T, KW_bool);
			printf("%s%s\n", STR_LANGNAME, ": Boolean Variable List Declaration parsed");
			break;
		case KW_String:
			matchToken(KW_T, KW_String);
			printf("%s%s\n", STR_LANGNAME, ": String Variable List Declaration parsed");
			break;
		case KW_char:
			matchToken(KW_T, KW_char);
			printf("%s%s\n", STR_LANGNAME, ": Char Variable List Declaration parsed");
			break;
		case KW_NULL:
			matchToken(KW_T, KW_NULL);
			printf("%s%s\n", STR_LANGNAME, ": NULL Variable List Declaration parsed");
			break;
		default:
			printError();
		}
		break;
	default:
		printError();
	}
}

/*
 ************************************************************
 * The function prints statistics of BNF rules
 * Param:
 *	- Parser data
 * Return:
 *	- Void (procedure)
 ***********************************************************
 */
/*
bust_void printBNFData(ParserData psData) {
}
*/
bust_void printBNFData(ParserData psData) {
	/* Print Parser statistics */
	printf("Statistics:\n");
	printf("----------------------------------\n");
	int cont = 0;
	for (cont = 0; cont < NUM_BNF_RULES; cont++) {
		if (psData.parsHistogram[cont] > 0)
			printf("%s%s%s%d%s", "Token[", BNFStrTable[cont], "]=", psData.parsHistogram[cont], "\n");
	}
	printf("----------------------------------\n");
}

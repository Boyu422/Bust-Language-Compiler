:: COMPILERS COURSE - SCRIPT ---------------------------------------------
:: SCRIPT A12 - CST8152 - Winter 2023

CLS
SET COMPILER=Bust.exe

SET FILE0=INPUT0_Empty
SET FILE1=INPUT1_Hello
SET FILE2=INPUT2_Volume
SET FILE3=INPUT3_Factorial
SET FILE4=INPUT4_Datatypes
SET FILE5=INPUT5_General
SET FILE6=INPUT6_Err1Reader
SET FILE9=INPUT9_Big

SET ASSIGNMENT=A12
SET EXTENSION=bs
SET OUTPUT=out
SET ERROR=err

SET PARAM=R

:: ---------------------------------------------------------------------
:: Begin of Tests (A12 - W22) ------------------------------------------
:: ---------------------------------------------------------------------

@echo off

ECHO "                                                                       "
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "@@@@                                                               @@@@"
ECHO "@@          /       ==============================        /          @@"
ECHO "@         ////           @@       @@ #@                  ////         @"
ECHO "@         ////*          @@ @%  @ @@    @@  @ #@#       /////         @"
ECHO "@     ((( ////))))   @@  @% @%  @ @@ #@ @@  @ #@@#   ///////( ///     @"
ECHO "@     ((((,/ )))))    @@@@   @@@  @@ ##  @@@   #@#   ///// ,/////     @"
ECHO "@     (((((/)))((    ------------------------------    ((((./////*    @"
ECHO "@    //*./ /  .///   ---  PROGRAMMING LANGUAGE  ---  ////   / ( (//   @"
ECHO "@    ///// / /////   ==============================  * ////* / ////   @"
ECHO "@     ///// ///// ((                               (( ///// /////     @"
ECHO "@    ((((   / , (((((                             (((((  //   /(((    @"
ECHO "@    (((((((/ . (((((                          (((((* / (((((((       @"
ECHO "@      (((((( //((((/((((                    *((((/((((/( (((((/      @"
ECHO "@       .//,   * /   (((((                   (((((  ///    .//.       @"
ECHO "@     ,////////./(  (((((* ////         (///(((((( ,/(,////////       @"
ECHO "@         //////// ,// ((( /////,     ////// ((( //  /////// *        @"
ECHO "@            (((((((((,// * /////     /////   (//(((((((((            @"
ECHO "@            ((((((((((((/////         //.///  (((((((((((.           @"
ECHO "@                   (///////// //(   (//.//////////                   @"
ECHO "@                  (/////////             //////////                  @"
ECHO "@                                                                     @"
ECHO "@@          A L G O N Q U I N   C O L L E G E  -  2 0 2 3 W          @@"
ECHO "@@@@                                                               @@@@"
ECHO "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
ECHO "                                                                       "
ECHO "[READER SCRIPT .......................................................]"
ECHO "                                                                       "

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
:: Basic Tests (A12 - W22) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% %PARAM% %FILE0%.%EXTENSION%	> %FILE0%-%ASSIGNMENT%.%OUTPUT%	2> %FILE0%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE1%.%EXTENSION%	> %FILE1%-%ASSIGNMENT%.%OUTPUT%	2> %FILE1%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE2%.%EXTENSION%	> %FILE2%-%ASSIGNMENT%.%OUTPUT%	2> %FILE2%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE3%.%EXTENSION%	> %FILE3%-%ASSIGNMENT%.%OUTPUT%	2> %FILE3%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE4%.%EXTENSION%	> %FILE4%-%ASSIGNMENT%.%OUTPUT%	2> %FILE4%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE5%.%EXTENSION%	> %FILE5%-%ASSIGNMENT%.%OUTPUT%	2> %FILE5%-%ASSIGNMENT%.%ERROR%
%COMPILER% %PARAM% %FILE6%.%EXTENSION%	> %FILE6%-%ASSIGNMENT%.%OUTPUT%	2> %FILE6%-%ASSIGNMENT%.%ERROR%

::
:: ADVANCED TESTS  -------------------------------------------------------
::
:: Advanced Tests (A12 - W22) - - - - - - - - -- - - - - - - - - - - -

%COMPILER% %PARAM% %FILE9%.%EXTENSION%	F 100 10	> %FILE9%-%ASSIGNMENT%-f-100-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-f-100-10.%ERROR%
%COMPILER% %PARAM% %FILE9%.%EXTENSION%	A 100 10	> %FILE9%-%ASSIGNMENT%-a-100-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-a-100-10.%ERROR%
%COMPILER% %PARAM% %FILE9%.%EXTENSION%	M 100 10	> %FILE9%-%ASSIGNMENT%-m-100-10.%OUTPUT%	2> %FILE9%-%ASSIGNMENT%-m-100-10.%ERROR%

:: SHOW OUTPUTS - - - - - - - - - - - - - - - - - - - - - - - - - - -
DIR *.OUT
DIR *.ERR

:: ---------------------------------------------------------------------
:: End of Tests (A12 - W22) --------------------------------------------
:: ---------------------------------------------------------------------

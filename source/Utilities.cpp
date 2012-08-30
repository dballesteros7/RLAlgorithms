/*

** FILE: Utilities.cpp

**

** ABSTRACT:

**   A general description of the module's role in the

**   overall software architecture,  What services it 

**   provides and how it interacts with other components.

**

** DOCUMENTS:

**   A reference to the applicable design documents.

**

** AUTHOR:

**   Diego A. Ballesteros Villamizar

**

** CREATION DATE:

**   09/10/2011

**

** NOTES:

**   Other relevant information

*/


// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#include "Utilities.h"

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Functions
// ----------------------------------------------------------------------------

int RLAlgorithmsLib::fexist( char *filename ) {
  struct stat buffer ;
  if ( stat( filename, &buffer ) ) return 0 ;
  return 1;
}


STR2NUMBER_ERROR RLAlgorithmsLib::str2int(int &i, char const *s, int base){
    char *end;
    long  l;
    errno = 0;
    l = strtol(s, &end, base);
    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
		return NOVERFLOW;
    }
	if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
        return NUNDERFLOW;
    }
    if (*s == '\0' || *end != '\0') {
        return NAN;
    }
    i = l;
    return SUCCESS;
}

STR2NUMBER_ERROR RLAlgorithmsLib::str2double (double &i, char const *s){
	char *end;
	double d;
	errno = 0;
	d = strtod(s,&end);
	if((errno == ERANGE && d != 0) || d > INT_MAX){
		return NOVERFLOW;
	}
	if((errno == ERANGE && d == 0) || d < INT_MIN){
		return NUNDERFLOW;
	}
	if (*s == '\0' || *end != '\0') {
        return NAN;
    }
	i = d;
	return SUCCESS;
}

int RLAlgorithmsLib::getRandomIndex(int optionsNumber){
	int coin = rand();
	int accum = RAND_MAX/optionsNumber;
	for(int i = 0; i < optionsNumber; i++){
		if(coin < accum){
			return i;
		}
		accum += RAND_MAX/optionsNumber;
	}
	return 0;
}

bool RLAlgorithmsLib::rollBinaryDice(double p){
	int coin = rand();
	return (coin <= RAND_MAX*p);
}
/*

** FILE: Utilities.h

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

#ifndef UTILITIES_H
#define UTILITIES_H

#include <errno.h>
#include <sys/stat.h>
#include <string>
#include <math.h>
#include <iostream>
#include <time.h>

using namespace std;

// -------------------------------------------------------------------------------
// Enumerations
// -------------------------------------------------------------------------------
namespace RLAlgorithmsLib{

	enum STR2NUMBER_ERROR{SUCCESS,NOVERFLOW,NUNDERFLOW,NAN};

}

// -------------------------------------------------------------------------------
// Functions
// -------------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	int fexist( char *filename );
	STR2NUMBER_ERROR str2double (double &i, char const *s);
	STR2NUMBER_ERROR str2int (int &i, char const *s, int base = 0);
	int getRandomIndex(int optionsNumber);
	bool rollBinaryDice(double p);
}

#endif //UTILITIES_H

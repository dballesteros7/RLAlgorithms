/*

** FILE: State.h

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

**   04/10/2011

**

** NOTES:

**   Other relevant information

*/

// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#ifndef STATE_H
#define STATE_H

#include "Strings.h"

#include <iostream>
using namespace std;

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	class State {
		protected:
			string stateID;
			int stateIndex;
		public:			
			virtual string getID() const =0;
			virtual int getIndex() const =0;
	};
}

#endif //STATE_H
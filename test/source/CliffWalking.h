/*

** FILE: CliffWalking.h

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

**   17/10/2011

**

** NOTES:

**   Other relevant information

*/

// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#include <string>
#pragma once

using namespace std;

// ----------------------------------------------------------------------------
// Definitions
// ----------------------------------------------------------------------------

namespace CliffWalking{

	const int x_start = 0;
	const int y_start = 0;
	const int x_goal = 11;
	const int y_goal = 0;
	const int x_size = 12;
	const int y_size = 4;
	void initializeWorld(int &x_pos, int &y_pos);
	void moveInWorld(int &x_pos, int &y_pos, bool &goalReached, double &reward, const string &action);
}
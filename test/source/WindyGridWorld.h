/*

** FILE: WindyGridWorld.h

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

namespace WindyGridWorld{

	const int x_start = 0;
	const int y_start = 3;
	const int x_goal = 7;
	const int y_goal = 3;
	const int windPattern [] = {0,0,0,1,1,1,2,2,1,0};
	const int x_size = 10;
	const int y_size = 7;
	void initializeWorld(int &x_pos, int &y_pos);
	void moveInWorld(int &x_pos, int &y_pos, bool &goalReached, double &reward, const string &action);

}
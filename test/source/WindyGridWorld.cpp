/*

** FILE: WindyGridWorld.cpp

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

#include "WindyGridWorld.h"

using namespace WindyGridWorld;

// ----------------------------------------------------------------------------
// Functions
// ----------------------------------------------------------------------------

void WindyGridWorld::initializeWorld(int &x_pos, int &y_pos){
	x_pos = x_start;
	y_pos = y_start; 
}


void WindyGridWorld::moveInWorld(int &x_pos, int &y_pos, bool &goalReached, double &reward, const std::string &action){
	y_pos += windPattern[x_pos];

	if(action == "UP")
		y_pos += 1;
	else if(action == "DOWN")
		y_pos -= 1;
	else if(action == "LEFT")
		x_pos -= 1;
	else if(action == "RIGHT")
		x_pos += 1;

	if(x_pos > 9)
		x_pos = 9;
	else if(x_pos < 0)
		x_pos = 0;

	if(y_pos > 6)
		y_pos = 6;
	else if(y_pos < 0)
		y_pos = 0;

	if(x_pos == x_goal && y_pos == y_goal){
		goalReached = true;
		reward = 0.0;
	}
	else
		reward = -1.0;
}
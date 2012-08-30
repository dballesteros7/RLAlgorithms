/*

** FILE: Action.cpp

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

**   06/10/2011

**

** NOTES:

**   Other relevant information

*/

// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#include <Action.h>

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------------------------

Action::Action(string nID, int nActionIndex){
	actionID = nID;
	actionIndex = nActionIndex;
}

Action::~Action(){
	actionID = "";
	actionIndex = 0;
}

// ----------------------------------------------------------------------------
// Public Methods
// ----------------------------------------------------------------------------

string Action::getID() const{
	return actionID;
}

int Action::getIndex() const{
	return actionIndex;
}

void Action::changeIndex(int newIndex){
	actionIndex = newIndex;
}

// ----------------------------------------------------------------------------
// Static Methods
// ----------------------------------------------------------------------------

bool Action::compareActions(const Action &x, const Action &y){
	return (x.getIndex() < y.getIndex());
}

bool Action::compareActionsPtr(Action *x, Action *y){
	return (x->getIndex() < y->getIndex());
}

bool Action::compareActionsByID(const RLAlgorithmsLib::Action &x, const RLAlgorithmsLib::Action &y){
	return (x.getID() < y.getID());
}

bool Action::compareActionsByIDPtr(Action *x, Action *y){
	return (x->getID() < y->getID());
}

bool Action::equals(const Action &x, const Action &y){
	return (x.getID() == y.getID());
}

bool Action::equalsPtr(Action *x, Action *y){
	return (x == y || x->getID() == y->getID());
}
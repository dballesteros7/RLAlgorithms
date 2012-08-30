/*

** FILE: StateActionPair.cpp

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

#include "StateActionPair.h"

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------------------------

StateWithFeaturesActionPair::StateWithFeaturesActionPair(StateWithFeatures* nState, Action* nAction, int nActionNumber){
	state = nState;
	action = nAction;
	actionNumber = nActionNumber;
	generateID();
	calculateIndex();
}

StateWithFeaturesActionPair::~StateWithFeaturesActionPair(){
	delete state;
	delete action;
}

// ----------------------------------------------------------------------------
// Public Methods
// ----------------------------------------------------------------------------

int StateWithFeaturesActionPair::getIndex() const{
	return stateActionPairIndex;
}

string StateWithFeaturesActionPair::getID() const{
	return stateActionPairID;
}

Action* StateWithFeaturesActionPair::getAction() const{
	return action;
}

State* StateWithFeaturesActionPair::getState() const{
	return state;
}

// ----------------------------------------------------------------------------
// Static Methods
// ----------------------------------------------------------------------------

bool StateWithFeaturesActionPair::compareStateWithFeaturesActionPair(
	const RLAlgorithmsLib::StateWithFeaturesActionPair &x, const RLAlgorithmsLib::StateWithFeaturesActionPair &y){
	return (x.getIndex() < y.getIndex());
}

bool StateWithFeaturesActionPair::compareStateWithFeaturesActionPairPtr(
	RLAlgorithmsLib::StateWithFeaturesActionPair *x, RLAlgorithmsLib::StateWithFeaturesActionPair *y){
	return (x->getIndex() < y->getIndex());
}

// ----------------------------------------------------------------------------
// Private Methods
// ----------------------------------------------------------------------------

void StateWithFeaturesActionPair::calculateIndex(){
	stateActionPairIndex = actionNumber*state->getIndex() + action->getIndex();
}

void StateWithFeaturesActionPair::generateID(){
	stateActionPairID = state->getID() + " " + SEPARATOR_CHARACTER + " " + action->getID();
}
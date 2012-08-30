/*

** FILE: StateActionPair.h

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

#ifndef STATE_ACTION_PAIR_H
#define STATE_ACTION_PAIR_H

#include "StateWithFeatures.h"
#include "Action.h"

using namespace std;

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	class StateActionPair{
	protected:
		string stateActionPairID;
		int stateActionPairIndex;
	public:
		virtual int getIndex() const =0;
		virtual string getID() const =0;
		virtual State *getState() const =0;
		virtual Action *getAction() const =0;
	};

	class StateWithFeaturesActionPair : public StateActionPair{
	private:
		StateWithFeatures *state;
		Action *action;
		int actionNumber;
	public:
		StateWithFeaturesActionPair(StateWithFeatures *nState, Action *nAction, int nActionNumber);
		~StateWithFeaturesActionPair();
		int getIndex() const;
		string getID() const;
		Action* getAction() const;
		State* getState() const;
		static bool compareStateWithFeaturesActionPair(const StateWithFeaturesActionPair &x, const StateWithFeaturesActionPair &y);
		static bool compareStateWithFeaturesActionPairPtr(StateWithFeaturesActionPair* x, StateWithFeaturesActionPair* y);
	private:
		void calculateIndex();
		void generateID();
	};

}

#endif //STATE_ACTION_PAIR_H
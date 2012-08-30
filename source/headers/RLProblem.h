/*

** FILE: RLProblem.h

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

#ifndef RL_PROBLEM_H
#define RL_PROBLEM_H

#include "StateActionPair.h"
#include "Utilities.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>

using namespace std;

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	class RLProblem{
	public:
		enum PROBLEM_TYPE {STATES_WITH_FEATURES = 1, STATES_WITHOUT_FEATURES};
	private:
		StateActionPair **stateActionPairs;
		int stateSpaceSize;
		int actionNumber;
		PROBLEM_TYPE problemType;
	public:
		RLProblem(list<StateWithFeatures*> states, list<Action*> actions);
		RLProblem(ifstream *problemDescriptionFile);
		~RLProblem();
		StateActionPair** getStateActionPairs() const;
		Action** getActions() const;
		StateWithFeatures** getStatesWithFeatures() const;
		int getStateSpaceSize() const;
		int getActionNumber() const;
		PROBLEM_TYPE getProblemType() const;
		int getStateActionPairsNumber() const;
		int getStateActionPairIndex(string stateID, const Action &action) const;
		int getStateActionPairIndex(string stateID, string actionID) const;
		int getStateActionPairIndex(const StateWithFeatures &state, const Action &action) const;
		int getStateActionPairIndex(const StateWithFeatures &state, string actionID) const;
		int getStateActionPairIndex(const list<string> &featuresID, const list<int> &values, string actionID) const;
		int getStateBaseIndex(string stateID) const;
		int getStateBaseIndex(const StateWithFeatures &state) const;
		int getStateBaseIndex(const list<string> &featuresID, const list<int> &values) const;
		string getActionID(int actionIndex) const;
		string getStateIDFromBaseIndex(int stateBaseIndex) const;
		string getStateIDFromStateIndex(int stateIndex) const;
		void saveProblemDescription(ofstream &problemDescriptionFile);
	private:
		void processProblemDescriptionFileWithFeatures(ifstream *problemDescriptionFile);
		void processActionsTag(ifstream *problemDescriptionFile, string &line, list<Action*> &actions);
		void processFeaturesTag(ifstream *problemDescriptionFile, string &line, list<Feature*> &features);
		void generateStatesWithFeatures(list<Feature*> &features, list<StateWithFeatures*> &states);
		void generateStateActionPairs(list<StateWithFeatures*> &states, list<Action*> &actions);
		void orderActions(list<Action*> &actions);
		StateWithFeatures *getState(const list<string> &featuresID, const list<int> &values) const;
	};

}

#endif //RL_PROBLEM_H


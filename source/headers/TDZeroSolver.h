/*

** FILE: TDZeroSolver.h

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

**   16/10/2011

**

** NOTES:

**   Other relevant information

*/

// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#ifndef TD_ZERO_SOLVER_H
#define TD_ZERO_SOLVER_H

#include "RLProblem.h"

#include <time.h>
#include <list>

using namespace std;

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	class TDZeroSolver{
	protected:
		RLProblem *problemDescription;
		double *qValues;
		double epsilon;
		double gamma;
		double alpha;
	public:
		string getActionAccordingToPolicy(string stateID) const;
		string getActionAccordingToPolicy(const list<Feature*> &stateFeatures, const list<int> &featuresValues) const;
		string getActionAccordingToPolicy(const list<string> &stateFeaturesID, const list<int> &featuresValues) const;
		list<StateActionPair*> getGreedyPolicy() const;
		virtual void processStateTransition(string initialStateID, string finalStateID, string actionID, double reward) =0;
		virtual void processStateTransition(const list<string> &initialStateFeaturesID, const list<int> &initialFeaturesValues,
			const list<string> &finalStateFeaturesID, const list<int> &finalFeaturesValues, string actionID, double reward) =0;
		virtual void processStateTransition(const list<Feature*> &initialStateFeatures, const list<int> &initialFeaturesValues,
			const list<Feature*> &finalStateFeatures, const list<int> &finalFeaturesValues, string actionID, double reward) =0;
		void saveQValuesFile(ofstream &qValuesFile);
		void savePolicyToFile(ofstream &policyFile);
	protected:
		string getActionAccordingToPolicy(int stateBaseIndex) const;
		int getActionIndexAccordingToPolicy(int stateBaseIndex) const;
		string getGreedyActionAccordingToPolicy(int stateBaseIndex) const;
		int getGreedyActionIndexAccordingToPolicy(int stateBaseIndex) const;
		void processQValuesFile(ifstream &qValuesFile);
	};

}

#endif //TD_ZERO_SOLVER_H
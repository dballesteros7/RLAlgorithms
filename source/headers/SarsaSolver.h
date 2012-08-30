/*

** FILE: Sarsa.h

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

#ifndef SARSA_SOLVER_H
#define SARSA_SOLVER_H

#include "TDZeroSolver.h"

using namespace std;

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	class SarsaSolver : public TDZeroSolver{
	private:
		int nextActionIndex;
		int nextStateBaseIndex;
	public:
		SarsaSolver(RLProblem *nProblemDescription, 
			double nEpsilon = 0.1, double nGamma = 1, double nAlpha = 0.1);
		SarsaSolver(RLProblem *nProblemDescription, double *nQValues, 
			double nEpsilon = 0.1, double nGamma = 1, double nAlpha = 0.1);
		SarsaSolver(RLProblem *nProblemDescription, ifstream &qValuesFile, 
			double nEpsilon = 0.1, double nGamma = 1, double nAlpha = 0.1);
		~SarsaSolver();
		string getActionAccordingToPolicy(string stateID) const;
		string getActionAccordingToPolicy(const list<Feature*> &stateFeatures, const list<int> &featuresValues) const;
		string getActionAccordingToPolicy(const list<string> &stateFeaturesID, const list<int> &featuresValues) const;
		void processStateTransition(string initialStateID, string finalStateID, string actionID, double reward);
		void processStateTransition(const list<string> &initialStateFeaturesID, const list<int> &initialFeaturesValues,
			const list<string> &finalStateFeaturesID, const list<int> &finalFeaturesValues, string actionID, double reward);
		void processStateTransition(const list<Feature*> &initialStateFeatures, const list<int> &initialFeaturesValues,
			const list<Feature*> &finalStateFeatures, const list<int> &finalFeaturesValues, string actionID, double reward);
	};
}

#endif //SARSA_SOLVER_H
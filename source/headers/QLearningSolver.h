/*

** FILE: QLearningSolver.h

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

**   10/10/2011

**

** NOTES:

**   Other relevant information

*/

// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#ifndef Q_LEARNING_SOLVER_H
#define Q_LEARNING_SOLVER_H

#include "TDZeroSolver.h"

using namespace std;

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	class QLearningSolver : public TDZeroSolver{
	public:
		QLearningSolver(RLProblem *nProblemDescription, 
			double nEpsilon = 0.1, double nGamma = 1, double nAlpha = 0.1);
		QLearningSolver(RLProblem *nProblemDescription, double *nQValues, 
			double nEpsilon = 0.1, double nGamma = 1, double nAlpha = 0.1);
		QLearningSolver(RLProblem *nProblemDescription, ifstream &qValuesFile, 
			double nEpsilon = 0.1, double nGamma = 1, double nAlpha = 0.1);
		~QLearningSolver();
		void processStateTransition(string initialStateID, string finalStateID, string actionID, double reward);
		void processStateTransition(const list<string> &initialStateFeaturesID, const list<int> &initialFeaturesValues,
			const list<string> &finalStateFeaturesID, const list<int> &finalFeaturesValues, string actionID, double reward);
		void processStateTransition(const list<Feature*> &initialStateFeatures, const list<int> &initialFeaturesValues,
			const list<Feature*> &finalStateFeatures, const list<int> &finalFeaturesValues, string actionID, double reward);
	};
}

#endif //Q_LEARNING_SOLVER_H
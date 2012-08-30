/*

** FILE: QLearningSolver.cpp

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

#include "QLearningSolver.h"

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------------------------

QLearningSolver::QLearningSolver(RLAlgorithmsLib::RLProblem *nProblemDescription, double nEpsilon, double nGamma, double nAlpha){
	problemDescription = nProblemDescription;
	epsilon = nEpsilon;
	gamma = nGamma;
	alpha = nAlpha;
	qValues = new double[problemDescription->getStateActionPairsNumber()];
	for(int i = 0; i < problemDescription->getStateActionPairsNumber(); i++){
		qValues[i] = 0.0;
	}
	srand((unsigned int)time(0));
}

QLearningSolver::QLearningSolver(RLAlgorithmsLib::RLProblem *nProblemDescription, double *nQValues, 
								 double nEpsilon, double nGamma, double nAlpha){
	problemDescription = nProblemDescription;
	epsilon = nEpsilon;
	gamma = nGamma;
	alpha = nAlpha;
	qValues = nQValues;
	srand((unsigned int)time(0));
}

QLearningSolver::QLearningSolver(RLAlgorithmsLib::RLProblem *nProblemDescription, 
								 std::ifstream &qValuesFile, double nEpsilon, double nGamma, double nAlpha){
	problemDescription = nProblemDescription;	
	epsilon = nEpsilon;
	gamma = nGamma;
	alpha = nAlpha;
	processQValuesFile(qValuesFile);
	srand((unsigned int)time(0));
}

QLearningSolver::~QLearningSolver(){
	delete problemDescription;
	//delete[] qValues;
}

// ----------------------------------------------------------------------------
// Public Methods
// ----------------------------------------------------------------------------

void QLearningSolver::processStateTransition(std::string initialStateID, std::string finalStateID, std::string actionID, double reward){
	int qValueIndex = problemDescription->getStateActionPairIndex(initialStateID,actionID);
	int nextStateBaseIndex = problemDescription->getStateBaseIndex(finalStateID);
	int nextGreedyActionIndex = getGreedyActionIndexAccordingToPolicy(nextStateBaseIndex);
	qValues[qValueIndex] += alpha*(reward + gamma*qValues[nextStateBaseIndex + nextGreedyActionIndex] - qValues[qValueIndex]);
}

void QLearningSolver::processStateTransition(const std::list<string> &initialStateFeaturesID, const std::list<int> &initialFeaturesValues, 
											 const std::list<string> &finalStateFeaturesID, const std::list<int> &finalFeaturesValues, 
											 std::string actionID, double reward){
	int qValueIndex = problemDescription->getStateActionPairIndex(initialStateFeaturesID, initialFeaturesValues, actionID);
	int nextStateBaseIndex = problemDescription->getStateBaseIndex(finalStateFeaturesID, finalFeaturesValues);
	int nextGreedyActionIndex = getGreedyActionIndexAccordingToPolicy(nextStateBaseIndex);
	qValues[qValueIndex] += alpha*(reward + gamma*qValues[nextStateBaseIndex + nextGreedyActionIndex] - qValues[qValueIndex]);
}

void QLearningSolver::processStateTransition(const std::list<Feature*> &initialStateFeatures, const std::list<int> &initialFeaturesValues, 
											 const  std::list<Feature*> &finalStateFeatures, const std::list<int> &finalFeaturesValues, 
											 std::string actionID, double reward){
	StateWithFeatures *initialState = new StateWithFeatures(initialStateFeatures, initialFeaturesValues);
	StateWithFeatures *finalState = new StateWithFeatures(finalStateFeatures, finalFeaturesValues);
	int qValueIndex = problemDescription->getStateActionPairIndex(*initialState, actionID);
	int nextStateBaseIndex = problemDescription->getStateBaseIndex(*finalState);
	int nextGreedyActionIndex = getGreedyActionIndexAccordingToPolicy(nextStateBaseIndex);
	qValues[qValueIndex] += alpha*(reward + gamma*qValues[nextStateBaseIndex + nextGreedyActionIndex] - qValues[qValueIndex]);
}

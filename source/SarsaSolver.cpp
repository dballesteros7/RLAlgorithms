/*

** FILE: SarsaSolver.cpp

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

#include "SarsaSolver.h"

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------------------------

SarsaSolver::SarsaSolver(RLAlgorithmsLib::RLProblem *nProblemDescription, double nEpsilon, double nGamma, double nAlpha){
	problemDescription = nProblemDescription;
	epsilon = nEpsilon;
	gamma = nGamma;
	alpha = nAlpha;
	qValues = new double[problemDescription->getStateActionPairsNumber()];
	nextActionIndex = -1;
	nextStateBaseIndex = -1;
	for(int i = 0; i < problemDescription->getStateActionPairsNumber(); i++){
		qValues[i] = 0.0;
	}
	srand((unsigned int)time(0));
}

SarsaSolver::SarsaSolver(RLAlgorithmsLib::RLProblem *nProblemDescription, double *nQValues, 
								 double nEpsilon, double nGamma, double nAlpha){
	problemDescription = nProblemDescription;
	epsilon = nEpsilon;
	gamma = nGamma;
	alpha = nAlpha;
	qValues = nQValues;
	nextActionIndex = -1;
	nextStateBaseIndex = -1;
	srand((unsigned int)time(0));
}

SarsaSolver::SarsaSolver(RLAlgorithmsLib::RLProblem *nProblemDescription, 
								 std::ifstream &qValuesFile, double nEpsilon, double nGamma, double nAlpha){
	problemDescription = nProblemDescription;	
	epsilon = nEpsilon;
	gamma = nGamma;
	alpha = nAlpha;
	processQValuesFile(qValuesFile);
	nextActionIndex = -1;
	nextStateBaseIndex = -1;
	srand((unsigned int)time(0));
}

SarsaSolver::~SarsaSolver(){
	delete problemDescription;
	delete[] qValues;
}

// ----------------------------------------------------------------------------
// Public Methods
// ----------------------------------------------------------------------------

string SarsaSolver::getActionAccordingToPolicy(std::string stateID) const{
	if(nextActionIndex == -1 || nextStateBaseIndex == -1)
		return TDZeroSolver::getActionAccordingToPolicy(stateID);
	int tmpStateBaseIndex = problemDescription->getStateBaseIndex(stateID);
	if(tmpStateBaseIndex != nextStateBaseIndex)
		return problemDescription->getActionID(getActionIndexAccordingToPolicy(tmpStateBaseIndex));
	else
		return problemDescription->getActionID(nextActionIndex);
	
}

string SarsaSolver::getActionAccordingToPolicy(const std::list<string> &stateFeaturesID, const std::list<int> &featuresValues) const{
	if(nextActionIndex == -1 || nextStateBaseIndex == -1)
		return TDZeroSolver::getActionAccordingToPolicy(stateFeaturesID, featuresValues);
	int tmpStateBaseIndex = problemDescription->getStateBaseIndex(stateFeaturesID, featuresValues);
	if(tmpStateBaseIndex != nextStateBaseIndex)
		return problemDescription->getActionID(getActionIndexAccordingToPolicy(tmpStateBaseIndex));
	else
		return problemDescription->getActionID(nextActionIndex);
}

string SarsaSolver::getActionAccordingToPolicy(const std::list<Feature*> &stateFeatures, const std::list<int> &featuresValues) const{
	if(nextActionIndex == -1 || nextStateBaseIndex == -1)
		return TDZeroSolver::getActionAccordingToPolicy(stateFeatures, featuresValues);
	StateWithFeatures tmpState(stateFeatures, featuresValues);
	int tmpStateBaseIndex = problemDescription->getStateBaseIndex(tmpState);
	if(tmpStateBaseIndex != nextStateBaseIndex)
		return problemDescription->getActionID(getActionIndexAccordingToPolicy(tmpStateBaseIndex));
	else
		return problemDescription->getActionID(nextActionIndex);
}

void SarsaSolver::processStateTransition(std::string initialStateID, std::string finalStateID, std::string actionID, double reward){
	int qValueIndex = problemDescription->getStateActionPairIndex(initialStateID,actionID);
	nextStateBaseIndex = problemDescription->getStateBaseIndex(finalStateID);
	nextActionIndex = getActionIndexAccordingToPolicy(nextStateBaseIndex);
	qValues[qValueIndex] += alpha*(reward + gamma*qValues[nextStateBaseIndex + nextActionIndex] - qValues[qValueIndex]);
}

void SarsaSolver::processStateTransition(const std::list<string> &initialStateFeaturesID, const std::list<int> &initialFeaturesValues, 
											 const std::list<string> &finalStateFeaturesID, const std::list<int> &finalFeaturesValues, 
											 std::string actionID, double reward){
	int qValueIndex = problemDescription->getStateActionPairIndex(initialStateFeaturesID, initialFeaturesValues, actionID);
	nextStateBaseIndex = problemDescription->getStateBaseIndex(finalStateFeaturesID, finalFeaturesValues);
	nextActionIndex = getActionIndexAccordingToPolicy(nextStateBaseIndex);
	qValues[qValueIndex] += alpha*(reward + gamma*qValues[nextStateBaseIndex + nextActionIndex] - qValues[qValueIndex]);
}

void SarsaSolver::processStateTransition(const std::list<Feature*> &initialStateFeatures, const std::list<int> &initialFeaturesValues, 
											 const  std::list<Feature*> &finalStateFeatures, const std::list<int> &finalFeaturesValues, 
											 std::string actionID, double reward){
	StateWithFeatures *initialState = new StateWithFeatures(initialStateFeatures, initialFeaturesValues);
	StateWithFeatures *finalState = new StateWithFeatures(finalStateFeatures, finalFeaturesValues);
	int qValueIndex = problemDescription->getStateActionPairIndex(*initialState, actionID);
	nextStateBaseIndex = problemDescription->getStateBaseIndex(*finalState);
	nextActionIndex = getActionIndexAccordingToPolicy(nextStateBaseIndex);
	qValues[qValueIndex] += alpha*(reward + gamma*qValues[nextStateBaseIndex + nextActionIndex] - qValues[qValueIndex]);
}
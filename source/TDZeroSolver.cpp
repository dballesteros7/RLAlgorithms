/*

** FILE: TDZeroSolver.cpp

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

#include "TDZeroSolver.h"

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Public Methods
// ----------------------------------------------------------------------------

string TDZeroSolver::getActionAccordingToPolicy(std::string stateID) const{
	int baseIndex = problemDescription->getStateBaseIndex(stateID);
	return getActionAccordingToPolicy(baseIndex);
}

string TDZeroSolver::getActionAccordingToPolicy(const std::list<string> &stateFeaturesID, const std::list<int> &featuresValues) const{
	int baseIndex = problemDescription->getStateBaseIndex(stateFeaturesID, featuresValues);
	return getActionAccordingToPolicy(baseIndex);
}

string TDZeroSolver::getActionAccordingToPolicy(const std::list<Feature*> &stateFeatures, const std::list<int> &featuresValues) const{
	StateWithFeatures *tmpState = new StateWithFeatures(stateFeatures, featuresValues);
	int baseIndex = problemDescription->getStateBaseIndex(*tmpState);
	return getActionAccordingToPolicy(baseIndex);
}

list<StateActionPair*> TDZeroSolver::getGreedyPolicy() const{
	list<StateActionPair*> policy;
	StateActionPair** stateActions = problemDescription->getStateActionPairs();
	int n = problemDescription->getStateActionPairsNumber();
	int actionNumber = problemDescription->getActionNumber();
	for(int i = 0; i < n; i += actionNumber){
		int greedyAction = getGreedyActionIndexAccordingToPolicy(i);
		policy.push_back(stateActions[i + greedyAction]);
	}
	return policy;
}

void TDZeroSolver::saveQValuesFile(std::ofstream &qValuesFile){
	if(!qValuesFile.is_open())
		throw new exception(FILE_NOT_OPEN.c_str());
	qValuesFile << COMMENT_CHARACTER << AUTOMATICALLY_GENERATED_FILE << endl;
	qValuesFile << COMMENT_CHARACTER << QVALUES_FILE << endl;
	int type = problemDescription->getProblemType();
	qValuesFile << TYPE_TAG << ASSIGNATION_CHARACTER << type << endl;
	qValuesFile << QVALUES_TAG << endl;
	int n = problemDescription->getStateActionPairsNumber();
	StateActionPair **stateActions = problemDescription->getStateActionPairs();
	for(int i = 0; i < n; i++){
		qValuesFile << stateActions[i]->getID() << " " << SEPARATOR_CHARACTER << " ";
		qValuesFile << QVALUE_TAG << ASSIGNATION_CHARACTER << " " << qValues[i] <<  endl;
	}
	qValuesFile.close();
}

void TDZeroSolver::savePolicyToFile(std::ofstream &policyFile){
	policyFile << COMMENT_CHARACTER << AUTOMATICALLY_GENERATED_FILE << endl;
	policyFile << POLICY_TAG << endl;
	list<StateActionPair*> policy = getGreedyPolicy();
	for(list<StateActionPair*>::iterator it = policy.begin(); it != policy.end(); it++){
		policyFile << (*it)->getID() << endl;
	}
	policyFile.close();
}

// ----------------------------------------------------------------------------
// Private Methods
// ----------------------------------------------------------------------------

string TDZeroSolver::getActionAccordingToPolicy(int stateBaseIndex) const{
	return problemDescription->getActionID(getActionIndexAccordingToPolicy(stateBaseIndex));
}

int TDZeroSolver::getActionIndexAccordingToPolicy(int stateBaseIndex) const{
	if(epsilon > 0.0 && rollBinaryDice(epsilon))
		return getRandomIndex(problemDescription->getActionNumber());
	else
		return getGreedyActionIndexAccordingToPolicy(stateBaseIndex);	
}

string TDZeroSolver::getGreedyActionAccordingToPolicy(int stateBaseIndex) const{
	int index = getGreedyActionIndexAccordingToPolicy(stateBaseIndex);
	return problemDescription->getActionID(index);
}

int TDZeroSolver::getGreedyActionIndexAccordingToPolicy(int stateBaseIndex) const{
	if(stateBaseIndex < 0)
		return -1;
	double maxValue = INT_MIN;
	int maxIndex = 0;
	int actions = problemDescription->getActionNumber();
	for(int i = stateBaseIndex; i < stateBaseIndex + actions; i++){
		if(qValues[i] > maxValue){
			maxValue = qValues[i];
			maxIndex = i - stateBaseIndex;
		}
	}
	return maxIndex;
}

void TDZeroSolver::processQValuesFile(std::ifstream &qValuesFile){
	bool typeFound = false;
	string line;
	while(qValuesFile.good() && !typeFound){
		getline(qValuesFile,line);
		bool commentLine = (line.substr(0,1) == COMMENT_CHARACTER);
		if(!commentLine){
			string tmp = line.substr(0,TYPE_TAG.length() + ASSIGNATION_CHARACTER.length());
			if(tmp == (TYPE_TAG + ASSIGNATION_CHARACTER)){
				typeFound = true;
				line = line.substr(TYPE_TAG.length() + ASSIGNATION_CHARACTER.length());
			}
			else
				throw new exception(FIRST_LINE_IS_NOT_TYPE_LINE.c_str());
		}
	}
	int type = 0;
	STR2NUMBER_ERROR error = str2int(type,line.c_str());
	if(error != SUCCESS)
		throw new exception("Type line is not well formatted");
	if(type != problemDescription->getProblemType()){
		throw new exception(FILES_DO_NOT_MATCH.c_str());
	}
	bool qValuesTagFound = false;
	while(qValuesFile.good() && !qValuesTagFound){
		getline(qValuesFile,line);
		bool commentLine = (line.substr(0,1) == COMMENT_CHARACTER);
		if(!commentLine){
			if(line != (QVALUES_TAG))
				throw new exception(QVALUES_TAG_NOT_FOUND.c_str());
			else
				qValuesTagFound = true;
		}
	}
	if(!qValuesTagFound)
		throw new exception(QVALUES_TAG_NOT_FOUND.c_str());
	int i = 0;
	int n = problemDescription->getStateActionPairsNumber();
	qValues = new double[n];
	StateActionPair **tmpStatesActions = problemDescription->getStateActionPairs();
	while(qValuesFile.good() && i < n){
		getline(qValuesFile,line);
		bool commentLine = (line.substr(0,1) == COMMENT_CHARACTER);
		if(!commentLine){
			size_t found = line.find_last_of(SEPARATOR_CHARACTER);
			if(found == string::npos)
				throw new exception(QVALUES_NOT_WELL_FORMATTED.c_str());
			string stateAction = line.substr(0, found - 1);
			if(stateAction != tmpStatesActions[i]->getID())
				throw new exception(FILES_DO_NOT_MATCH.c_str());
			string qValueStr = line.substr(found + 2);
			if(qValueStr.substr(0, QVALUE_TAG.length() + ASSIGNATION_CHARACTER.length()) != QVALUE_TAG + ASSIGNATION_CHARACTER)
				throw new exception(QVALUES_NOT_WELL_FORMATTED.c_str());
			qValueStr = qValueStr.substr(QVALUE_TAG.length() + ASSIGNATION_CHARACTER.length() + 1);
			double qValue = 0;
			STR2NUMBER_ERROR error = str2double(qValue,qValueStr.c_str());
			if(error != SUCCESS)
				throw new exception(QVALUES_NOT_WELL_FORMATTED.c_str());
			qValues[i] = qValue;
			i++;
		}
	}
}
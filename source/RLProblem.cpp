/*

** FILE: RLProblem.cpp

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

#include "RLProblem.h"

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------------------------

RLProblem::RLProblem(std::list<StateWithFeatures*> states, std::list<Action*> actions){
	orderActions(actions);
	stable_sort(states.begin(), states.end(), StateWithFeatures::compareStatesWithFeaturesPtr);
	stateSpaceSize = states.size();
	generateStateActionPairs(states,actions);
}

RLProblem::RLProblem(std::ifstream *problemDescriptionFile){
	bool typeFound = false;
	string line;
	while(problemDescriptionFile->good() && !typeFound){
		getline(*problemDescriptionFile,line);
		bool commentLine = (line.substr(0,1) == COMMENT_CHARACTER);
		if(!commentLine){
			string tmp = line.substr(0,TYPE_TAG.length());
			if(tmp == TYPE_TAG){
				typeFound = true;
				line = line.substr(TYPE_TAG.length());
			}
			else
				throw new exception("Bad Formatted file, type line is not the first non-comment line");
		}
	}
	if(typeFound){
		if(line.substr(0,1) != ASSIGNATION_CHARACTER)
			throw new exception("Type line is not well formatted");
		string typeNumberStr = line.substr(1);
		int type = 0;
		STR2NUMBER_ERROR error = str2int(type,typeNumberStr.c_str());
		if(error != SUCCESS)
			throw new exception("Type line is not well formatted");
		switch (type){
			case STATES_WITH_FEATURES:
				processProblemDescriptionFileWithFeatures(problemDescriptionFile);
				break;
			case STATES_WITHOUT_FEATURES:
				//TODO: Process description file with states not described by features
				break;
			default:
				throw new exception("Type given in file is not valid");
		}
	}
	else{
		throw new exception("Bad File, Type tag not found");
	}
}

RLProblem::~RLProblem(){
	for(int i = 0; i < getStateActionPairsNumber(); i++)
		delete stateActionPairs[i];
	delete [] stateActionPairs;
}

// ----------------------------------------------------------------------------
// Public Methods
// ----------------------------------------------------------------------------

StateActionPair **RLProblem::getStateActionPairs() const{
	return stateActionPairs;
}

Action **RLProblem::getActions() const{
	Action **tmpActions = new Action*[actionNumber];
	for(int i = 0; i < actionNumber; i++){
		tmpActions[i] = stateActionPairs[i]->getAction();
	}
	return tmpActions;
}

StateWithFeatures **RLProblem::getStatesWithFeatures() const{
	StateWithFeatures **tmpStates = new StateWithFeatures*[stateSpaceSize];
	for(int i = 0; i < getStateActionPairsNumber(); i += actionNumber){
		tmpStates[i/actionNumber] = dynamic_cast<StateWithFeatures*>(stateActionPairs[i]->getState());
	}
	return tmpStates;
}

int RLProblem::getStateSpaceSize() const{
	return stateSpaceSize;
}

int RLProblem::getActionNumber() const{
	return actionNumber;
}

RLProblem::PROBLEM_TYPE RLProblem::getProblemType() const{
	return problemType;
}

int RLProblem::getStateActionPairsNumber() const{
	return stateSpaceSize*actionNumber;
}

int RLProblem::getStateActionPairIndex(std::string stateID, const RLAlgorithmsLib::Action &action) const{
	int baseIndex = getStateBaseIndex(stateID);
	if(baseIndex >= 0){
		int actionIndex = action.getIndex();
		Action *testAction = stateActionPairs[baseIndex + actionIndex]->getAction();
		if(Action::equals(*testAction, action))
			return baseIndex + actionIndex;
	}
	return -1;
}	

int RLProblem::getStateActionPairIndex(std::string stateID, std::string actionID) const{
	int baseIndex = getStateBaseIndex(stateID);
	if(baseIndex >= 0){
		for(int i = baseIndex; i < baseIndex + actionNumber; i++){
			if(stateActionPairs[i]->getAction()->getID() == actionID)
				return i;
		}
	}
	return -1;
}

int RLProblem::getStateActionPairIndex(const RLAlgorithmsLib::StateWithFeatures &state, const RLAlgorithmsLib::Action &action) const{
	StateWithFeatures *testState = dynamic_cast<StateWithFeatures*>(stateActionPairs[state.getIndex()*actionNumber]->getState());
	bool matchingStates = StateWithFeatures::equals(*testState, state);
	if(!matchingStates)
		return -1;
	for(int i = state.getIndex()*actionNumber; i < (state.getIndex() + 1)*actionNumber; i++){
		testState = dynamic_cast<StateWithFeatures*>(stateActionPairs[i]->getState());
		Action *testAction = stateActionPairs[i]->getAction();
		if(Action::equals(*testAction, action) && StateWithFeatures::equals(*testState, state))
			return i;
	}
	return -1;
}

int RLProblem::getStateActionPairIndex(const RLAlgorithmsLib::StateWithFeatures &state, string actionID) const{
	StateWithFeatures *testState = dynamic_cast<StateWithFeatures*>(stateActionPairs[state.getIndex()*actionNumber]->getState());
	bool matchingStates = StateWithFeatures::equals(*testState, state);
	if(!matchingStates)
		return -1;
	for(int i = state.getIndex()*actionNumber; i < (state.getIndex() + 1)*actionNumber; i++){
		testState = dynamic_cast<StateWithFeatures*>(stateActionPairs[i]->getState());
		Action *testAction = stateActionPairs[i]->getAction();
		if(testAction->getID() == actionID)
			return i;
	}
	return -1;
}

int RLProblem::getStateActionPairIndex(const std::list<string> &featuresID, const std::list<int> &values, std::string actionID) const{
	StateWithFeatures *tmpState = getState(featuresID, values);
	Action *tmpAction = 0;
	for(int i = 0; i < actionNumber; i++){
		if(stateActionPairs[i]->getAction()->getID() == actionID)
			tmpAction = stateActionPairs[i]->getAction();
	}
	if(!tmpAction)
		return -1;
	return tmpState->getIndex()*actionNumber + tmpAction->getIndex();
}

int RLProblem::getStateBaseIndex(std::string stateID) const{
	for(int i = 0; i < getStateActionPairsNumber(); i+= actionNumber){
		if(stateActionPairs[i]->getState()->getID() == stateID)
			return i;
	}
	return -1;
}

int RLProblem::getStateBaseIndex(const RLAlgorithmsLib::StateWithFeatures &state) const{
	int index = state.getIndex()*actionNumber;
	if(StateWithFeatures::equals(*(dynamic_cast<StateWithFeatures*>(stateActionPairs[index]->getState())), state))
		return index;
	else
		return -1;
}

int RLProblem::getStateBaseIndex(const std::list<string> &featuresID, const std::list<int> &values) const{
	StateWithFeatures *testState = getState(featuresID, values);
	int index = testState->getIndex()*actionNumber;
	if(StateWithFeatures::equalsPtr(testState, dynamic_cast<StateWithFeatures*>(stateActionPairs[index]->getState())))
		return index;
	else
		return -1;
}

string RLProblem::getActionID(int actionIndex) const{
	if(actionIndex < actionNumber && actionIndex >= 0)
		return stateActionPairs[actionIndex]->getAction()->getID();
	return "";
}

string RLProblem::getStateIDFromBaseIndex(int stateBaseIndex) const{
	if(stateBaseIndex < getStateActionPairsNumber() && stateBaseIndex >= 0)
		return stateActionPairs[stateBaseIndex]->getState()->getID();
	return "";
}

string RLProblem::getStateIDFromStateIndex(int stateIndex) const{
	if(stateIndex < stateSpaceSize && stateIndex >= 0)
		return stateActionPairs[stateIndex*actionNumber]->getState()->getID();
	return "";
}

void RLProblem::saveProblemDescription(std::ofstream &problemDescriptionFile){
	if(!problemDescriptionFile.is_open())
		throw new exception(FILE_NOT_OPEN.c_str());
	problemDescriptionFile << COMMENT_CHARACTER + AUTOMATICALLY_GENERATED_FILE << endl;
	problemDescriptionFile << COMMENT_CHARACTER + PROBLEM_DESCRIPTION_FILE << endl;
	problemDescriptionFile << TYPE_TAG << ASSIGNATION_CHARACTER << ((int)problemType) << endl;
	if(problemType == STATES_WITH_FEATURES){
		problemDescriptionFile << FEATURES_TAG << "\n";
		StateWithFeatures *testState = dynamic_cast<StateWithFeatures*>(stateActionPairs[0]->getState());
		list<Feature*> features = testState->getFeatures();
		for(list<Feature*>::const_iterator it = features.begin(); it != features.end(); it++){
			string ID = (*it)->getID();
			int minVal = (*it)->getMinVal();
			int maxVal = (*it)->getMaxVal();
			problemDescriptionFile << ID_TAG << ASSIGNATION_CHARACTER << ID << SEPARATOR_CHARACTER;
			problemDescriptionFile << MIN_TAG << ASSIGNATION_CHARACTER << minVal << SEPARATOR_CHARACTER;
			problemDescriptionFile << MAX_TAG << ASSIGNATION_CHARACTER << maxVal << endl;
		}
	}
	else{
		//Problem description without features
	}
	problemDescriptionFile << ACTIONS_TAG << "\n";
	Action **tmpActions = getActions();
	for(int i = 0; i < actionNumber; i++){
		Action *tmpAction = tmpActions[i];
		problemDescriptionFile << ACTION_TAG << ASSIGNATION_CHARACTER << tmpAction->getID() << endl;
	}
	problemDescriptionFile.close();
}

// ----------------------------------------------------------------------------
// Private Methods
// ----------------------------------------------------------------------------

void RLProblem::processProblemDescriptionFileWithFeatures(std::ifstream *problemDescriptionFile){
	string line;
	getline(*problemDescriptionFile,line);
	bool featuresTagProcessed = false;
	bool actionsTagProcessed = false;
	list<Action*> actions = *(new list<Action*>);
	list<Feature*> features = *(new list<Feature*>);
	while(problemDescriptionFile->good()){
		bool isComment = (line.substr(0,1) == COMMENT_CHARACTER);
		//Only check non-comment lines
		if(!isComment){
			//Look for tag lines and process them
			if(line.substr(0,ACTIONS_TAG.length()) == ACTIONS_TAG && !actionsTagProcessed){
				processActionsTag(problemDescriptionFile, line, actions);
				actionsTagProcessed = true;
			}
			else if(line.substr(0,FEATURES_TAG.length()) == FEATURES_TAG && !featuresTagProcessed){
				processFeaturesTag(problemDescriptionFile, line, features);
				featuresTagProcessed = true;
			}
			//If it is a non-comment line with an ivalid tag then throw an exception
			else
				throw new exception("Invalid non-comment line");
		}
		else
			getline(*problemDescriptionFile,line);
	}
	list<StateWithFeatures*> states = *(new list<StateWithFeatures*>);;
	generateStatesWithFeatures(features,states);
	orderActions(actions);
	problemType = STATES_WITH_FEATURES;
	generateStateActionPairs(states,actions);
}

void RLProblem::processActionsTag(ifstream *problemDescriptionFile, string &line, list<Action*> &actions){
	getline(*problemDescriptionFile, line);
	//int maxIndex = 0;
	while(problemDescriptionFile->good()){
		bool isComment = (line.substr(0,1) == COMMENT_CHARACTER);
		if(!isComment){
			if(line == FEATURES_TAG || line == ACTIONS_TAG || line == STATES_TAG){
				return;
			}
			string tmp = line.substr(0,ACTION_TAG.length() + ASSIGNATION_CHARACTER.length());
			if(tmp != ACTION_TAG + ASSIGNATION_CHARACTER)
				throw new exception (ACTION_DESCRIPTION_NOT_WELL_FORMATTED.c_str());
			line = line.substr(ACTION_TAG.length() + ASSIGNATION_CHARACTER.length());
			string actionID = line;
			Action *tmpAction = new Action(actionID);
			actions.push_back(tmpAction);
		}
		getline(*problemDescriptionFile, line);
	}
}

void RLProblem::processFeaturesTag(ifstream *problemDescriptionFile, string &line, list<Feature*> &features){
	getline(*problemDescriptionFile, line);
	while(problemDescriptionFile->good()){
		bool isComment = (line.substr(0,1) == COMMENT_CHARACTER);
		if(!isComment){
			if(line == FEATURES_TAG || line == ACTIONS_TAG || line == STATES_TAG){
				return;
			}
			string tmp = line.substr(0,ID_TAG.length() + ASSIGNATION_CHARACTER.length());
			if(tmp != ID_TAG + ASSIGNATION_CHARACTER)
				throw new exception (FEATURE_DESCRIPTION_NOT_WELL_FORMATTED.c_str());
			line = line.substr(ID_TAG.length() + ASSIGNATION_CHARACTER.length());
			int endOfID = line.find_first_of(SEPARATOR_CHARACTER);
			if(endOfID == string::npos)
				throw new exception (FEATURE_DESCRIPTION_NOT_WELL_FORMATTED.c_str());
			string featureID = line.substr(0,endOfID);
			line = line.substr(endOfID + 1);
			tmp = line.substr(0,MIN_TAG.length() + ASSIGNATION_CHARACTER.length());
			if(tmp != MIN_TAG + ASSIGNATION_CHARACTER)
				throw new exception (FEATURE_DESCRIPTION_NOT_WELL_FORMATTED.c_str());
			line = line.substr(MIN_TAG.length() + ASSIGNATION_CHARACTER.length());
			endOfID = line.find_first_of(SEPARATOR_CHARACTER);
			if(endOfID == string::npos)
				throw new exception (FEATURE_DESCRIPTION_NOT_WELL_FORMATTED.c_str());
			int minVal;
			int error = str2int(minVal, line.substr(0,endOfID).c_str());
			if(error != SUCCESS)
				throw new exception (FEATURE_DESCRIPTION_NOT_WELL_FORMATTED.c_str());
			line = line.substr(endOfID+1);
			tmp = line.substr(0,MAX_TAG.length() + ASSIGNATION_CHARACTER.length());
			if(tmp != MAX_TAG + ASSIGNATION_CHARACTER)
				throw new exception (FEATURE_DESCRIPTION_NOT_WELL_FORMATTED.c_str());
			line = line.substr(MAX_TAG.length() + ASSIGNATION_CHARACTER.length());
			int maxVal;
			error = str2int(maxVal, line.c_str());
			if(error != SUCCESS)
				throw new exception (FEATURE_DESCRIPTION_NOT_WELL_FORMATTED.c_str());
			Feature *tmpFeature = new Feature(featureID, minVal, maxVal);
			features.push_back(tmpFeature);
		}
		getline(*problemDescriptionFile, line);
	}
	if(features.size() == 0)
		throw new exception("No features were readen");
}

void RLProblem::generateStatesWithFeatures(list<Feature*> &features, list<StateWithFeatures*> &states){
	stable_sort(features.begin(),features.end(),Feature::compareFeaturesPtr);
	features.unique(Feature::equalFeaturesPtr);
	int tmp = 1;
	int *indexes = new int [features.size()];
	int *minValues = new int[features.size()];
	int *maxValues = new int[features.size()];
	int i = 0;
	for(list<Feature*>::iterator iter = features.begin(); iter != features.end(); iter++){
		tmp *= (*iter)->getRangeLength();
		indexes[i] = 0;
		minValues[i] = (*iter)->getMinVal();
		maxValues[i] = (*iter)->getMaxVal();
		i++;
	}
	stateSpaceSize = tmp;
	
	for(i = 0; i < stateSpaceSize; i++){
		StateWithFeatures *tmpState = new StateWithFeatures;
		int j = 0;
		for(list<Feature*>::iterator iter = features.begin(); iter != features.end(); iter++){
			tmpState->addFeature((*iter),(*iter)->getMinVal() + indexes[j]);
			j++;
		}
		for(j = features.size() - 1; j >= 0; j--){
			indexes[j]++;
			if(indexes[j] + minValues[j] > maxValues[j]){
				indexes[j] = 0;
			}
			else
				break;
		}
		states.push_back(tmpState);
	}
}

void RLProblem::generateStateActionPairs(list<StateWithFeatures*> &states, list<Action*> &actions){
	stateActionPairs = new StateActionPair*[getStateActionPairsNumber()];
	int i = 0;
	for(list<StateWithFeatures*>::iterator it1 = states.begin(); it1 != states.end(); it1++){
		int j = 0;
		for(list<Action*>::iterator it2 = actions.begin(); it2 != actions.end(); it2++){
			StateActionPair *tmpStateActionPair = new StateWithFeaturesActionPair((*it1),(*it2),actionNumber);
			stateActionPairs[i*actionNumber + j] = tmpStateActionPair;
			j++;
		}
		i++;
	}
}
void RLProblem::orderActions(std::list<Action*> &actions){
	stable_sort(actions.begin(), actions.end(), Action::compareActionsByIDPtr);
	int index = 0;
	for(list<Action*>::iterator it = actions.begin(); it != actions.end(); it++){
		(*it)->changeIndex(index);
		index++;
	}
	actionNumber = actions.size();
}
StateWithFeatures *RLProblem::getState(const std::list<string> &featuresID, const std::list<int> &values) const{
	bool correctFeatures = true;
	list<Feature*> referenceList = dynamic_cast<StateWithFeatures*>(stateActionPairs[0]->getState())->getFeatures();
	int *indexes = new int[referenceList.size()];
	if(referenceList.size() == featuresID.size() && featuresID.size() == values.size()){
		int i = 0;
		for(list<Feature*>::const_iterator it1 = referenceList.begin(); it1 != referenceList.end() && correctFeatures; it1++){
			bool found = false;
			int j = 0;
			for(list<string>::const_iterator it2 = featuresID.begin(); it2 != featuresID.end(); it2++){
				if((*it1)->getID() == (*it2)){
					found = !found;
					indexes[j] = i;
				}
				j++;
			}
			correctFeatures &= found;
			i++;
		}
	}
	else
		correctFeatures = false;
	if(!correctFeatures)
		return 0;
	StateWithFeatures *tmpState = new StateWithFeatures;
	int k = 0;
	for(list<Feature*>::const_iterator it1 = referenceList.begin(); it1 != referenceList.end(); it1++){
		list<int>::const_iterator it2 = values.begin();
		int m = 0;
		for(it2; m < indexes[k]; it2++){
			m++;
		}
		int value = *it2;
		tmpState->addFeature((*it1),value);
		k++;
	}
	return tmpState;
}
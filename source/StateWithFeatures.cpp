/*

** FILE: StateWithFeatures.cpp

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

**   04/10/2011

**

** NOTES:

**   Other relevant information

*/

// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#include "StateWithFeatures.h"

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------------------------

StateWithFeatures::FeatureValuePair::FeatureValuePair(Feature *nFeature, int nValue){
	feature = nFeature;
	changeValue(nValue);
}

StateWithFeatures::FeatureValuePair::~FeatureValuePair(){
	delete feature;
}

StateWithFeatures::StateWithFeatures(){
	stateID = DEFAULT_STATE;
	stateIndex = 0;
	features = *(new list<FeatureValuePair*>);
}

StateWithFeatures::StateWithFeatures(const list<Feature*> &nFeatures){
	features = *(new list<FeatureValuePair*>);	
	for(list<Feature*>::const_iterator iter = nFeatures.begin(); iter != nFeatures.end(); iter++){
		FeatureValuePair *tmp = new FeatureValuePair((*iter),(*iter)->getMinVal());
		features.push_back(tmp);
	}
	stable_sort(features.begin(), features.end(), FeatureValuePair::compareFeatureValuePairsPtr);
	generateID();
	calculateIndex();
}

StateWithFeatures::StateWithFeatures(const list<Feature*> &nFeatures, const list<int> &nValues){
	features = *(new list<FeatureValuePair*>);
	list<int>::const_iterator iter1 = nValues.begin();
	for(list<Feature*>::const_iterator iter2 = nFeatures.begin(); iter2 != nFeatures.end() && iter1 != nValues.end();iter1++, iter2++){
		FeatureValuePair *tmp = new FeatureValuePair((*iter2),(*iter1));
		features.push_back(tmp);
	}
	stable_sort(features.begin(), features.end(), FeatureValuePair::compareFeatureValuePairsPtr);
	generateID();
	calculateIndex();
}

StateWithFeatures::~StateWithFeatures(){
	features.clear();
}


// ----------------------------------------------------------------------------
// Public Methods
// ----------------------------------------------------------------------------

Feature* StateWithFeatures::FeatureValuePair::getFeature() const{
	return feature;
}

int StateWithFeatures::FeatureValuePair::getValue() const{
	return value;
}

void StateWithFeatures::FeatureValuePair::changeValue(int newVal){
	if(newVal > feature->getMaxVal())
		value = feature->getMaxVal();
	else if(newVal < feature->getMinVal())
		value = feature->getMinVal();
	else
		value = newVal;
}

string StateWithFeatures::getID() const{
	return stateID;
}
		
int StateWithFeatures::getIndex() const{
	return stateIndex;
}

bool StateWithFeatures::addFeature(Feature *newFeature, int val){
	if(existsFeature(newFeature)){
		return false;
	}
	list<FeatureValuePair*>::const_iterator iter = features.begin();
	for(; iter != features.end(); iter++){
		if(!Feature::compareFeaturesPtr((*iter)->getFeature(),newFeature)) 
			break;
	}
	FeatureValuePair *tmp = new FeatureValuePair(newFeature,val);
	features.insert(iter,tmp);
	generateID();
	calculateIndex();
	return true;
}	

bool StateWithFeatures::changeFeatureValue(Feature *feature, int newVal){
	list<FeatureValuePair*>::iterator target = findFeature(feature);
	if(target != features.end()){
		(*target)->changeValue(newVal);
		generateID();
		calculateIndex();
		return true;
	}
	return false;
}

bool StateWithFeatures::changeFeatureValue(string featureID, int newVal){
	list<FeatureValuePair*>::iterator target = findFeature(featureID);
	if(target != features.end()){
		(*target)->changeValue(newVal);
		generateID();
		calculateIndex();
		return true;
	}
	return false;
}

bool StateWithFeatures::removeFeature(Feature *feature){
	list<FeatureValuePair*>::iterator target = findFeature(feature);
	if(target != features.end()){
		features.erase(target);
		generateID();
		calculateIndex();
		return true;
	}
	return false;
}

bool StateWithFeatures::removeFeature(string featureID){
	list<FeatureValuePair*>::iterator target = findFeature(featureID);
	if(target != features.end()){
		features.erase(target);
		generateID();
		calculateIndex();
		return true;
	}
	return false;
}

list<int> StateWithFeatures::getValues() const{
	return *(new list<int>);
}

list<Feature*> StateWithFeatures::getFeatures() const{
	list<Feature*> featuresNoValues;
	for(list<FeatureValuePair*>::const_iterator iter = features.begin(); iter != features.end(); iter++){
		Feature* ptr = (*iter)->getFeature();
		featuresNoValues.push_back(ptr);
	}
	return featuresNoValues;
}

// ----------------------------------------------------------------------------
// Static Methods
// ----------------------------------------------------------------------------

bool StateWithFeatures::FeatureValuePair::compareFeatureValuePairs(const StateWithFeatures::FeatureValuePair &x, 
																   const StateWithFeatures::FeatureValuePair &y){
	return Feature::compareFeaturesPtr(x.getFeature(), y.getFeature());
}

bool StateWithFeatures::FeatureValuePair::compareFeatureValuePairsPtr(StateWithFeatures::FeatureValuePair *x, 
																		   StateWithFeatures::FeatureValuePair *y){
	return Feature::compareFeaturesPtr(x->getFeature(), y->getFeature());
}

bool StateWithFeatures::compareStatesWithFeatures(const RLAlgorithmsLib::StateWithFeatures &x, 
												  const RLAlgorithmsLib::StateWithFeatures &y){
	return (x.getIndex() < y.getIndex());
}

bool StateWithFeatures::compareStatesWithFeaturesPtr(RLAlgorithmsLib::StateWithFeatures *x, RLAlgorithmsLib::StateWithFeatures *y){
	return (x->getIndex() < y->getIndex());
}

bool StateWithFeatures::equals(const RLAlgorithmsLib::StateWithFeatures &x, const RLAlgorithmsLib::StateWithFeatures &y){
	return x.getID() == y.getID();
}

bool StateWithFeatures::equalsPtr(RLAlgorithmsLib::StateWithFeatures *x, RLAlgorithmsLib::StateWithFeatures *y){
	if(y == x)
		return true;
	return x->getID() == y->getID();
}

// ----------------------------------------------------------------------------
// Private Methods
// ----------------------------------------------------------------------------

void StateWithFeatures::generateID(){
	stringstream tmpID;
	for(list<FeatureValuePair*>::iterator iter = features.begin(); iter != features.end(); iter++){
		tmpID << (*iter)->getFeature()->getID();
		tmpID << ASSIGNATION_CHARACTER << " ";
		tmpID << (*iter)->getValue();
		tmpID << " " << SEPARATOR_CHARACTER << " ";
	}
	stateID = tmpID.str();
	if(stateID.length() > 3)
		stateID = stateID.substr(0, stateID.length() - 3);
}

void StateWithFeatures::calculateIndex(){
	int tmp = 0;
	for(list<FeatureValuePair*>::iterator iter = features.begin(); iter != features.end(); iter++){
		tmp *= (*iter)->getFeature()->getRangeLength();
		tmp += ((*iter)->getValue() - (*iter)->getFeature()->getMinVal());
	}
	stateIndex = tmp;
}

bool StateWithFeatures::existsFeature(Feature *feature){
	return existsFeature(feature->getID());
}

bool StateWithFeatures::existsFeature(string featureID){
	for(list<FeatureValuePair*>::iterator iter = features.begin(); iter != features.end(); iter++){
		if(!(*iter)->getFeature()->getID().compare(featureID)){
			return true;
		}
	}
	return false;
}

list<StateWithFeatures::FeatureValuePair*>::iterator StateWithFeatures::findFeature(Feature *feature){
	list<FeatureValuePair*>::iterator iter = features.begin();
	for(;iter != features.end(); iter++){
		if((*iter)->getFeature() == feature)
			return iter;
	}
	return iter;
}

list<StateWithFeatures::FeatureValuePair*>::iterator StateWithFeatures::findFeature(string featureID){
	list<FeatureValuePair*>::iterator iter = features.begin();
	for(; iter != features.end(); iter++){
		if(!((*iter)->getFeature()->getID().compare(featureID)))
			return iter;
	}
	return iter;
}
/*

** FILE: Feature.cpp

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

#include "Feature.h"

using namespace RLAlgorithmsLib;

// ----------------------------------------------------------------------------
// Constructors/Destructors
// ----------------------------------------------------------------------------

Feature::Feature(string ID, int nMinVal, int nMaxVal){
	if(nMaxVal < nMinVal)
		throw new exception("Feature's specified range is not valid");
	featureID = ID;
	minVal = nMinVal;
	maxVal = nMaxVal;
}

Feature::~Feature(){
	featureID = "";
	minVal = 0;
	maxVal = 0;
}

// ----------------------------------------------------------------------------
// Public Methods
// ----------------------------------------------------------------------------

string Feature::getID() const{
	return featureID;
}

int Feature::getMinVal() const{
	return minVal;
}
			
int Feature::getMaxVal() const{
	return maxVal;
}

int Feature::getRangeLength() const{
	return maxVal - minVal + 1;
}	

// ----------------------------------------------------------------------------
// Static Methods
// ----------------------------------------------------------------------------

bool Feature::compareFeatures(const Feature &x, const Feature &y){
	return (x.getID() < y.getID());
}

bool Feature::compareFeaturesPtr(Feature *x, Feature *y){
	return (x->getID() < y->getID());
}

bool Feature::equalFeatures(const RLAlgorithmsLib::Feature &x, const RLAlgorithmsLib::Feature &y){
	return (x.getID() == y.getID());
}

bool Feature::equalFeaturesPtr(Feature *x, Feature *y){
	return (x->getID() == y->getID());
}


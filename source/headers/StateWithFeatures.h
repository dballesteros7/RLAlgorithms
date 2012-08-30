/*

** FILE: StateWithFeatures.h

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

#ifndef STATE_WITH_FEATURES_H
#define STATE_WITH_FEATURES_H

#include "State.h"
#include "Feature.h"
#include <list>
#include <algorithm>
#include <sstream>

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	class StateWithFeatures : public State {
	private:
		class FeatureValuePair {
		private:
			Feature *feature;
			int value;
		public:
			FeatureValuePair(Feature *nFeature, int newValue);
			~FeatureValuePair();
			Feature* getFeature() const;
			int getValue() const;
			void changeValue(const int newVal);
			static bool compareFeatureValuePairs(const FeatureValuePair &x, const FeatureValuePair &y);
			static bool compareFeatureValuePairsPtr(FeatureValuePair *x, FeatureValuePair *y);
		};
	private:
		list<FeatureValuePair*> features;
	public:
		StateWithFeatures();
		StateWithFeatures(const list<Feature*> &nFeatures, const list<int> &nValues);
		StateWithFeatures(const list<Feature*> &nFeatures);
		~StateWithFeatures();
		string getID() const;
		int getIndex() const;
		bool addFeature(Feature *newFeature, int val);
		bool changeFeatureValue(Feature *feature, int newVal);
		bool changeFeatureValue(string featureID, int newVal);
		bool removeFeature(Feature *feature);
		bool removeFeature(string featureID);
		list<int> getValues() const;
		list<Feature*> getFeatures() const;
		static bool compareStatesWithFeatures(const StateWithFeatures &x, const StateWithFeatures &y);
		static bool compareStatesWithFeaturesPtr(StateWithFeatures *x, StateWithFeatures *y);
		static bool equals(const StateWithFeatures &x, const StateWithFeatures &y);
		static bool equalsPtr(StateWithFeatures *x, StateWithFeatures *y);
	private:
		void generateID();
		void calculateIndex();		
		bool existsFeature(Feature *feature);
		bool existsFeature(string featureID);
		list<FeatureValuePair*>::iterator findFeature(Feature *feature);
		list<FeatureValuePair*>::iterator findFeature(string featureID);
	};
}

#endif //STATE_WITH_FEATURES_H
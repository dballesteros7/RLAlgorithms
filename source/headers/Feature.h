/*

** FILE: Feature.h

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

#ifndef FEATURE_H
#define FEATURE_H

#include <string>

using namespace std;

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	class Feature {
		private:
			string featureID;
			int minVal;
			int maxVal;
		public:		
			Feature(string ID, int nMinVal, int nMaxVal);
			~Feature();
			string getID() const;
			int getMinVal() const;
			int getMaxVal() const;
			int getRangeLength() const;
			static bool compareFeatures(const Feature &x, const Feature &y);
			static bool compareFeaturesPtr(Feature *x, Feature *y);
			static bool equalFeatures(const Feature &x, const Feature &y);
			static bool equalFeaturesPtr(Feature *x, Feature *y);
	};
}

#endif //FEATURE_H
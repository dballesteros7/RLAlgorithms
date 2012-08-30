/*

** FILE: Action.h

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

**   06/10/2011

**

** NOTES:

**   Other relevant information

*/

// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#ifndef ACTION_H
#define ACTION_H

#include <string>

using namespace std;

// ----------------------------------------------------------------------------
// Classes
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{
	
	class Action {
	private:
		int actionIndex;
		string actionID;
	public:
		Action(string nID, int nActionIndex = 0);
		~Action();
		string getID() const;
		int getIndex() const;
		void changeIndex(int newIndex);
		static bool compareActions(const Action &x, const Action &y);
		static bool compareActionsPtr(Action *x, Action *y);
		static bool compareActionsByID(const Action &x, const Action &y);
		static bool compareActionsByIDPtr(Action *x, Action *y);
		static bool equals(const Action &x, const Action &y);
		static bool equalsPtr(Action *x, Action *y);
	};
}

#endif //ACTION_H
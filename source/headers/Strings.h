/*

** FILE: Strings.h

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

**   15/10/2011

**

** NOTES:

**   Other relevant information

*/

// ----------------------------------------------------------------------------
// Preprocessor Definitions
// ----------------------------------------------------------------------------

#ifndef STRINGS_H
#define STRINGS_H

#include <string>

using namespace std;

// ----------------------------------------------------------------------------
// Constants
// ----------------------------------------------------------------------------

namespace RLAlgorithmsLib{

	const string DEFAULT_STATE = "null";
	const string TYPE_TAG = "Type";
	const string ID_TAG = "ID";
	const string MIN_TAG = "Min";
	const string MAX_TAG = "Max";
	const string INDEX_TAG = "Index";
	const string ACTION_TAG = "Action";
	const string ACTIONS_TAG = "[Actions]";
	const string FEATURES_TAG = "[Features]";
	const string STATES_TAG = "[States]";
	const string QVALUES_TAG = "[Q-Values]";
	const string QVALUE_TAG = "Q-Value";
	const string POLICY_TAG = "[Policy]";
	const string ASSIGNATION_CHARACTER = "=";
	const string SEPARATOR_CHARACTER = ";";
	const string COMMENT_CHARACTER = "#";
	const string FEATURE_DESCRIPTION_NOT_WELL_FORMATTED = "A feature's description is not formatted correctly";
	const string ACTION_DESCRIPTION_NOT_WELL_FORMATTED = "An action's description is not formatted correctly";
	const string AUTOMATICALLY_GENERATED_FILE = "This file has been automatically generated";
	const string PROBLEM_DESCRIPTION_FILE = "This is a problem description file";
	const string QVALUES_FILE = "This file contains learned Q-values";
	const string FILE_NOT_OPEN = "File is not available for I/O operations";
	const string FIRST_LINE_IS_NOT_TYPE_LINE = "Bad Formatted file, type line is not the first non-comment line";
	const string FILES_DO_NOT_MATCH = "Problem files don't match";
	const string QVALUES_TAG_NOT_FOUND = "Q-Values tag was not found in file";
	const string QVALUES_NOT_WELL_FORMATTED = "Q-Values file is not well formatted";
}

#endif //STRINGS_H
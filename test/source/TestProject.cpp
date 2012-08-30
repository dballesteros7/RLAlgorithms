// TestProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SarsaSolver.h"
#include "QLearningSolver.h"
#include "WindyGridWorld.h"
#include "CliffWalking.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>


using namespace std;

const string windyGridWorldProblemFileName = "./data/Windy-Grid-World.pData";
const string windyGridWorldSarsaQValuesFileName = "./data/Windy-Grid-World-Sarsa-Q-Values.qValuesData";
const string windyGridWorldSarsaResultsFileName = "./data/Results-Windy-Grid-World-Sarsa.txt";
const string windyGridWorldSarsaPolicyFileName = "./data/Windy-Grid-World-Sarsa-Policy.txt";

const string cliffWalkingProblemFileName = "./data/Cliff-Walking.pData";
const string cliffWalkingSarsaQValuesFileName = "./data/Cliff-Walking-Sarsa-Q-Values.qValuesData";
const string cliffWalkingSarsaResultsFileName = "./data/Results-Cliff-Walking-Sarsa.txt";
const string cliffWalkingSarsaPolicyFileName = "./data/Cliff-Walking-Sarsa-Policy.txt";

const string cliffWalkingQLearningQValuesFileName = "./data/Cliff-Walking-QLearning-Q-Values.qValuesData";
const string cliffWalkingQLearningResultsFileName = "./data/Results-Cliff-Walking-QLearning.txt";
const string cliffWalkingQLearningPolicyFileName = "./data/Cliff-Walking-QLearning-Policy.txt";

void solveWindyWorldSarsaNoLibrary(){

	bool reached = false;
	double r = 0.0, epsilon = 0.1, gamma = 1.0, alpha = 0.1;
	int x = 0, y = 0, epCount = 0, steps = 0, maxSteps = 8000;
	ofstream resultsOut((windyGridWorldSarsaResultsFileName + "a").c_str());
	double qValues [280];
	for(int i = 0; i < 280; i++)
		qValues[i] = 0.0;
	while(steps < maxSteps)
	{
		WindyGridWorld::initializeWorld(x,y);
		int last_x = x;
		int last_y = y;
		int last_index = 0;
		reached = false;
		string action = "";
		int k = (x*7 + y)*4;
		double maxValue = -50000;
		int maxIndex = k;
		for(int i = k; i < k + 4; i++){
			if(qValues[i] > maxValue){
				maxValue = qValues[i];
				maxIndex = i - k;
			}
		}
		int coin = rand();
		if(coin < epsilon*RAND_MAX){
			//select random action
			coin = rand();
			int accum = RAND_MAX/4;
			for(int i = 0; i < 4; i++){
				if(coin < accum){
					maxIndex = i;
					break;
				}
				else{
					accum += RAND_MAX/4;
				}
			}
		}
		switch(maxIndex){
			case 0:
				action = "DOWN";
				break;
			case 1:
				action = "LEFT";
				break;
			case 2:
				action = "RIGHT";
				break;
			case 3:
				action = "UP";
				break;
		}
		while(!reached && steps < maxSteps){
			WindyGridWorld::moveInWorld(x,y,reached,r,action);
			action = "";
			k = (x*7 + y)*4;
			maxValue = -50000;
			maxIndex = k;
			for(int i = k; i < k + 4; i++){
				if(qValues[i] > maxValue){
					maxValue = qValues[i];
					maxIndex = i - k;
				}
			}
			int coin = rand();
			if(coin < epsilon*RAND_MAX){
				//select random action
				coin = rand();
				int accum = RAND_MAX/4;
				for(int i = 0; i < 4; i++){
					if(coin < accum){
						maxIndex = i;
						break;
					}
					else{
						accum += RAND_MAX/4;
					}
				}
			}
			switch(maxIndex){
				case 0:
					action = "DOWN";
					break;
				case 1:
					action = "LEFT";
					break;
				case 2:
					action = "RIGHT";
					break;
				case 3:
					action = "UP";
					break;
			}
			qValues[4*(last_x*7 + last_y) + last_index] += alpha*(r + gamma*qValues[(x*7 + y)*4 + maxIndex] - qValues[4*(last_x*7 + last_y) + last_index]);
			resultsOut << epCount << endl;
			steps++;
			last_x = x;
			last_y = y;
			last_index = maxIndex;
		}
		if(reached)
			epCount++;
	}
	resultsOut.close();
}


void runWindyWorldSarsa(){

	bool reached = false;
	double r = 0.0, epsilon = 0.1, gamma = 1.0, alpha = 0.5;
	int x = 0, y = 0, epCount = 0, steps = 0, maxSteps = 8000, maxEpCount = 170;
	ifstream *windyGridWorldProblemFile = new ifstream(windyGridWorldProblemFileName.c_str());
	ofstream resultsOut(windyGridWorldSarsaResultsFileName.c_str()), 
		qValuesOut(windyGridWorldSarsaQValuesFileName.c_str()),policyOut(windyGridWorldSarsaPolicyFileName.c_str());
	RLAlgorithmsLib::RLProblem *windyGridWorldProblem = new RLAlgorithmsLib::RLProblem(windyGridWorldProblemFile);
	RLAlgorithmsLib::SarsaSolver *windyGridWorldSarsaSolver = 
		new RLAlgorithmsLib::SarsaSolver(windyGridWorldProblem, epsilon, gamma, alpha);
	list<string> featuresID;
	featuresID.push_back("X-Coordinate");
	featuresID.push_back("Y-Coordinate");
	list<int> values, next_values;
	while(epCount < maxEpCount)
	{
		WindyGridWorld::initializeWorld(x,y);
		reached = false;
		values.clear();
		values.push_back(x);
		values.push_back(y);
		string action = windyGridWorldSarsaSolver->getActionAccordingToPolicy(featuresID, values);
		while(!reached){	
			WindyGridWorld::moveInWorld(x,y,reached,r,action);
			next_values.clear();
			next_values.push_back(x);
			next_values.push_back(y);
			windyGridWorldSarsaSolver->processStateTransition(featuresID, values, featuresID, next_values, action, r);
			resultsOut << epCount << endl;
			//steps++;
			values.clear();
			values.push_back(x);
			values.push_back(y);
			action = windyGridWorldSarsaSolver->getActionAccordingToPolicy(featuresID, values);
		}
		//if(reached)
		epCount++;
	}
	windyGridWorldSarsaSolver->saveQValuesFile(qValuesOut);
	windyGridWorldSarsaSolver->savePolicyToFile(policyOut);
	windyGridWorldProblemFile->close();
	resultsOut.close();

}

void runCliffWalkingSarsa(){

	bool reached = false;
	double r = 0.0, epsilon = 0.1, gamma = 1.0, alpha = 0.1;
	int x = 0, y = 0, epCount = 0, maxEpCount = 500;
	ifstream *cliffWalkingProblemFile = new ifstream(cliffWalkingProblemFileName.c_str());
	ofstream resultsOut(cliffWalkingSarsaResultsFileName.c_str()), 
		qValuesOut(cliffWalkingSarsaQValuesFileName.c_str()),policyOut(cliffWalkingSarsaPolicyFileName.c_str());
	RLAlgorithmsLib::RLProblem *cliffWalkingProblem = new RLAlgorithmsLib::RLProblem(cliffWalkingProblemFile);
	RLAlgorithmsLib::SarsaSolver *cliffWalkingSarsaSolver = 
		new RLAlgorithmsLib::SarsaSolver(cliffWalkingProblem, epsilon, gamma, alpha);
	list<string> featuresID;
	featuresID.push_back("X-Coordinate");
	featuresID.push_back("Y-Coordinate");
	list<int> values, next_values;
	while(epCount < maxEpCount)
	{
		CliffWalking::initializeWorld(x,y);
		reached = false;
		values.clear();
		values.push_back(x);
		values.push_back(y);
		string action = cliffWalkingSarsaSolver->getActionAccordingToPolicy(featuresID, values);
		double accumR = 0;
		while(!reached){
			CliffWalking::moveInWorld(x,y,reached,r,action);
			next_values.clear();
			next_values.push_back(x);
			next_values.push_back(y);
			cliffWalkingSarsaSolver->processStateTransition(featuresID, values, featuresID, next_values, action, r);
			values.clear();
			values.push_back(x);
			values.push_back(y);
			action = cliffWalkingSarsaSolver->getActionAccordingToPolicy(featuresID, values);
			accumR += r;
		}
		resultsOut << accumR << endl;
		epCount++;
	}
	cliffWalkingSarsaSolver->saveQValuesFile(qValuesOut);
	cliffWalkingSarsaSolver->savePolicyToFile(policyOut);
	cliffWalkingProblemFile->close();
	resultsOut.close();
}
void runCliffWalkingQLearning(){

	bool reached = false;
	double r = 0.0, epsilon = 0.1, gamma = 1.0, alpha = 0.1;
	int x = 0, y = 0, epCount = 0, maxEpCount = 500;
	ifstream *cliffWalkingProblemFile = new ifstream(cliffWalkingProblemFileName.c_str());
	ofstream resultsOut(cliffWalkingQLearningResultsFileName.c_str()), 
		qValuesOut(cliffWalkingQLearningQValuesFileName.c_str()),policyOut(cliffWalkingQLearningPolicyFileName.c_str());
	RLAlgorithmsLib::RLProblem *cliffWalkingProblem = new RLAlgorithmsLib::RLProblem(cliffWalkingProblemFile);
	RLAlgorithmsLib::QLearningSolver *cliffWalkingQLearningSolver = 
		new RLAlgorithmsLib::QLearningSolver(cliffWalkingProblem, epsilon, gamma, alpha);
	list<string> featuresID;
	featuresID.push_back("X-Coordinate");
	featuresID.push_back("Y-Coordinate");
	list<int> values, next_values;
	while(epCount < maxEpCount)
	{
		CliffWalking::initializeWorld(x,y);
		reached = false;
		values.clear();
		values.push_back(x);
		values.push_back(y);
		string action = cliffWalkingQLearningSolver->getActionAccordingToPolicy(featuresID, values);
		double accumR = 0;
		while(!reached){
			CliffWalking::moveInWorld(x,y,reached,r,action);
			next_values.clear();
			next_values.push_back(x);
			next_values.push_back(y);
			cliffWalkingQLearningSolver->processStateTransition(featuresID, values, featuresID, next_values, action, r);
			values.clear();
			values.push_back(x);
			values.push_back(y);
			action = cliffWalkingQLearningSolver->getActionAccordingToPolicy(featuresID, values);
			accumR += r;
		}
		resultsOut << accumR << endl;
		epCount++;
	}
	cliffWalkingQLearningSolver->saveQValuesFile(qValuesOut);
	cliffWalkingQLearningSolver->savePolicyToFile(policyOut);
	cliffWalkingProblemFile->close();
	resultsOut.close();

}
int _tmain(int argc, _TCHAR* argv[])
{

	runWindyWorldSarsa();
	//runCliffWalkingSarsa();
	//runCliffWalkingQLearning();

	return 0;
}


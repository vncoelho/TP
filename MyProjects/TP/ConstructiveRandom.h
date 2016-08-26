#ifndef TP_CONSTRUCTIVE_Random_H_
#define TP_CONSTRUCTIVE_Random_H_

#include "../../OptFrame/Constructive.h"
#include "../../OptFrame/RandGen.hpp"
#include "../../OptFrame/Heuristics/GRASP/GRConstructive.h"
#include "ProblemInstance.h"

#include "Representation.h"
#include "Solution.h"

#include "Evaluator.h"

#include <list>

#include <algorithm>
#include <stdlib.h>

using namespace std;

using namespace optframe;

namespace TP
{

class ConstructiveRandom: public GRConstructive<RepTP, MY_ADS>
{
private:
	ProblemInstance& pTP;
	RandGen& rg;
	int nodeMaxChildren;
	int treeMaxDepth;

	// Your private vars

public:

	ConstructiveRandom(ProblemInstance& _pTP, RandGen& _rg, int _nodeMaxChildren, int _treeMaxDepth);

	virtual ~ConstructiveRandom();

	Solution<RepTP, MY_ADS>& generateSolution();
	Solution<RepTP, MY_ADS>& generateSolution(float notUsed);

	void fillNode(Node& previousNode, int nOperators, int nVariables, int nodeMaxChildren, int treeMaxDepth);
};

}

#endif /*TP_CONTRUCTIVE_Random_H_*/

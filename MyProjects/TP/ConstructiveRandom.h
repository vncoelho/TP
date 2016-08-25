#ifndef TP_CONSTRUCTIVE_Random_H_
#define TP_CONSTRUCTIVE_Random_H_

#include "../../OptFrame/Constructive.h"
#include "../../OptFrame/RandGen.hpp"

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

class ConstructiveRandom: public Constructive<RepTP, MY_ADS>
{
private:
	ProblemInstance& pTP;
	RandGen& rg;
	int nLayers;

	// Your private vars

public:

	ConstructiveRandom(ProblemInstance& _pTP, RandGen& rg);

	virtual ~ConstructiveRandom();

	Solution<RepTP, MY_ADS>& generateSolution();

	void fillNode (Node& previousNode, int nOperators, int nVariables, int maxChildren, int maxDepth);
};

}

#endif /*TP_CONTRUCTIVE_Random_H_*/

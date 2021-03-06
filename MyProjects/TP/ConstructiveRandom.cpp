#include "ConstructiveRandom.h"

using namespace TP;

ConstructiveRandom::ConstructiveRandom(ProblemInstance& _pTP, RandGen& _rg, int _nodeMaxChildren, int _treeMaxDepth) :
		pTP(_pTP), rg(_rg), nodeMaxChildren(_nodeMaxChildren), treeMaxDepth(_treeMaxDepth)
{

}

ConstructiveRandom::~ConstructiveRandom()
{
}
//
//Node* ConstructiveRandom::fillNode(Node& previousNode, int previousNodePos, int nOperators, int nVariables, int nextMaxDepth)
//{
//	int nROperator = rg.rand(nOperators);
//	int rVariable = rg.rand(nVariables);
//	int operatorOrVariable = rg.rand(2);
//
//	if (operatorOrVariable == 0)
//		previousNode.children.at(previousNodePos)->operation = pTP.operators[nROperator];
//
//	if (operatorOrVariable == 1)
//		previousNode.children.at(previousNodePos)->operation = rVariable;
//
//	int nRLayers = rg.rand(nextMaxDepth);
//	vector<Node*> currentChildren(nRLayers);
//	previousNode.children.at(previousNodePos)->children = currentChildren;
//
//	return previousNode.children.at(previousNodePos);
//}

void ConstructiveRandom::fillNode(Node& node, int nOperators, int nVariables, int nodeMaxChildren, int treeMaxDepth)
{
	if (treeMaxDepth == 0)
		return;

	int nRandomChildren = 0;
	if (node.nodeChar.nT == opOperator)
	{
		nRandomChildren = 2 * (rg.rand(nodeMaxChildren) + 1);
		node.children = vector<Node*>(nRandomChildren, NULL);
	}

	for (int i = 0; i < nRandomChildren; i++)
	{
		Node* newNode = new Node(&node);
		node.children[i] = newNode;

		int operatorOrVariable = rg.rand(2);

		if (operatorOrVariable == 0)
		{
			int nROperator = rg.rand(nOperators);
			newNode->nodeChar.nT = opOperator;
			newNode->nodeChar.typeIndex = nROperator;
			newNode->nodeChar.varLag = -1;
//
		}
		if (operatorOrVariable == 1)
		{
			int rVariable = rg.rand(nVariables);
			newNode->nodeChar.nT = opVar;
			newNode->nodeChar.typeIndex = rVariable;
			newNode->nodeChar.varLag = 0;
		}

		fillNode(*newNode, nOperators, nVariables, nodeMaxChildren, treeMaxDepth - 1);

	}

	return;
}

Solution<RepTP, MY_ADS>& ConstructiveRandom::generateSolution()
{
	return generateSolution(0);
}

Solution<RepTP, MY_ADS>& ConstructiveRandom::generateSolution(float notUsed)
{

//	cout << "welcome to construtive" << endl;
	int nOperators = pTP.operators.size();
	int nVariables = pTP.inputs[0].size() - 1; //the last variable is the one we want to know formula

//	cout<<nOperators<<"/"<<nVariables<<endl;
//	getchar();

	int firstOperator = rg.rand(nOperators);
	Node* firstNode = new Node; // or new Node(NULL)
	firstNode->nodeChar.nT = opOperator;
	firstNode->nodeChar.typeIndex = firstOperator;
	firstNode->nodeChar.varLag = -1;

	fillNode(*firstNode, nOperators, nVariables, nodeMaxChildren, treeMaxDepth);

//	Node::printNode(firstNode);

	// copy representation to solution
	Solution<RepTP>& sol = *new Solution<RepTP>(*firstNode);
	// destroy original solution
	delete firstNode;
	// return solution
	return sol;

	// C++11 alternative... MOVE AND DESTROY EMPTY POINTER!
	//return *new Solution<RepTP>(std::move(*firstNode));

}

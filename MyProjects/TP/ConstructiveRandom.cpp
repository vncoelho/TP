#include "ConstructiveRandom.h"

using namespace TP;

ConstructiveRandom::ConstructiveRandom(ProblemInstance& _pTP, RandGen& _rg) :
		pTP(_pTP), rg(_rg)
{
	nLayers = 10;
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

void ConstructiveRandom::fillNode(Node& node, int nOperators, int nVariables, int maxChildren, int maxDepth)
{
	if (maxDepth == 0)
		return;

	int nChildren = 2 * (rg.rand(maxChildren) + 1);
	node.children = vector<Node*>(nChildren, NULL);

	for (int i = 0; i < nChildren; i++)
	{
		Node* newNode = new Node;
		node.children[i] = newNode;
		int nROperator = rg.rand(nOperators);
		int rVariable = rg.rand(nVariables);
		int operatorOrVariable = rg.rand(2);

		if (operatorOrVariable == 0)
			newNode->operation = make_pair(pTP.operators[nROperator], 0);
//
		if (operatorOrVariable == 1)
			newNode->operation = make_pair(to_string(rVariable), 1);

		fillNode(*newNode, nOperators, nVariables, maxChildren, maxDepth - 1);

	}

//
//	int nRLayers = rg.rand(nextMaxDepth);
//	vector<Node*> currentChildren(nRLayers);
//	previousNode.children.at(previousNodePos)->children = currentChildren;
//
//	return previousNode.children.at(previousNodePos);
}

Solution<RepTP, MY_ADS>& ConstructiveRandom::generateSolution()
{

//	cout << "welcome to construtive" << endl;
	int nOperators = pTP.operators.size();
	int nVariables = pTP.inputs[0].size() - 1; //the last variable is the one we want to know formula

//	cout<<nOperators<<"/"<<nVariables<<endl;
//	getchar();
	int firstOperator = rg.rand(nOperators);

	Node* firstNode = new Node;
	firstNode->operation = make_pair(pTP.operators[firstOperator], 0);

	int maxDepth = 3;

	fillNode(*firstNode, nOperators, nVariables, 3, maxDepth);

	Node::printNode(firstNode);

	RepTP newRep = *firstNode;

	return *new Solution<RepTP, MY_ADS>(newRep);

//	vector<Node*> firstChildren(nRLayers, NULL);
//	firstNode->children = firstChildren;

//	for(unsigned i=0; i<)
//
//
//
//	vector<Node*> firstChildren(nRLayers, NULL);
//	firstNode->children = firstChildren;
//
//	int childrenMax = 5;
//	int childrenPrevDepth = nRLayers;
//	Node* prevNode = firstNode;
//
//	cout << "going to childrens" << endl;
//	getchar();
//
//	for(unsigned i=0; i<firstChildren.size(); i++)
//	{
//
//	}
//	while (childrenPrevDepth != 0)
//	{
//		Node* currentChildren = fillNode(*prevNode, childrenPrevDepth, nOperators, nVariables, childrenPrevDepth);
//		childrenPrevDepth = rg.rand(childrenMax);
//
//
//		prevNode = currentChildren;
//	}

//	RepTP newRep = *firstNode;

//	return *new Solution<RepTP, MY_ADS>(newRep);
//}
//
//	firstNode->operation = pTP.operators[firstOperator];
//	firstNode->children = firstChildren;
//
//	int childrenMaxDepth = 5;
//	int childrenPrevDepth = nRLayers;
//	Node* prevNode = firstNode;
//
//	cout << "going to childrens" << endl;
//	getchar();
//
//	while (childrenPrevDepth != 0)
//	{
//		Node* currentChildren = fillNode(*prevNode, childrenPrevDepth, nOperators, nVariables, childrenPrevDepth);
//		childrenPrevDepth = rg.rand(childrenMaxDepth);
//
//
//		prevNode = currentChildren;
//	}
//
//	cout << "going to print..." << endl;
//	getchar();
//	printNode(firstNode);

}

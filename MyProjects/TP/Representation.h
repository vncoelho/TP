#ifndef TP_REPRESENTATION_H_
#define TP_REPRESENTATION_H_

#include <vector>
#include "../../OptFrame/Util/printable.h"

using namespace std;

enum Operation
{
	opOperator, opVar
};

//Node characteristics
struct NodeChar
{
	Operation nT;
	int typeIndex; //index for accessing that specific type
	int varLag; //special variable when accessing time series

};

struct Node
{
	NodeChar nodeChar;
	vector<Node*> children;

	// default empty constructor
	Node()
	{
	}

	// copy constructor
	Node(const Node& node)
	{
		nodeChar = node.nodeChar;
		for(unsigned i=0; i<node.children.size(); i++)
			children.push_back(new Node(*node.children[i]));
	}

	// move constructor (C++11 only!)
	Node(Node&& node)
	{
		nodeChar = node.nodeChar;
		// steal from the dying friend... (dirty move!)
		for(unsigned i=0; i<node.children.size(); i++)
			children.push_back(node.children[i]);
		// very important to empty the vector WITHOUT deleting the elements...
		node.children.clear();
	}

	// destructor (recursive destructor call cleans whole tree)
	~Node()
	{
		// destroy dependent children
		for(unsigned i=0; i<children.size(); i++)
		{
			// delete children
			delete children[i];
			// safety NULL assign
			children[i] = NULL;
		}
		// empty vector of garbage references
		children.clear();
	}

	// assignment operator
	Node& operator=(const Node& node)
	{
		// self-check, very important!!
		if(this == &node)
			return *this;
		nodeChar = node.nodeChar;
		for(unsigned i=0; i<children.size(); i++)
			delete children[i];
		children.clear();
		for(unsigned i=0; i<node.children.size(); i++)
			children.push_back(new Node(*node.children[i]));
		return *this;
	}

	// move assignment operator (C++11 only!)
	Node& operator=(Node&& node)
	{
		// self-check... don't know if needed with move assignment (???)
		if (this == &node)
			return *this;
		nodeChar = node.nodeChar;
		for (unsigned i = 0; i < children.size(); i++)
			delete children[i];
		children.clear();
		// steal from dying friend...
		for (unsigned i = 0; i < node.children.size(); i++)
			children.push_back(node.children[i]);
		// clear without delete!
		node.children.clear();
		return *this;
	}


	friend ostream & operator<<(ostream & os, const Node& rep)
	{
		os << "=======================================" << endl;
		os << "======PRINTING SOL CUADRANTES CLUSTERS=" << endl;

		os << "=======================================" << endl;

		return os;
	}

	static void rPrintNode(Node* root)
	{

		cout << "(op:" << root->nodeChar.nT << "/" << root->nodeChar.typeIndex << "/" << root->nodeChar.varLag << ",|c|=" << root->children.size() << "): { ";

		//for (Node* n : root->children){
		for (unsigned i = 0; i < root->children.size(); i++)
		{
			cout << endl;
			rPrintNode(root->children[i]);
		}
		cout << "}  \n";

	}

	static void printNode(Node* root)
	{
		cout << "ROOT NODE: (";
		rPrintNode(root);
		cout << ")";
		/*
		 cout << "My Value is " << root->operation << endl;
		 cout << "My children are ";
		 for (int i = 0; i < root->children.size(); i++){
		 cout << root->children[i]->operation << " ";
		 }
		 cout << endl;
		 for (int i = 0; i < root->children.size(); i++){
		 printNode(root->children[i]);         //call display on all children
		 }
		 cout << endl;
		 */
		cout << endl;
	}

};

typedef Node RepTP;

//

//#include <ostream>
//ostream & operator<< (ostream & s, RepTP){}

#endif /*TP_REPRESENTATION_H_*/


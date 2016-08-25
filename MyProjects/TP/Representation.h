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


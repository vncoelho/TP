#include "Evaluator.h"

using namespace TP;

TPEvaluator::TPEvaluator(ProblemInstance& _pTP) : // If necessary, add more parameters
		pTP(_pTP)
{
	// Put the rest of your code here
}

TPEvaluator::~TPEvaluator()
{
}

double TPEvaluator::getNodeValue(const Node* root, int s)
{
	double nodeValue = 0;
	Operation rootNT = root->nodeChar.nT;
	int rootTypeIndex = root->nodeChar.typeIndex;
	int rootLag = root->nodeChar.varLag;
//	cout << "(op:" << root->nodeChar.nT << "/" << root->nodeChar.typeIndex << "/" << root->nodeChar.varLag << ",|c|=" << root->children.size() << "): { ";
//getchar();
	if (rootNT == opVar)
	{
		return pTP.inputs[s - rootLag][rootTypeIndex];
	}

	//If reached this point, it is an operation
	int rootNChildren = root->children.size();
	//for (Node* n : root->children){
	for (int c = 0; c < rootNChildren; c++)
	{
		//Soma DONE
		if (rootTypeIndex == 0)
			nodeValue += getNodeValue(root->children[c], s);

		//Subtracao DONE
		if (rootTypeIndex == 1)
		{
			if (c == 0)
				nodeValue += getNodeValue(root->children[c], s);
			else
				nodeValue -= getNodeValue(root->children[c], s);

		}

		//* DONE
		if (rootTypeIndex == 2)
			nodeValue *= getNodeValue(root->children[c], s);

		// divisao  DONE
		if (rootTypeIndex == 3)
		{
			if (c == 0)
				nodeValue += getNodeValue(root->children[c], s);
			else
			{
				double divValue = getNodeValue(root->children[c], s);
				if (divValue != 0)
					nodeValue /= getNodeValue(root->children[c], s);
				else
					nodeValue = 10000000;
			}

		}

	}

	return nodeValue;
}

EvaluationTP& TPEvaluator::evaluate(const RepTP& rep)
{
// 'rep' is the representation of the solution

	double fo = 0; // Evaluation Function Value
//	cout << pTP.inputs << endl;
	int nSamples = pTP.getNSamples();
//	cout << "nSamples: " << nSamples << endl;
//getchar();

	for (int s = 0; s < nSamples; s++)
	{
		double expectedDebt = getNodeValue(&rep, s);
		double debt = pTP.inputs[s][pTP.inputs[s].size()-1];
		double error = abs(expectedDebt - debt);
		fo += error;


//		cout << "expectedDebt " << s << " = " << expectedDebt << "/" << debt << " error: " << error << endl;
	}
//	cout << "fo:" << fo << endl;

	return *new EvaluationTP(fo);
}
//EvaluationTP& TPEvaluator::evaluate(const RepTP& rep, const MY_ADS& ads);
//{
//	return evaluate(rep);
//}

bool TPEvaluator::betterThan(double f1, double f2)
{
	// MINIMIZATION
	return (f1 < (f2 - EPSILON_TP));
}

bool TPEvaluator::isMinimization() const
{
	// MINIMIZATION
	return true;
}

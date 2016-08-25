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

EvaluationTP& TPEvaluator::evaluate(const RepTP& rep)
{
	// 'rep' is the representation of the solution

	double fo = 0; // Evaluation Function Value


	cout<<"checking values of tree"<<endl;
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

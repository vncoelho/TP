#include "ProblemInstance.h"
#include "../../OptFrame/Util/printable.h"

ProblemInstance::ProblemInstance()
{
	File* fileBanco;

	try
	{
		fileBanco = new File("./MyProjects/Instance/banco");
	} catch (FileNotFound& f)
	{
		cout << "File '" << "./MyProjects/Instance/banco" << "' not found" << endl;
		exit(1);
	}

	Scanner scannerASDist(fileBanco);
	int nVariables = scannerASDist.nextInt();
	vector<vector<double> > inputsValues;

	cout << scannerASDist.nextLine() << endl;
	while (scannerASDist.hasNext())
	{
		vector<double> sampleVar(nVariables);
		for (int v = 0; v < nVariables; v++)
		{
			double vValues = scannerASDist.nextDouble();
			sampleVar[v] = vValues;
		}
		inputsValues.push_back(sampleVar);

	}



	inputs = inputsValues;
	operators =
	{	"+", "-", "*", "/"};
	cout << inputs << endl;

}

ProblemInstance::~ProblemInstance()
{
}

#include "pch.h"
#include "ApplicationController.h"
#include "MatrixCalculatorParallel.h"
#include "MatrixCalculatorSequential.h"

ApplicationController::ApplicationController()
{
	RunApplication();
}

void ApplicationController::RunApplication()
{
	std::string programType = GetProgrammType();
	std::ifstream file("input.txt");
	int matrixSize = ReadMatrixSize(file);
	Matrix matrix = ReadMatrix(matrixSize, file);

	if (programType == "parallel")
	{
		MatrixCalculatorParallel parallelProgram(matrixSize, matrix);
	}
	else if (programType == "sequential")
	{
		MatrixCalculatorSequential sequentialProgram(matrixSize, matrix);
	} 
	else
	{
		std::cout << "Input error" << std::endl;
	}
}

std::string ApplicationController::GetProgrammType()
{
	std::string typeName = "";
	std::cout << "Write programm version: parallel or sequential" << std::endl;
	std::cin >> typeName;

	return typeName;
}

int ApplicationController::ReadMatrixSize(std::ifstream &file)
{
	int matrixSize = 0;
	file >> matrixSize;

	return matrixSize;
}

Matrix ApplicationController::ReadMatrix(int matrixSize, std::ifstream &file)
{
	Matrix matrix;
	matrix.reserve(matrixSize);

	std::string matrixStr = "";

	while (std::getline(file, matrixStr))
	{
		std::vector<double> matrixLine = TransformStrInMatrixLine(matrixStr);
		matrix.push_back(matrixLine);
	}

	return matrix;
}

std::vector<double> ApplicationController::TransformStrInMatrixLine(std::string const& matrixStr)
{
	std::vector<double> matrixLine;
	std::stringstream  stringStream;

	stringStream << matrixStr;

	std::string numberStr;
	double number;

	while (stringStream >> numberStr)
	{
		number = std::stod(numberStr);
		matrixLine.push_back(number);
	}

	return matrixLine;
}
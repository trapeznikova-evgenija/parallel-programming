#include "pch.h"
#pragma once
class ApplicationController
{
public:
	ApplicationController();

	void RunApplication();
	int ReadMatrixSize(std::ifstream &file);
	Matrix ReadMatrix(int matrixSize, std::ifstream &file);

private:
	std::string GetProgrammType();
	std::vector<double> TransformStrInMatrixLine(std::string const& matrixStr);
};


#pragma once
#include "pch.h"

class MatrixCalculatorParallel
{
public:
	MatrixCalculatorParallel(int matrixSize, Matrix matrix);
	~MatrixCalculatorParallel();

private:
	int m_matrixSize;
	Matrix m_startMatrix;
};


#include "pch.h"
#include "MatrixCalculatorSequential.h"


MatrixCalculatorSequential::MatrixCalculatorSequential(size_t matrixSize, Matrix matrix) :
	m_matrixSize(matrixSize), m_startMatrix(matrix)
{
	std::cout << m_matrixSize << std::endl;
	int time = StartClock();
	CalculateAlgebraicAdditionsMatrix();
	PrintClock(time);
	//PrintMatrix(m_startMatrix);
	PrintMatrix(m_resultMatrix);
}

void MatrixCalculatorSequential::CalculateAlgebraicAdditionsMatrix()
{
	for (size_t i = 0; i < m_startMatrix.size(); i++)
	{
		std::vector<double> line;
		for (size_t j = 0; j < m_startMatrix[i].size(); j++)
		{
			line.push_back(pow(-1, i + j) * GetMinor(i, j));
		}
		m_resultMatrix.push_back(line);
	}
}

double MatrixCalculatorSequential::GetMinor(size_t x, size_t y)
{
	std::vector<std::vector<double>> minorMatrix = CalculateMatrixForMinor(x, y);
	return CalculateDeterminantMatrix(minorMatrix);
}

Matrix MatrixCalculatorSequential::CalculateMatrixForMinor(size_t x, size_t y)
{
	std::vector<std::vector<double>> matrixForMinor;
	for (size_t i = 0; i < m_startMatrix.size(); i++)
	{
		std::vector<double> line;
		for (size_t j = 0; j < m_startMatrix[i].size(); j++)
		{
			if (i != x && j != y)
			{
				line.push_back(m_startMatrix[i][j]);
			}
		}
		if (line.size() > 0)
		{
			matrixForMinor.push_back(line);
		}
	}
	return matrixForMinor;
}

double MatrixCalculatorSequential::CalculateDeterminantMatrix(Matrix matrix)
{
	if (matrix.size() == 2)
	{
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	}
	double determinant = 0;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		size_t k = i;
		double line = 1;
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (k >= matrix[i].size())
			{
				k = 0;
			}

			line *= matrix[j][k];
			k++;
		}
		determinant += line;
	}
	for (size_t i = 0; i < matrix.size(); i++)
	{
		int k = matrix.size() - 1;
		double line = 1;
		for (int j = matrix[i].size() - 1; j >= 0; j--)
		{
			if (k < 0)
			{
				k = matrix[i].size() - 1;
				std::cout << k;
			}
			line *= matrix[j][k];
			k--;
		}
		determinant -= line;
	}
	return determinant;
}

void MatrixCalculatorSequential::PrintMatrix(Matrix &matrix)
{
	for (size_t i = 0; i < matrix.size(); i++)
	{
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

int MatrixCalculatorSequential::StartClock()
{
	int time = clock();
	return time;
}

void MatrixCalculatorSequential::PrintClock(int const& time)
{
	std::cout << clock() - time << " ms" << std::endl;
}


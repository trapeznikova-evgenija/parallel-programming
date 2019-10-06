#include "pch.h"
#include "MatrixCalculator.h"


MatrixCalculator::MatrixCalculator()
{
}

std::vector<std::vector<double>> MatrixCalculator::GetMatrixOfAlgebraicComplements(std::vector<std::vector<double>> matrix)
{
	m_matrix = matrix;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::vector<double> line;
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			line.push_back(pow(-1, i + j) * GetMinor(m_matrix, i, j));
		}
		m_matrixOfAlgebraicComplements.push_back(line);
	}
	return m_matrixOfAlgebraicComplements;
}

void MatrixCalculator::ShowMatrix(std::vector<std::vector<double>> matrix) const
{
	std::cout << "size: " << matrix.size() << std::endl;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::cout << "size[" << i << "] " << matrix[i].size() << ": " << ' ';
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			std::cout << matrix[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}

double MatrixCalculator::GetMinor(std::vector<std::vector<double>> matrix, size_t x, size_t y)
{
	std::vector<std::vector<double>> minorMatrix = GetMatrixForMinor(matrix, x, y);
	return GetDeterminantOfMatrix(minorMatrix);
}

void MatrixCalculator::ShowMatrixOfAlgebraicComplements() const
{
	for (size_t i = 0; i < m_matrixOfAlgebraicComplements.size(); i++)
	{
		for (size_t j = 0; j < m_matrixOfAlgebraicComplements[i].size(); j++)
		{
			std::cout << m_matrixOfAlgebraicComplements[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

std::vector<std::vector<double>> MatrixCalculator::GetMatrixForMinor(std::vector<std::vector<double>> matrix, size_t x, size_t y)
{
	std::vector<std::vector<double>> matrixForMinor;
	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::vector<double> line;
		for (size_t j = 0; j < matrix[i].size(); j++)
		{
			if (i != x && j != y)
			{
				line.push_back(matrix[i][j]);
			}
		}
		if (line.size() > 0)
		{
			matrixForMinor.push_back(line);
		}
	}
	return matrixForMinor;
}

double MatrixCalculator::GetDeterminantOfMatrix(std::vector<std::vector<double>> matrix)
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
			}
			line *= matrix[j][k];
			k--;
		}
		determinant -= line;
	}

	return determinant;
}

MatrixCalculator::~MatrixCalculator()
{
}

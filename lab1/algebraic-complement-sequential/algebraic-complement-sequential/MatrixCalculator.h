#pragma once
#include "pch.h"

class MatrixCalculator
{
public:
	MatrixCalculator();
	std::vector<std::vector<double>> GetMatrixOfAlgebraicComplements(std::vector<std::vector<double>> matrix);
	void ShowMatrixOfAlgebraicComplements() const;
	void ShowMatrix(std::vector<std::vector<double>> matrix) const;
	~MatrixCalculator();
private:
	std::vector<std::vector<double>> m_matrix;
	std::vector<std::vector<double>> m_matrixOfAlgebraicComplements;

	double GetMinor(std::vector<std::vector<double>> matrix, size_t x, size_t y);
	std::vector<std::vector<double>> GetMatrixForMinor(std::vector<std::vector<double>> matrix, size_t x, size_t y);
	double GetDeterminantOfMatrix(std::vector<std::vector<double>> matrix);
};


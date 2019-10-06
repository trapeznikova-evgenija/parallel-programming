#pragma once
#include "pch.h"

class MatrixReader
{
public:
	MatrixReader();
	void ReadMatrixFromFile(std::string  fileName);
	std::vector<std::vector<double>> GetMatrix() const;
	~MatrixReader();
private:
	std::vector<std::vector<double>> m_matrix;

	std::vector<double> ConvertStrToMatrixLine(std::string const& str);
};
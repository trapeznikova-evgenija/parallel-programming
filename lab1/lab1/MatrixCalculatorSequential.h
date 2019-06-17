#pragma once
class MatrixCalculatorSequential
{
public:
	MatrixCalculatorSequential(size_t matrixSize, Matrix matrix);
	void CalculateAlgebraicAdditionsMatrix();

	void PrintMatrix(Matrix &matrix);
private:
	double GetMinor(size_t i, size_t j);
	double CalculateDeterminantMatrix(Matrix minor);
	Matrix CalculateMatrixForMinor(size_t i, size_t j);

	int StartClock();
	void PrintClock(int const& clock);

	size_t m_matrixSize;
	Matrix m_startMatrix;
	Matrix m_resultMatrix;
};


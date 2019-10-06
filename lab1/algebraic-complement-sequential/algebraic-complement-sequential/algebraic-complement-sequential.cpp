// algebraic-complement-sequential.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "MatrixReader.h";
#include "MatrixCalculator.h";

int StartClock()
{
	int time = clock();
	return time;
}

void PrintClock(int const& time)
{
	std::cout << clock() - time << " ms" << std::endl;
}

int main()
{
	MatrixReader reader;
	MatrixCalculator matrixCalculator;
	std::vector<std::vector<double>> matrix;

	reader.ReadMatrixFromFile("input.txt");
	matrix = reader.GetMatrix();

	std::cout << "matrix size: " << matrix.size() << std::endl;

	int time = StartClock();

	matrixCalculator.GetMatrixOfAlgebraicComplements(matrix);

	//matrixCalculator.ShowMatrixOfAlgebraicComplements();

	std::cout << std::endl;

	PrintClock(time);
}
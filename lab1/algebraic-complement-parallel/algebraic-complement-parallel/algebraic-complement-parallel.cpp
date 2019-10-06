// CofactorFinder.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "MatrixReader.h"

struct Data
{
	Matrix matrix;
	size_t x = 0;
	size_t y = 0;
	double result = 0;
};

Matrix GetMatrixOfAlgebraicComplements(Matrix matrix, size_t usersAmountThread);
double GetMinor(Matrix matrix, size_t x, size_t y);
Matrix GetMatrixForMinor(Matrix matrix, size_t x, size_t y);
double GetDeterminantOfMatrix(Matrix matrix);
void ShowMatrix(Matrix matrix);

DWORD WINAPI GetMinorParal(CONST LPVOID matrixData)
{
	auto data = (Data*)matrixData;
	Matrix minorMatrix = GetMatrixForMinor(data->matrix, data->x, data->y);
	data->result = GetDeterminantOfMatrix(minorMatrix);
	ExitThread(0);
}

int main()
{
	MatrixReader matrixReader;

	HANDLE process = GetCurrentProcess();
	SetProcessAffinityMask(process, 0b0001);
	
	Matrix matrix;
	matrixReader.ReadMatrixFromFile("input.txt");
	matrix = matrixReader.GetMatrix();
	std::cout << "size: " << matrix.size() << std::endl;
	int amountThreads = 0;
	std::cin >> amountThreads;
	int t = clock();
	//ShowMatrix(GetMatrixOfAlgebraicComplements(matrix, 3));
	GetMatrixOfAlgebraicComplements(matrix, amountThreads);
	std::cout << clock() - t << " ms" << std::endl;
}

void ShowMatrix(Matrix matrix)
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

double GetDeterminantOfMatrix(Matrix matrix)
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


Matrix GetMatrixForMinor(Matrix matrix, size_t x, size_t y)
{
	Matrix matrixForMinor;

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


double GetMinor(Matrix matrix, size_t x, size_t y)
{
	Matrix minorMatrix = GetMatrixForMinor(matrix, x, y);
	return GetDeterminantOfMatrix(minorMatrix);
}

Matrix GetMatrixOfAlgebraicComplements(Matrix matrix, size_t usersAmountThread)
{
	Matrix m_matrixOfAlgebraicComplements;
	Matrix m_matrix = matrix;

	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::vector<double> line;
		size_t currentPos = 0;

		while (currentPos < matrix[i].size())
		{
			int amountThread = 0;
			std::vector<Data*> dataVector;

			if (usersAmountThread > (matrix[i].size() - currentPos))
			{
				amountThread = matrix[i].size() - currentPos;
			}
			else
			{
				amountThread = usersAmountThread;
			}

			for (int j = 0; j < amountThread; j++)
			{
				auto* data = new Data;
				data->matrix = matrix;
				data->x = i;
				data->y = currentPos;
				dataVector.push_back(data);
				currentPos++;
			}

			HANDLE* handles = new HANDLE[amountThread];

			for (int j = 0; j < amountThread; j++)
			{
				HANDLE* handle = new HANDLE;

				handles[j] = CreateThread(NULL, 2048, &GetMinorParal, dataVector[j], 0, NULL);
			}

			WaitForMultipleObjects(amountThread, handles, true, INFINITE);

			for (int j = 0; j < amountThread; j++)
			{
				line.push_back(pow(-1, i + 0) * dataVector[j]->result);
			}
		}

		m_matrixOfAlgebraicComplements.push_back(line);
	}
	return m_matrixOfAlgebraicComplements;
}

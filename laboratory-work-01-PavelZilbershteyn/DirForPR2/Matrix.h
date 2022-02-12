#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix
{
private:
	struct coord
	{
		std::size_t i; // номер строки
		std::size_t j; // номер столбца
		double value; // Значение

		bool operator==(const coord& right) const;
	};

	std::size_t rows, cols;
	std::vector<coord> coefs;

public:
	Matrix();
   ~Matrix() = default;
    Matrix(const Matrix& other);
    Matrix(std::size_t r, std::size_t c);
	
	Matrix operator+(const Matrix& right) const;
	Matrix operator-(const Matrix& right) const;

	bool operator==(const Matrix& right) const;

	Matrix& operator=(const Matrix& right);

	Matrix operator*(double lambda) const;
	Matrix operator*(const Matrix& right) const;
	friend Matrix operator*(double lambda, const Matrix& right);

	friend std::ostream& operator<<(std::ostream& out, const Matrix& object);
	friend std::istream& operator>>(std::istream& in,  Matrix& object);

	Matrix Transpose() const;

	//Сеттеры
	void SetRows(std::size_t NewR);
	void SetCols(std::size_t NewC);

	//Геттер
	std::size_t GetRows() const;
	std::size_t GetCols() const;
	std::vector<coord> GetCoefs() const;

	double  operator()(std::size_t row, std::size_t col) const; //если нужно как rvalue
	double& operator()(std::size_t row, std::size_t col); //если нужно как lvalue
};

#endif //MATRIX_H


#include "Matrix.h"
#include <vector>
#include <cassert>
#include <algorithm>

Matrix::Matrix()
    :rows{ 0 }, cols{ 0 }
{}

Matrix::Matrix(const Matrix& other)
    : rows{ other.rows }, cols{ other.cols }, coefs{other.coefs}
{}

Matrix::Matrix(std::size_t r, std::size_t c)
    : rows{ r }, cols{ c }
{}

Matrix Matrix::operator+(const Matrix& right) const
{
    if (this->rows == right.rows && this->cols == right.cols)
    {
        Matrix result(rows, cols);
        for (std::size_t a{ 0 }; a < rows; ++a)
            for (std::size_t b{ 0 }; b < cols; ++b)
                result(a, b) = (*this)(a, b) + right(a, b);

        //Если внеслись нули

        for (std::size_t a{ 0 }; a < result.coefs.size(); ++a)
        {
            if (result.coefs[a].value == 0)
            {
                result.coefs.erase(result.coefs.begin() + a);
                --a;
            }
        }

        return result;
    }
}

Matrix Matrix::operator-(const Matrix& right) const
{
    if (this->rows == right.rows && this->cols == right.cols)
    {
        Matrix result(rows, cols);
        for (std::size_t a{ 0 }; a < rows; ++a)
            for (std::size_t b{ 0 }; b < cols; ++b)
                result(a, b) = (*this)(a, b) - right(a, b);

        //Если внеслись нули

        for (std::size_t a{ 0 }; a < result.coefs.size(); ++a)
        {
            if (result.coefs[a].value == 0)
            {
                result.coefs.erase(result.coefs.begin() + a);
                --a;
            }
        }

        return result;
    }
}

bool Matrix::operator==(const Matrix& right) const
{
    if (this->rows == right.rows && this->cols == right.cols && this->coefs.size() == right.coefs.size())
    {
        Matrix first(*this), second(right);

        std::size_t cnt{ 0 };

        for (std::size_t a{0};a<first.coefs.size();++a)         
            for (std::size_t b{ 0 }; b < second.coefs.size(); ++b)
            {
                if (first.coefs[a] == second.coefs[b])
                {
                    first.coefs[a].i = -1;
                    second.coefs[b].i = -1;
                }
            }

        for (const auto& elem : first.coefs)
            if (elem.i == -1)
                ++cnt;

        if (cnt == first.coefs.size())
            return true;
    }

    return false;
}

Matrix& Matrix::operator=(const Matrix& right)
{
    if (this != &right)
    {
        this->rows = right.rows;
        this->cols = right.cols;
        this->coefs = right.coefs;
    }

    return (*this);
}


Matrix Matrix::operator*(double lambda) const
{
    Matrix res(*this);
    for (auto& elem : res.coefs)
    {
        elem.value *= lambda;
    }

    return res;
}

Matrix Matrix::operator*(const Matrix& right) const
{
    if (this->cols == right.rows)
    {
        Matrix result(this->rows, right.cols);

        for (size_t r = 0; r < this->rows; ++r)
            for (size_t c = 0; c < right.cols; ++c)
                for (size_t s = 0; s < this->cols; ++s) {
                    result(r, c) += ((*this)(r, s) * right(s, c));
                }

        //Если внеслись нули

        for (std::size_t a{ 0 }; a < result.coefs.size(); ++a)
        {
            if (result.coefs[a].value == 0)
            {
                result.coefs.erase(result.coefs.begin() + a);
                --a;
            }
        }


        return result;
    }
}

Matrix Matrix::Transpose() const
{
    Matrix result(*this);

    for (auto& elem : result.coefs)
        std::swap(elem.i, elem.j);

    std::swap(result.rows, result.cols);

    return result;
}

void Matrix::SetRows(std::size_t NewR)
{
   for (std::size_t k{ 0 }; k < coefs.size(); ++k)
      if (coefs[k].i >= NewR)
          coefs.erase(coefs.begin() + k);

   this->rows = NewR;
}

void Matrix::SetCols(std::size_t NewC)
{
    for (std::size_t k{ 0 }; k < coefs.size(); ++k)
        if (coefs[k].j >= NewC)
            coefs.erase(coefs.begin() + k);

    this->cols = NewC;
}

std::size_t Matrix::GetRows() const
{
    return this->rows;
}

std::size_t Matrix::GetCols() const
{
    return this->cols;
}

std::vector<Matrix::coord> Matrix::GetCoefs() const
{
    return this->coefs;
}

double Matrix::operator()(std::size_t row, std::size_t col) const
{
    if ((row < this->rows) && (col < this->cols))
    {
        int val = 0;

        for (const auto& elem : this->coefs)
        {
            if (elem.i == row && elem.j == col)
                val = elem.value;
        }

        return val;
    }
}

double& Matrix::operator()(std::size_t row, std::size_t col)
{
    if ((row < this->rows) && (col < this->cols))
    {

        for (auto& elem : this->coefs)
        {
            if (elem.i == row && elem.j == col)
                return elem.value;
        }

        //Если в цикле не вышли, то такого элемента нет и его надо внести

        this->coefs.push_back({ row, col, 0 });

        for (auto& elem : this->coefs)
        {
            if (elem.i == row && elem.j == col)
                return elem.value;
        }
    }
}

Matrix operator*(double lambda, const Matrix& right)
{
    return (right * lambda);
}

std::ostream& operator<<(std::ostream& out, const Matrix& object)
{
    out << object.rows << ' ' << object.cols << '\n';

    for (std::size_t a{ 0 }; a < object.rows; ++a)
    {
        for (std::size_t b{ 0 }; b < object.cols; ++b)
        {
            if (b != object.cols - 1)
                out << object(a, b) << ' ';
            else
                out << object(a, b);
        }

        if(a!=object.cols-1)
            out << '\n';
    }

    return out;
}

std::istream& operator>>(std::istream& in, Matrix& object)
{
    in >> object.rows >> object.cols;

    for(std::size_t a{0};a<object.rows;++a)
        for (std::size_t b{ 0 }; b < object.cols; ++b)
        {
            int num;
            assert(in >> num);

            if (num != 0)
                object(a, b) = num;
        }
    return in;
}

bool Matrix::coord::operator==(const coord& right) const
{
    if (this->i == right.i && this->j == right.j && this->value == right.value)
        return true;

    return false;
}

#include <cassert>
#include <iostream>
#include "Matrix.hpp"

template <typename T>
Matrix<T>::Matrix(std::size_t const numberColumns, std::size_t const numberLines, T const initialValue) 
 : m_numberLines(numberLines), m_numberColumns(numberColumns), m_matrix(numberLines * numberColumns, initialValue)
{
    assert(m_numberLines > 0 && m_numberColumns > 0 && "The matrix cannot have a zero size");
}

template <typename T>
std::size_t Matrix<T>::numberLines() const noexcept
{
    return m_numberLines;
}

template <typename T>
std::size_t Matrix<T>::numberColumns() const noexcept
{
    return m_numberColumns;
}

template <typename T>
std::size_t Matrix<T>::offset(std::size_t const n, std::size_t const m) const noexcept
{
    /* assert(n < m_numberColumns && "Line requested invalid.");
    assert(m < m_numberLines && "Column requested invalid."); */
    std::size_t const index = m * m_numberColumns + n;
    // assert(index < m_numberLines * m_numberColumns && "The offset return a invalid index.");
    return index;
}

template <typename T>
T const& Matrix<T>::operator()(std::size_t n, std::size_t m) const
{
    return m_matrix[offset(n, m)];
}

template <typename T>
T & Matrix<T>::operator()(std::size_t n, std::size_t m)
{
    return m_matrix[offset(n, m)];
}

template <typename T>
Matrix<T> & Matrix<T>::operator+=(Matrix<T> const & matrix)
{
    assert(matrix.m_numberColumns == m_numberColumns && "The sum of two matrixes, requires that they be of the same size");
    assert(matrix.m_numberLines == m_numberLines && "The sum of two matrixes, requires that they be of the same size");

    for (std::size_t i { 0 }; i < m_numberLines; i++)
    {
        for (std::size_t j { 0 }; j < m_numberColumns; j++)
        {
            (*this)(i, j) += matrix(i, j);
        }
    }
    return *this;
}

template<typename T>
Matrix<T> operator+(Matrix<T> matrix_left, Matrix<T> const & matrix_right)
{
    return matrix_left += matrix_right;
}

template <typename T>
Matrix<T> & Matrix<T>::operator-=(Matrix<T> const & matrix)
{
    assert(matrix.m_numberColumns == m_numberColumns && "The sum of two matrixes, requires that they be of the same size");
    assert(matrix.m_numberLines == m_numberLines && "The sum of two matrixes, requires that they be of the same size");

    for (std::size_t i { 0 }; i < m_numberLines; i++)
    {
        for (std::size_t j { 0 }; j < m_numberColumns; j++)
        {
            (*this)(i, j) -= matrix(i, j);
        }
    }
    return *this;
}

template<typename T>
Matrix<T> operator-(Matrix<T> matrix_left, Matrix<T> const & matrix_right)
{
    return matrix_left -= matrix_right;
}

template <typename T>
Matrix<T> & Matrix<T>::operator*=(int const multiplier)
{
    for (std::size_t i { 0 }; i < m_numberLines; i++)
    {
        for (std::size_t j { 0 }; j < m_numberColumns; j++)
        {
            (*this)(i, j) *= multiplier;
        }
    }
    return *this;
}

template<typename T>
Matrix<T> operator*(Matrix<T> matrix, int const multiplier)
{
    return matrix *= multiplier;
}

template<typename T>
Matrix<T> operator*(int const multiplier, Matrix<T> matrix)
{
    return matrix * multiplier;
}

template<typename T>
Matrix<T> operator*(Matrix<T> const & matrix_left, Matrix<T> const & matrix_right)
{
    assert(matrix_left.numberColumns() == matrix_right.numberLines() && "The seconde matrix must have the same number of collons as the line on the first matrix");
    // Attend il y a pas une formule de pour verifier mutiplication M(i x n) * M(n x j) = M(i x j) i nombres de lignes, j nombres de colonnes.
    Matrix<T> destination {matrix_left.numberLines(), matrix_right.numberColumns()};
    for (std::size_t i { 0 }; i < matrix_left.numberLines() * matrix_right.numberColumns(); i++)
    {
        std::size_t const n = i % matrix_right.numberColumns();
        std::size_t const m = i / matrix_right.numberColumns();
        T summe = 0;
        for (std::size_t j { 0 }; j < matrix_left.numberColumns() ; j++)
        {
            std::cout << n << ':' << m << std::endl;
            summe += matrix_left(j, m) * matrix_right(n, j);
        }
        destination(n, m) = summe;
    }
    return destination;
}

template <typename T>
Matrix<T> & Matrix<T>::operator*=(Matrix<T> const & matrix)
{
    (*this) = (*this) * matrix;
    return *this;
}

template <typename T>
std::ostream & operator<<(std::ostream & out, Matrix<T> const& matrix)
{
    for (std::size_t i { 0 }; i < matrix.numberLines(); i++)
    {
        for (std::size_t j { 0 }; j < matrix.numberColumns(); j++)
        {
            out << "| " << matrix(j, i) << ' ';
        }
        out << '|' << std::endl;
    }
    return out;
}

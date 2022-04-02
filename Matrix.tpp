#include "Matrix.hpp"
#include <cassert>
#include <algorithm>
#include <string>
#include <iostream>
#include <cmath>

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr
Matrix<T, LINES, COLUMNS>::Matrix(T const initialValue)
{
	std::fill(std::begin(m_matrix), std::end(m_matrix), initialValue);
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t
Matrix<T, LINES, COLUMNS>::numberLines() const noexcept
{
	return LINES;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t
Matrix<T, LINES, COLUMNS>::numberColumns() const noexcept
{
	return COLUMNS;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t
Matrix<T, LINES, COLUMNS>::offset(std::size_t const lines,
	std::size_t const columns) const noexcept
{
	assert(lines < numberLines() && "Column requested invalid.");
	assert(columns < numberColumns() && "Line requested invalid.");
	return lines * numberColumns() + columns;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr T const&
Matrix<T, LINES, COLUMNS>::operator() (std::size_t const lines,
	std::size_t const columns) const noexcept
{
	return m_matrix[offset(lines, columns)];
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr T&
Matrix<T, LINES, COLUMNS>::operator() (std::size_t const lines,
	std::size_t const columns)
{
	return m_matrix[offset(lines, columns)];
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>&
Matrix<T, LINES, COLUMNS>::operator+= (Matrix<T, LINES, COLUMNS> const& matrix) noexcept
{
	for (std::size_t i{ 0 }; i < numberLines(); i++)
	{
		for (std::size_t j{ 0 }; j < numberColumns(); j++)
		{
			(*this) (i, j) += matrix(i, j);
		}
	}
	return *this;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>
operator+ (Matrix<T, LINES, COLUMNS> matrix_left,
	Matrix<T, LINES, COLUMNS> const& matrix_right) noexcept
{
	return matrix_left += matrix_right;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>&
Matrix<T, LINES, COLUMNS>::operator-= (Matrix<T, LINES, COLUMNS> const& matrix) noexcept
{
	assert(matrix.numberLines() == numberLines()
		&& "The subtraction of two matrixes, requires that they be of the "
		"same size");
	assert(matrix.numberColumns() == numberColumns()
		&& "The subtraction of two matrixes, requires that they be of the "
		"same size");

	for (std::size_t i{ 0 }; i < numberLines(); i++)
	{
		for (std::size_t j{ 0 }; j < numberColumns(); j++)
		{
			(*this) (i, j) -= matrix(i, j);
		}
	}
	return *this;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>
operator- (Matrix<T, LINES, COLUMNS> matrix_left,
	Matrix<T, LINES, COLUMNS> const& matrix_right) noexcept
{
	return matrix_left -= matrix_right;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>&
Matrix<T, LINES, COLUMNS>::operator*= (int const multiplier) noexcept
{
	for (std::size_t i{ 0 }; i < numberLines(); i++)
	{
		for (std::size_t j{ 0 }; j < numberColumns(); j++)
		{
			(*this) (i, j) *= multiplier;
		}
	}
	return *this;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>
operator* (Matrix<T, LINES, COLUMNS> matrix, int const multiplier) noexcept
{
	return matrix *= multiplier;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>
operator* (int const multiplier, Matrix<T, LINES, COLUMNS> matrix) noexcept
{
	return matrix * multiplier;
}

template <typename T, std::size_t LINES_M1, std::size_t SHARED,
	std::size_t COLUMNS_M2>
	constexpr Matrix<T, LINES_M1, COLUMNS_M2>
	operator* (Matrix<T, LINES_M1, SHARED> const& matrix_left,
		Matrix<T, SHARED, COLUMNS_M2> const& matrix_right) noexcept
{

	Matrix<T, LINES_M1, COLUMNS_M2> destination{};
	for (std::size_t i{ 0 }; i < matrix_left.numberLines(); i++)
	{
		for (std::size_t j{ 0 }; j < matrix_right.numberColumns(); j++)
		{
			T summe = 0;
			for (std::size_t k{ 0 }; k < matrix_left.numberColumns(); k++)
			{
				summe += matrix_left(i, k) * matrix_right(k, j);
			}
			destination(i, j) = summe;
		}
	}
	return destination;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t Matrix<T, LINES, COLUMNS>::strSize(T const value) const
{
	std::size_t size{ 1 };
	if (std::is_integral<T>())
	{
		if (value != 0)
		{
			size = log10(value) + 1;
		}
	}
	else
	{
		std::string str{ std::to_string(value) };
		size = std::size(str);
	}
	return size;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t Matrix<T, LINES, COLUMNS>::strSizeMax() const
{
	std::size_t maxSize{ 0 };
	for (T const e : m_matrix)
	{
		std::size_t size = strSize(e);
		if (size > maxSize)
		{
			maxSize = size;
		}
	}

	return maxSize;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
std::ostream&
operator<< (std::ostream& out, Matrix<T, LINES, COLUMNS> const& matrix)
{
	std::size_t maxSize{ matrix.strSizeMax() };

	for (std::size_t i{ 0 }; i < matrix.numberLines(); i++)
	{

		for (std::size_t j{ 0 }; j < matrix.numberColumns(); j++)
		{
			std::size_t size = maxSize - matrix.strSize(matrix(i, j));

			out << "|";
			for (std::size_t k{ 0 }; k < size % 2 + 1 || k < 1; k++)
			{
				out << ' ';
			}
			out << matrix(i, j);
			for (std::size_t k{ 0 }; k < size % 2 || k < 1; k++)
			{
				out << ' ';
			}
		}
		out << '|' << std::endl;
	}
	return out;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, COLUMNS, LINES>
Matrix<T, LINES, COLUMNS>::transposed() const noexcept
{
	Matrix<T, COLUMNS, LINES> trans{};
	for (std::size_t i{ 0 }; i < numberLines(); i++)
	{
		for (std::size_t j{ 0 }; j < numberColumns(); j++)
		{
			trans(j, i) = (*this) (i, j);
		}
	}
	return trans;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, 1, COLUMNS>
Matrix<T, LINES, COLUMNS>::line(std::size_t const indexLine) const noexcept
{
	assert(indexLine < numberLines() && "index outside the matrix");
	Matrix<T, 1, COLUMNS> cpyLine{};
	for (std::size_t i{ 0 }; i < numberColumns(); i++)
	{
		cpyLine(0, i) = (*this) (indexLine, i);
	}
	return cpyLine;
}

template <typename T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, 1>
Matrix<T, LINES, COLUMNS>::column(
	std::size_t const indexColumn) const noexcept
{
	assert(indexColumn < numberColumns() && "index outside the matrix");
	Matrix<T, LINES, 1> cpyLine{};
	for (std::size_t i{ 0 }; i < numberLines(); i++)
	{
		cpyLine(i, 0) = (*this) (i, indexColumn);
	}
	return cpyLine;
}

#include <cassert>
#include <algorithm>
#include <string>
#include <ostream>
#include <iomanip>
#include <cmath>
#include "Matrix.hpp"

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>::Matrix(T const initialValue)
{
	std::fill(std::begin(m_matrix), std::end(m_matrix), initialValue);
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>::Matrix(std::initializer_list<std::initializer_list<T>> const & matrix) :
m_matrix()
{
	m_matrix = array_matrix_with_initializer_list(matrix);
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>::Matrix(SubBloc const& a, SubBloc const& b, SubBloc const& c, SubBloc const& d)
 : m_matrix()
{
	static_assert( (LINES % 2 == 0 || COLUMNS % 2 == 0) 
						&& "Le constructeur par bloc n'est valable que pour des matrices de taille pair" );
	constexpr std::size_t N { LINES/2 };
	constexpr std::size_t M { COLUMNS/2 };

	for (std::size_t i {0}; i < N; i++)
	{
		for (std::size_t j {0}; j < M; j++)
		{
			m_matrix[offset(i, j)] = a(i, j);
			m_matrix[offset(i, j + M)] = b(i, j);
			m_matrix[offset(i + N, j)] = c(i, j);
			m_matrix[offset(i + N, j + M)] = d(i, j);
		}
	}
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t
Matrix<T, LINES, COLUMNS>::numberLines() const noexcept
{
	return LINES;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t
Matrix<T, LINES, COLUMNS>::numberColumns() const noexcept
{
	return COLUMNS;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t
Matrix<T, LINES, COLUMNS>::offset(std::size_t const lines,
								  std::size_t const columns) const noexcept
{
	assert(lines < numberLines() && "Column requested invalid.");
	assert(columns < numberColumns() && "Line requested invalid.");
	return lines * numberColumns() + columns;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr T const &
Matrix<T, LINES, COLUMNS>::operator()(std::size_t const lines,
									  std::size_t const columns) const noexcept
{
	return m_matrix[offset(lines, columns)];
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr T &
Matrix<T, LINES, COLUMNS>::operator()(std::size_t const lines,
									  std::size_t const columns)
{
	return m_matrix[offset(lines, columns)];
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>
Matrix<T, LINES, COLUMNS>::operator+=(Matrix<T, LINES, COLUMNS> const &matrix) noexcept
{
	for (std::size_t i{0}; i < numberLines(); i++)
	{
		for (std::size_t j{0}; j < numberColumns(); j++)
		{
			(*this)(i, j) += matrix(i, j);
		}
	}
	return *this;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>
operator+(Matrix<T, LINES, COLUMNS> matrix_left,
		  Matrix<T, LINES, COLUMNS> const &matrix_right) noexcept
{
	return matrix_left += matrix_right;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>
Matrix<T, LINES, COLUMNS>::operator-=(Matrix<T, LINES, COLUMNS> const &matrix) noexcept
{
	assert(matrix.numberLines() == numberLines() && "The subtraction of two matrixes, requires that they be of the "
													"same size");
	assert(matrix.numberColumns() == numberColumns() && "The subtraction of two matrixes, requires that they be of the "
														"same size");

	for (std::size_t i{0}; i < numberLines(); i++)
	{
		for (std::size_t j{0}; j < numberColumns(); j++)
		{
			(*this)(i, j) -= matrix(i, j);
		}
	}
	return *this;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS>
operator-(Matrix<T, LINES, COLUMNS> matrix_left,
		  Matrix<T, LINES, COLUMNS> const &matrix_right) noexcept
{
	return matrix_left -= matrix_right;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS> &
Matrix<T, LINES, COLUMNS>::operator*=(int const multiplier) noexcept
{
	for (std::size_t i{0}; i < numberLines(); i++)
	{
		for (std::size_t j{0}; j < numberColumns(); j++)
		{
			(*this)(i, j) *= multiplier;
		}
	}
	return *this;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS, arithmetic V>
constexpr Matrix<T, LINES, COLUMNS>
operator*(Matrix<T, LINES, COLUMNS> matrix, V const multiplier) noexcept
{
	return matrix *= multiplier;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS, arithmetic V>
constexpr Matrix<T, LINES, COLUMNS>
operator*(V const multiplier, Matrix<T, LINES, COLUMNS> matrix) noexcept
{
	return matrix * multiplier;
}

template <MathObj T, std::size_t LINES_M1, std::size_t SHARED,
		  std::size_t COLUMNS_M2>
constexpr Matrix<T, LINES_M1, COLUMNS_M2>
operator*(Matrix<T, LINES_M1, SHARED> const &matrix_left,
		  Matrix<T, SHARED, COLUMNS_M2> const &matrix_right) noexcept
{

	Matrix<T, LINES_M1, COLUMNS_M2> destination{};
	for (std::size_t i{0}; i < matrix_left.numberLines(); i++)
	{
		for (std::size_t j{0}; j < matrix_right.numberColumns(); j++)
		{
			T summe = 0;
			for (std::size_t k{0}; k < matrix_left.numberColumns(); k++)
			{
				summe += matrix_left(i, k) * matrix_right(k, j);
			}
			destination(i, j) = summe;
		}
	}
	return destination;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t Matrix<T, LINES, COLUMNS>::strSize(T const value) const
{
	std::size_t size{1};
	if constexpr (std::is_integral<T>())
	{
		if (value != 0)
		{
			size = static_cast<std::size_t>(std::log10(value)) + 1;
		}
	}
	else
	{
		std::string str{std::to_string(value)};
		size = std::size(str);
	}
	return size;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::size_t Matrix<T, LINES, COLUMNS>::strSizeMax() const
{
	std::size_t maxSize{0};
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

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
std::ostream &
operator<<(std::ostream &out, Matrix<T, LINES, COLUMNS> const &matrix)
{
	std::size_t maxSize{matrix.strSizeMax()};
	out << std::setfill(' ');
	if constexpr (LINES == 1)
	{
		out << "( ";
		std::for_each(std::begin(matrix.m_matrix), std::end(matrix.m_matrix), 
		[&out](T const& v) -> void
		{
			out << v << ' ';
		});
		out << ')' << std::endl;
		return out;
	}
	else
	{
		out << "/ ";
	}
	for (std::size_t i{0}; i < matrix.numberLines(); i++)
	{
		if (i == matrix.numberLines() -1)
		{
			out << "\\ ";
		}
		else if (i > 0)
		{
			out << "| ";
		}
		for (std::size_t j{0}; j < matrix.numberColumns(); j++)
		{
			std::size_t const size = maxSize - matrix.strSize(matrix(i, j));
			out << std::setw(static_cast<int>(size)) << matrix(i, j) << ' ';
		}
		if (i == 0)
		{
			out << '\\' << std::endl;
		}
		else if (i < matrix.numberLines() -1)
		{
			out << '|' << std::endl;
		}
	}
	if constexpr (LINES == 1)
	{
		out << ")" << std::endl;
	}
	else
	{
		out << "/ " << std::endl;
	}
	/*
	for (std::size_t i{0}; i < matrix.numberLines(); i++)
	{

		for (std::size_t j{0}; j < matrix.numberColumns(); j++)
		{
			std::size_t size = maxSize - matrix.strSize(matrix(i, j));

			out << "|";
			for (std::size_t k{0}; k < size % 2 + 1 || k < 1; k++)
			{
				out << ' ';
			}
			out << matrix(i, j);
			for (std::size_t k{0}; k < size % 2 || k < 1; k++)
			{
				out << ' ';
			}
		}
		out << '|' << std::endl;
	}*/
	return out;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, COLUMNS, LINES>
Matrix<T, LINES, COLUMNS>::transposed() const noexcept
{
	Matrix<T, COLUMNS, LINES> trans{};
	for (std::size_t i{0}; i < numberLines(); i++)
	{
		for (std::size_t j{0}; j < numberColumns(); j++)
		{
			trans(j, i) = (*this)(i, j);
		}
	}
	return trans;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, 1, COLUMNS>
Matrix<T, LINES, COLUMNS>::line(std::size_t const indexLine) const noexcept
{
	assert(indexLine < numberLines() && "index outside the matrix");
	Matrix<T, 1, COLUMNS> cpyLine{};
	for (std::size_t i{0}; i < numberColumns(); i++)
	{
		cpyLine(0, i) = (*this)(indexLine, i);
	}
	return cpyLine;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, 1>
Matrix<T, LINES, COLUMNS>::column(
	std::size_t const indexColumn) const noexcept
{
	assert(indexColumn < numberColumns() && "index outside the matrix");
	Matrix<T, LINES, 1> cpyLine{};
	for (std::size_t i{0}; i < numberLines(); i++)
	{
		cpyLine(i, 0) = (*this)(i, indexColumn);
	}
	return cpyLine;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr std::array<T, COLUMNS*LINES>
Matrix<T, LINES, COLUMNS>::array_matrix_with_initializer_list(
	std::initializer_list<std::initializer_list<T>> const & matrix
)
{
	std::array<T, COLUMNS*LINES> array_matrix = {};
	auto it_mat_dst { std::begin(array_matrix) };
	for (std::initializer_list<T> const & e : matrix)
	{
		std::size_t const size_sub_list { std::size(e) };
		assert(size_sub_list <= COLUMNS && "Value entry out of matrix");
		std::move(std::begin(e), std::end(e), it_mat_dst);
		it_mat_dst += COLUMNS;
	}
	return array_matrix;
}

template <MathObj T, std::size_t LINES, std::size_t COLUMNS>
constexpr Matrix<T, LINES, COLUMNS> Matrix<T, LINES, COLUMNS>::identity() noexcept
{
	static_assert(LINES == COLUMNS && "not identity matrix in non square matrix");
	Matrix<T, LINES, COLUMNS> Id {};
	for (std::size_t i { 0 }; i < LINES; i++)
	{
		Id(i, i) = static_cast<T>(1);
	}
	return Id;
}

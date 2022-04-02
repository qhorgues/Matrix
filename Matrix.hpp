#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <type_traits>

template <typename T, std::size_t LINES, std::size_t COLUMNS>
class Matrix final
{
	static_assert (std::is_arithmetic_v<T>,
		"The type of a matrix must be floating or real");
	static_assert (LINES > 0 || COLUMNS > 0,
		"The matrix cannot have a zero size");

public:
	Matrix() = default;
	constexpr Matrix(T const initialValue);
	constexpr ~Matrix() noexcept = default;

	Matrix(Matrix const& matrix) = default;
	Matrix& operator= (Matrix const& matrix) = default;

	Matrix(Matrix&& matrix) noexcept = default;
	Matrix& operator= (Matrix&& matrix) = default;

	constexpr std::size_t numberLines() const noexcept;
	constexpr std::size_t numberColumns() const noexcept;

	constexpr T const& operator() (std::size_t const lines,
		std::size_t const columns) const noexcept;
	constexpr T& operator() (std::size_t const lines, std::size_t const columns);

	constexpr Matrix<T, LINES, COLUMNS>&
		operator+= (Matrix<T, LINES, COLUMNS> const& matrix) noexcept;

	template <typename U, std::size_t N, std::size_t M>
	constexpr friend Matrix<U, N, M>
		operator+ (Matrix<U, N, M> matrix_left, Matrix<U, N, M> const& matrix_right) noexcept;

	constexpr Matrix<T, LINES, COLUMNS>&
		operator-= (Matrix<T, LINES, COLUMNS> const& matrix) noexcept;

	template <typename U, std::size_t N, std::size_t M>
	constexpr friend Matrix<U, N, M>
		operator- (Matrix<U, N, M> matrix_left, Matrix<U, N, M> const& matrix_right) noexcept;

	constexpr Matrix<T, LINES, COLUMNS>& operator*= (int const multiplier) noexcept;

	template <typename U, std::size_t N, std::size_t M>
	constexpr friend Matrix<U, N, M> operator* (Matrix<U, N, M> matrix,
		int const multiplier) noexcept;

	template <typename U, std::size_t N, std::size_t M>
	constexpr friend Matrix<U, N, M> operator* (int const multiplier,
		Matrix<U, N, M> matrix) noexcept;

	template <typename U, std::size_t LINES_M1, std::size_t SHARED,
		std::size_t COLUMNS_M2>
		constexpr friend Matrix<U, LINES_M1, COLUMNS_M2>
		operator* (Matrix<U, LINES_M1, SHARED> const& matrix_left,
			Matrix<U, SHARED, LINES_M1> const& matrix_right) noexcept;

	template <typename U, std::size_t N, std::size_t M>
	friend std::ostream& operator<< (std::ostream& out,
		Matrix<U, N, M> const& matrix);

	constexpr Matrix<T, COLUMNS, LINES> transposed() const noexcept;

	constexpr Matrix<T, 1, COLUMNS>
		line(std::size_t const indexLine) const noexcept;

	constexpr Matrix<T, LINES, 1>
		column(std::size_t const indexColumn) const noexcept;

private:
	constexpr std::size_t offset(std::size_t const lines,
		std::size_t const columns) const noexcept;

	constexpr std::size_t strSizeMax() const;
	constexpr std::size_t strSize(T const value) const;

	std::array<T, LINES* COLUMNS> m_matrix{ 0 };
};

#include "Matrix.tpp"

#endif // MATRIX_H
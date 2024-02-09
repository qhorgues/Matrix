#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>
#include <initializer_list>
#include <concepts>
#include <type_traits>
#include <ostream>

template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template <typename T>
concept MathObj = requires(T lhs, T rhs) {
	lhs + rhs == rhs + lhs;
	lhs - rhs;
	lhs *rhs;
};

template <MathObj T, std::size_t LINES, std::size_t COLUMNS = LINES>
class Matrix final
{
	static_assert(LINES > 0 || COLUMNS > 0,
				  "The matrix cannot have a zero size");

public:
	Matrix() = default;
	constexpr Matrix(T const initialValue);
	constexpr Matrix(std::initializer_list<std::initializer_list<T>> const &matrix);

	using SubBloc = Matrix<T, LINES / 2, COLUMNS / 2>;
	constexpr Matrix(SubBloc const &a, SubBloc const &b, SubBloc const &c, SubBloc const &d);

	constexpr ~Matrix() noexcept = default;

	Matrix(Matrix const &matrix) = default;
	Matrix &operator=(Matrix const &matrix) = default;

	Matrix(Matrix &&matrix) noexcept = default;
	Matrix &operator=(Matrix &&matrix) = default;

	constexpr std::size_t numberLines() const noexcept;
	constexpr std::size_t numberColumns() const noexcept;

	constexpr T const &operator()(std::size_t const lines,
								  std::size_t const columns) const noexcept;
	constexpr T &operator()(std::size_t const lines, std::size_t const columns);

	constexpr Matrix<T, LINES, COLUMNS>
	operator+=(Matrix<T, LINES, COLUMNS> const &matrix) noexcept;

	template <typename U, std::size_t N, std::size_t M>
	constexpr friend Matrix<U, N, M>
	operator+(Matrix<U, N, M> matrix_left, Matrix<U, N, M> const &matrix_right) noexcept;

	constexpr Matrix<T, LINES, COLUMNS>
	operator-=(Matrix<T, LINES, COLUMNS> const &matrix) noexcept;

	template <MathObj U, std::size_t N, std::size_t M>
	constexpr friend Matrix<U, N, M>
	operator-(Matrix<U, N, M> matrix_left, Matrix<U, N, M> const &matrix_right) noexcept;

	constexpr Matrix<T, LINES, COLUMNS> &operator*=(int const multiplier) noexcept;

	template <MathObj U, std::size_t N, std::size_t M, arithmetic V>
	constexpr friend Matrix<U, N, M> operator*(Matrix<U, N, M> matrix,
											   V const multiplier) noexcept;

	template <MathObj U, std::size_t N, std::size_t M, arithmetic V>
	constexpr friend Matrix<U, N, M> operator*(V const multiplier,
											   Matrix<U, N, M> matrix) noexcept;

	template <MathObj U, std::size_t LINES_M1, std::size_t SHARED,
			  std::size_t COLUMNS_M2>
	constexpr friend Matrix<U, LINES_M1, COLUMNS_M2>
	operator*(Matrix<U, LINES_M1, SHARED> const &matrix_left,
			  Matrix<U, SHARED, LINES_M1> const &matrix_right) noexcept;

	template <MathObj U, std::size_t N, std::size_t M>
	friend std::ostream &operator<<(std::ostream &out,
									Matrix<U, N, M> const &matrix);

	constexpr Matrix<T, COLUMNS, LINES> transposed() const noexcept;

	constexpr Matrix<T, 1, COLUMNS>
	line(std::size_t const indexLine) const noexcept;

	constexpr Matrix<T, LINES, 1>
	column(std::size_t const indexColumn) const noexcept;

	constexpr static Matrix<T, LINES, COLUMNS> identity() noexcept;

private:
	constexpr std::size_t offset(std::size_t const lines,
								 std::size_t const columns) const noexcept;

	constexpr std::size_t strSizeMax() const;
	constexpr std::size_t strSize(T const value) const;

	constexpr std::array<T, COLUMNS * LINES>
	array_matrix_with_initializer_list(std::initializer_list<std::initializer_list<T>> const &matrix);

	std::array<T, LINES * COLUMNS> m_matrix{0};
};

#include "Matrix.tpp"

#endif // MATRIX_HPP

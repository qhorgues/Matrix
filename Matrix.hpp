#ifndef MATRIX_H
#define MATRIX_H

#include <type_traits>
#include <vector>

template <typename T = int/* , std::size_t N, std::size_t M */>
class Matrix final
{
    static_assert(std::is_arithmetic_v<T>, "The type of a matrix must be floating or real");
public:
    Matrix() = delete;
    Matrix(std::size_t const numberColumns, std::size_t const numberLines, T const initialValue = 0);
    ~Matrix() noexcept = default;
    

    Matrix(Matrix const & matrix) = default;
    Matrix& operator=(Matrix const& matrix) = default;

    Matrix(Matrix && matrix) noexcept = default;
    Matrix& operator=(Matrix && matrix)  = default;

    std::size_t numberLines() const noexcept;
    std::size_t numberColumns() const noexcept;

    T const& operator()(std::size_t n, std::size_t m) const;
    T & operator()(std::size_t n, std::size_t m);

    Matrix<T> & operator+=(Matrix<T> const & matrix);
    template<typename U> friend Matrix<U> operator+(Matrix<U> matrix_left, Matrix<U> const & matrix_right);

    Matrix<T> & operator-=(Matrix<T> const & matrix);
    template<typename U> friend Matrix<U> operator-(Matrix<U> matrix_left, Matrix<U> const & matrix_right);
    
    Matrix<T> & operator*=(int const multiplier);
    template<typename U> friend Matrix<U> operator*(Matrix<U> matrix, int const mutiplier);
    template<typename U> friend Matrix<U> operator*(int const multiplier, Matrix<U> matrix);

    Matrix<T> & operator*=(Matrix<T> const & matrix);
    template<typename U> friend Matrix<U> operator*(Matrix<U> const & matrix_left, Matrix<U> const & matrix_right);

    template<typename U> friend std::ostream & operator<<(std::ostream & out, Matrix<U> const& matrix);

private:
    std::size_t offset(std::size_t const n, std::size_t const m) const noexcept;
    std::size_t m_numberLines;
    std::size_t m_numberColumns;
    std::vector<T> m_matrix;
};

#include "Matrix.tpp"

#endif // MATRIX_H
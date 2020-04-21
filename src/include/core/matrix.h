#pragma once

#include <array>
#include <type_traits>

#include "core/coord.h"


namespace apc
{
    template<typename T, size_t rowsAmount, size_t columnsAmount>
    class Matrix
    {
    public:
        Matrix();

        Matrix(T defaultValue);

        template<size_t otherRowsAmount, size_t otherColumnsAmount, typename Enabled = typename std::enable_if<columnsAmount == otherRowsAmount, T>::type>
        Matrix<T, rowsAmount, otherColumnsAmount> operator*(const Matrix<T, otherRowsAmount, otherColumnsAmount>& other);

        Matrix<T, rowsAmount, columnsAmount> operator*(const T& other);

        Matrix<T, rowsAmount, columnsAmount> operator+(const Matrix<T, rowsAmount, columnsAmount>& other);

        Matrix<T, rowsAmount, columnsAmount> operator-(const Matrix<T, rowsAmount, columnsAmount>& other);

        Matrix<T, columnsAmount, rowsAmount> getTranspose() const;

        std::array<T, columnsAmount>& operator[](std::size_t idx);

        const std::array<T, columnsAmount>& operator[](std::size_t idx) const;

        template<size_t otherRowsAmount, size_t otherColumnsAmount, 
            typename Enabled = typename std::enable_if<columnsAmount == otherColumnsAmount && rowsAmount == otherRowsAmount, T>::type>
        Matrix<T, rowsAmount, columnsAmount>& operator=(const Matrix<T, otherRowsAmount, otherColumnsAmount>& other);

        bool operator==(const Matrix<T, rowsAmount, columnsAmount>& other);

        bool operator!=(const Matrix<T, rowsAmount, columnsAmount>& other);

        static Matrix<T, 3, 3> transpose(const Matrix<T, 3, 3> origin, const Coord<T>& offset);

        static Matrix<T, 3, 3> scale(const Matrix<T, 3, 3> origin, const Coord<T>& offset);

        static Matrix<T, 3, 3> rotate(const Matrix<T, 3, 3> origin, float angle);
    private:
        std::array<std::array<T, columnsAmount>, rowsAmount> m_data;
    };
}
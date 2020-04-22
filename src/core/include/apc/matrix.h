#pragma once

#include <array>
#include <type_traits>
#include <cmath>

#include "apc/math_utils.h"


namespace apc
{
    template<typename T>
    struct Coord;

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    class Matrix
    {
    public:
        Matrix();

        Matrix(T defaultValue);

        template<size_t otherRowsAmount, size_t otherColumnsAmount, typename Enabled = typename std::enable_if<columnsAmount == otherRowsAmount, T>::type>
        Matrix<T, rowsAmount, otherColumnsAmount> operator*(const Matrix<T, otherRowsAmount, otherColumnsAmount>& other) const;

        Matrix<T, rowsAmount, columnsAmount> operator*(const T& other) const;

        Matrix<T, rowsAmount, columnsAmount> operator+(const Matrix<T, rowsAmount, columnsAmount>& other) const;

        Matrix<T, rowsAmount, columnsAmount> operator-(const Matrix<T, rowsAmount, columnsAmount>& other) const;

        Matrix<T, columnsAmount, rowsAmount> getTranspose() const;

        std::array<T, columnsAmount>& operator[](std::size_t idx);

        const std::array<T, columnsAmount>& operator[](std::size_t idx) const;

        template<size_t otherRowsAmount, size_t otherColumnsAmount, 
            typename Enabled = typename std::enable_if<columnsAmount == otherColumnsAmount && rowsAmount == otherRowsAmount, T>::type>
        Matrix<T, rowsAmount, columnsAmount>& operator=(const Matrix<T, otherRowsAmount, otherColumnsAmount>& other);

        bool operator==(const Matrix<T, rowsAmount, columnsAmount>& other) const;

        bool operator!=(const Matrix<T, rowsAmount, columnsAmount>& other) const;

        static Matrix<T, 3, 3> translate(const Matrix<T, 3, 3>& origin, const Coord<T>& offset);

        static Matrix<T, 3, 3> scale(const Matrix<T, 3, 3>& origin, const Coord<T>& offset);

        static Matrix<T, 3, 3> rotate(const Matrix<T, 3, 3>& origin, float angle);

        static Matrix<T, 3, 3> cut(const Matrix<T, 3, 3>& origin, const T& left, const T& right, const T& top, const T& bottom);
    private:
        std::array<std::array<T, columnsAmount>, rowsAmount> m_data;
    };

    typedef Matrix<float, 3, 3> Matrixf33;

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, rowsAmount, columnsAmount>::Matrix()
    {
        m_data.fill(std::array<T, columnsAmount>());
        for(auto& data: m_data) {
            data.fill(0);
        }
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, rowsAmount, columnsAmount>::Matrix(T defaultValue)
    {
        m_data.fill(std::array<T, columnsAmount>());
        for(auto& data: m_data) {
            data.fill(0);
        }

        for(size_t i = 0; i < std::min(rowsAmount, columnsAmount); i++)
        {
            m_data[i][i] = defaultValue;
        }
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    std::array<T, columnsAmount>& Matrix<T, rowsAmount, columnsAmount>::operator[](std::size_t idx)
    {
        return m_data[idx];
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    const std::array<T, columnsAmount>& Matrix<T, rowsAmount, columnsAmount>::operator[](std::size_t idx) const
    {
        return m_data[idx];
    }


    template<typename T, size_t rowsAmount, size_t columnsAmount>
    template<size_t otherRowsAmount, size_t otherColumnsAmount, typename Enabled>
    Matrix<T, rowsAmount, columnsAmount>& Matrix<T, rowsAmount, columnsAmount>::operator=(const Matrix<T, otherRowsAmount, otherColumnsAmount>& other)
    {
        m_data = other.m_data;
        return *this;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    template<size_t otherRowsAmount, size_t otherColumnsAmount, typename Enabled>
    Matrix<T, rowsAmount, otherColumnsAmount> Matrix<T, rowsAmount, columnsAmount>::operator*(const Matrix<T, otherRowsAmount, otherColumnsAmount>& other) const
    {
        auto res = Matrix<T, rowsAmount, otherColumnsAmount>();
        for(size_t j = 0; j < rowsAmount; j++)
        {
            for(size_t i = 0; i < otherColumnsAmount; i++)
            {
                for(size_t k = 0; k < columnsAmount; k++)
                {
                    res[j][i] += m_data[j][k] * other[k][i];
                }
            }
        }
        return res;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, rowsAmount, columnsAmount> Matrix<T, rowsAmount, columnsAmount>::operator*(const T& other) const
    {
        Matrix<T, rowsAmount, columnsAmount> result; 
        for(int i = 0; i < rowsAmount; i++)
        {
            for(int j = 0; j < rowsAmount; j++)
            {
                result[j][i] = m_data[j][i] * other;
            }
        }
        return result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, rowsAmount, columnsAmount> Matrix<T, rowsAmount, columnsAmount>::operator+(const Matrix<T, rowsAmount, columnsAmount>& other) const
    {
        Matrix<T, rowsAmount, columnsAmount> result; 
        for(int i = 0; i < rowsAmount; i++)
        {
            for(int j = 0; j < rowsAmount; j++)
            {
                result[j][i] = m_data[j][i] + other[j][i];
            }
        }
        return result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, rowsAmount, columnsAmount> Matrix<T, rowsAmount, columnsAmount>::operator-(const Matrix<T, rowsAmount, columnsAmount>& other) const
    {
        Matrix<T, rowsAmount, columnsAmount> result; 
        for(int i = 0; i < rowsAmount; i++)
        {
            for(int j = 0; j < rowsAmount; j++)
            {
                result[j][i] = m_data[j][i] - other[j][i];
            }
        }
        return result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, columnsAmount, rowsAmount> Matrix<T, rowsAmount, columnsAmount>::getTranspose() const
    {
        Matrix<T, columnsAmount, rowsAmount> result;
        for(int i = 0; i < rowsAmount; i++)
        {
            for(int j = 0; j < rowsAmount; j++)
            {
                result[i][j] = m_data[j][i];
            }
        }
        return result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    bool Matrix<T, rowsAmount, columnsAmount>::operator==(const Matrix<T, rowsAmount, columnsAmount>& other) const
    {
        return m_data == other.m_data;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    bool Matrix<T, rowsAmount, columnsAmount>::operator!=( const Matrix<T, rowsAmount, columnsAmount>& other) const
    { 
        return !(*this == other); 
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, 3, 3> Matrix<T, rowsAmount, columnsAmount>::translate(const Matrix<T, 3, 3>& origin, const Coord<T>& offset)
    {
        Matrix<T, 3, 3> result(1);
        result[0][2] = offset.x; 
        result[1][2] = offset.y; 
        return origin * result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, 3, 3> Matrix<T, rowsAmount, columnsAmount>::scale(const Matrix<T, 3, 3>& origin, const Coord<T>& offset)
    {
        Matrix<T, 3, 3> result(1);
        result[0][0] = offset.x; 
        result[1][1] = offset.y; 
        return origin * result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, 3, 3> Matrix<T, rowsAmount, columnsAmount>::rotate(const Matrix<T, 3, 3>& origin, float angle)
    {
        Matrix<T, 3, 3> result(1);
        auto rad = radians(angle);
        result[0][0] = std::cos(rad); 
        result[0][1] = -std::sin(rad);
        result[1][0] = std::sin(rad); 
        result[1][1] = std::cos(rad);
        return origin * result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, 3, 3> Matrix<T, rowsAmount, columnsAmount>::cut(const Matrix<T, 3, 3>& origin, const T& left, const T& right, const T& top, const T& bottom)
    {
        Matrix<T, 3, 3> result(1);
        result[0][0] = static_cast<T>(2) / (right - left);
        result[1][1] = static_cast<T>(2) / (top - bottom);
        result[0][2] = -(right + left) / (right - left);
        result[1][2] = -(top + bottom) / (top - bottom);
        return origin * result;
    }
}
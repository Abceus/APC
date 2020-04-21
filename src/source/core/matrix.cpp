#include "core/matrix.h"

namespace apc
{
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
        Matrix();

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
    Matrix<T, rowsAmount, otherColumnsAmount> Matrix<T, rowsAmount, columnsAmount>::operator*(const Matrix<T, otherRowsAmount, otherColumnsAmount>& other)
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
    Matrix<T, rowsAmount, columnsAmount> Matrix<T, rowsAmount, columnsAmount>::operator*(const T& other)
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
    Matrix<T, rowsAmount, columnsAmount> Matrix<T, rowsAmount, columnsAmount>::operator+(const Matrix<T, rowsAmount, columnsAmount>& other)
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
    Matrix<T, rowsAmount, columnsAmount> Matrix<T, rowsAmount, columnsAmount>::operator-(const Matrix<T, rowsAmount, columnsAmount>& other)
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
    bool Matrix<T, rowsAmount, columnsAmount>::operator==(const Matrix<T, rowsAmount, columnsAmount>& other)
    {
        return m_data == other.m_data;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    bool Matrix<T, rowsAmount, columnsAmount>::operator!=( const Matrix<T, rowsAmount, columnsAmount>& other)
    { 
        return !(*this == other); 
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, 3, 3> Matrix<T, rowsAmount, columnsAmount>::transpose(const Matrix<T, 3, 3> origin, const Coord<T>& offset)
    {
        Matrix<T, 3, 3> result(1);
        result[0][2] = offset.x; 
        result[1][2] = offset.y; 
        return origin * result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, 3, 3> Matrix<T, rowsAmount, columnsAmount>::scale(const Matrix<T, 3, 3> origin, const Coord<T>& offset)
    {
        Matrix<T, 3, 3> result(1);
        result[0][0] = offset.x; 
        result[1][1] = offset.y; 
        return origin * result;
    }

    template<typename T, size_t rowsAmount, size_t columnsAmount>
    Matrix<T, 3, 3> Matrix<T, rowsAmount, columnsAmount>::rotate(const Matrix<T, 3, 3> origin, float angle)
    {
        Matrix<T, 3, 3> result(1);
        auto rad = radians(angle);
        result[0][0] = cos(rad); 
        result[0][1] = -sin(rad);
        result[1][0] = sin(rad); 
        result[1][1] = cos(rad);
        return origin * result;
    }
}
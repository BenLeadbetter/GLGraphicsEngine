#include "Matrix2.hpp"
#include "functions.hpp"

//

Matrix2::Matrix2(float value)
{
    for(int i = 0; i != 2; ++i)
        for(int j = 0; j != 2; ++j)
            setEntry(i, j, kroneckerDelta(i, j) * value);
}


template<typename T> Matrix2::Matrix2(
    T&& a00, T&& a01,
    T&& a10, T&& a11
    ):
data(
        {
            std::forward<T>(a00), std::forward<T>(a01),
            std::forward<T>(a10), std::forward<T>(a11)
        }
    )
{}


template Matrix2::Matrix2(
    float&&, float&&,
    float&&, float&&
    );

template Matrix2::Matrix2(
    float&, float&,
    float&, float&
    );


float Matrix2::det() const
{
    return getEntry(0, 0) * getEntry(1, 1) -
        getEntry(1, 0) * getEntry(0, 1);
}

float Matrix2::trace() const
{
    float ret = 0;

    for(int i = 0; i != 2; ++i)
        ret += getEntry(i, i);

    return ret;
}

Matrix2 Matrix2::inverse() const
{
    Matrix2 ret(
        getEntry(1, 1), -1.0f * getEntry(0, 1),
        -1.0f * getEntry(1, 0), getEntry(0, 0)
    );

    return ret / det();
}

Matrix2 Matrix2::transpose() const
{
    Matrix2 ret(
        getEntry(0, 0), getEntry(1, 0),
        getEntry(0, 1), getEntry(1, 1)
    );

    return ret;
}

template<typename T>
void Matrix2::setData(T&& arr)
{
    data = std::forward<T>(arr);
}

template void Matrix2::setData(std::array<float, 4>&&);
template void Matrix2::setData(std::array<float, 4>&);

float Matrix2::getEntry(short i, short j) const
{
    return data[2 * i + j];
}

void Matrix2::setEntry(short i, short j, float value)
{
    data[2 * i + j] = value; 
}

Vector2 Matrix2::getRow(short i) const
{
    Vector2 ret(getEntry(i, 0), getEntry(i, 1));

    return ret;
}

Vector2 Matrix2::getCol(short i) const
{
    Vector2 ret(getEntry(0, i), getEntry(1, i));

    return ret;
}

Matrix2 Matrix2::operator+(const Matrix2& rhs) const
{
    Matrix2 ret(
        getEntry(0, 0) + rhs.getEntry(0, 0),
        getEntry(0, 1) + rhs.getEntry(0, 1),
        getEntry(1, 0) + rhs.getEntry(1, 0),
        getEntry(1, 1) + rhs.getEntry(1, 1)
    );

    return ret;
}


Matrix2 Matrix2::operator-(const Matrix2& rhs) const
{
    Matrix2 ret(
        getEntry(0, 0) - rhs.getEntry(0, 0),
        getEntry(0, 1) - rhs.getEntry(0, 1),
        getEntry(1, 0) - rhs.getEntry(1, 0),
        getEntry(1, 1) - rhs.getEntry(1, 1)
    );

    return ret;
}


Matrix2 Matrix2::operator*(const Matrix2& rhs) const
{
    Matrix2 ret(
        dot(getRow(0), rhs.getCol(0)),
        dot(getRow(0), rhs.getCol(1)),
        dot(getRow(1), rhs.getCol(0)),
        dot(getRow(1), rhs.getCol(1))
    );

    return ret;
}

Matrix2& Matrix2::operator+=(const Matrix2& rhs)
{
    for(int i = 0; i != 2; ++i)
        for(int j = 0; j != 2; ++j)
            setEntry(i, j, getEntry(i, j) + rhs.getEntry(i, j));
    
    return *this;
}

Matrix2& Matrix2::operator-=(const Matrix2& rhs)
{
    for(int i = 0; i != 2; ++i)
        for(int j = 0; j != 2; ++j)
            setEntry(i, j, getEntry(i, j) - rhs.getEntry(i, j));
    
    return *this;
}

Matrix2& Matrix2::operator*=(const Matrix2& rhs)
{
    Matrix2 ret = *this * rhs;
    *this = ret;

    return *this;
}

Vector2 operator*(const Matrix2& mat, const Vector2& vec)
{
    Vector2 ret(
        dot(mat.getRow(0), vec),
        dot(mat.getRow(1), vec)
    );

    return ret;
}

Matrix2 operator*(const Matrix2& mat, const float& scalar)
{
    Matrix2 ret(
        mat.getEntry(0, 0) * scalar, mat.getEntry(0, 1) * scalar,
        mat.getEntry(1, 0) * scalar, mat.getEntry(1, 1) *scalar
    );

    return ret;
}

Matrix2 operator*(const float& scalar, const Matrix2& mat)
{
    Matrix2 ret(
        mat.getEntry(0, 0) * scalar, mat.getEntry(0, 1) * scalar,
        mat.getEntry(1, 0) * scalar, mat.getEntry(1, 1) * scalar
    );

    return ret;
}


Matrix2 operator/(const Matrix2& mat, const float& scalar)
{
    Matrix2 ret(
        mat.getEntry(0, 0) / scalar, mat.getEntry(0, 1) / scalar,
        mat.getEntry(1, 0) / scalar, mat.getEntry(1, 1) / scalar
    );

    return ret;
}
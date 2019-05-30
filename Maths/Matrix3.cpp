// source file for the Matrix3 class header

#include "Matrix3.hpp"
#include "functions.hpp"

Matrix3::Matrix3(float value)
{
    for(size_t i = 0; i != 9; ++i)
        data[i] = value * kroneckerDelta(i / 3, i % 3);
}

template<typename T>
Matrix3::Matrix3(
    T&& a00, T&& a01, T&& a02,
    T&& a10, T&& a11, T&& a12,
    T&& a20, T&& a21, T&& a22
    ):
    data(
        {
            std::forward<T>(a00),
            std::forward<T>(a01),
            std::forward<T>(a02),
            std::forward<T>(a10),
            std::forward<T>(a11),
            std::forward<T>(a12),
            std::forward<T>(a20),
            std::forward<T>(a21),
            std::forward<T>(a22)
        }
    )
{}

template Matrix3::Matrix3(
    float&&, float&&, float&&,
    float&&, float&&, float&&,
    float&&, float&&, float&&
);

template Matrix3::Matrix3(
    float&, float&, float&,
    float&, float&, float&,
    float&, float&, float&
);

float Matrix3::det() const
{
    float ret = 0; 
    
    for(int i = 0; i != 3; ++i)
    {
        int sign = i % 2 == 0 ? 1 : -1;
        ret += getEntry(0, i) * cofactor(0, i).det() * sign;
    }
    
    return ret;
}

float Matrix3::trace() const
{
    float ret = 0.0f;

    for(int i = 0; i != 3; ++i)
        ret += getEntry(i, i);
    
    return ret;
}

Matrix3 Matrix3::matrixOfCofactors() const
{
    Matrix3 ret(0.0f);

    for(int i = 0; i != 3; ++i)
        for(int j = 0; j != 3; ++j)
            ret.setEntry(i, j, cofactor(i, j).det());
    
    return ret;
}

Matrix3 Matrix3::adjoint() const
{
    Matrix3 ret = matrixOfCofactors();

    for(int i = 0; i != 3; ++i)
        for(int j = 0; j != 3; ++j)
        {
            float entry = ret.getEntry(i, j);
            entry *= (i + j) % 2 == 0 ? 1.0f : -1.0f;
            ret.setEntry(i, j, std::move(entry));
        }
    
    return ret;
}

Matrix3 Matrix3::inverse() const
{
    Matrix3 ret = adjoint();
    
    ret = ret.transpose();
    
    return ret / det();
}

Matrix3 Matrix3::transpose() const
{
    Matrix3 ret(0.0f);

    for(int i = 0; i != 3; ++i)
        for(int j = 0; j != 3; ++j)
            ret.setEntry(i, j, getEntry(j, i));
    
    return ret;
}


float cofactorIndex3(short ommitedIndex, short mappedIndex)
{
    static std::array<short, 2> arr0 {1, 2};
    static std::array<short, 2> arr1 {0, 2};
    static std::array<short, 2> arr2 {0, 1};

    if(ommitedIndex == 0)
        return arr0[mappedIndex];
    
    else if(ommitedIndex == 1)
        return arr1[mappedIndex];

    else if(ommitedIndex == 2)
        return arr2[mappedIndex];

    else
        return -1;
}

Matrix2 Matrix3::cofactor(short i, short j) const
{
    Matrix2 ret(
        getEntry(cofactorIndex3(i, 0), cofactorIndex3(j, 0)),
        getEntry(cofactorIndex3(i, 1), cofactorIndex3(j, 0)),
        getEntry(cofactorIndex3(i, 0), cofactorIndex3(j, 1)),
        getEntry(cofactorIndex3(i, 1), cofactorIndex3(j, 1))
    );

    return ret;
}

template<typename T>
void Matrix3::setData(T&& arr)
{
    data = std::forward<T>(arr);
}

template void Matrix3::setData(std::array<float, 9>&&);
template void Matrix3::setData(std::array<float, 9>&);

float Matrix3::getEntry(short row, short col) const
{
    return data[3 * row + col];
}

void Matrix3::setEntry(short row, short col, float value)
{
    data[3*row + col] = value;
}

Vector3 Matrix3::getRow(short i) const
{
    Vector3 ret;

    ret.setx(getEntry(i, 0));
    ret.sety(getEntry(i, 1));
    ret.setz(getEntry(i, 2));

    return ret;
}

Vector3 Matrix3::getCol(short i) const
{
    Vector3 ret;

    ret.setx(getEntry(0, i));
    ret.sety(getEntry(1, i));
    ret.setz(getEntry(2, i));

    return ret;
}

Matrix3 Matrix3::operator+(const Matrix3& rhs)
{
    Matrix3 ret(0.0f);

    for(size_t i = 0; i != 9; ++i)
        ret.data[i] = data[i] + rhs.data[i];
    
    return ret;
}

Matrix3 Matrix3::operator-(const Matrix3& rhs)
{
    Matrix3 ret(0.0f);

    for(size_t i = 0; i != 9; ++i)
        ret.data[i] = data[i] - rhs.data[i];

    return ret; 
}

Matrix3 Matrix3::operator*(const Matrix3& rhs)
{
    Matrix3 ret(0.0f);

    for(int i = 0; i != 3; ++i)
        for(int j = 0; j != 3; ++j)
            ret.setEntry(
                i, 
                j,
                dot(getRow(i), rhs.getCol(j))
            );
    
    return ret;
}

Matrix3& Matrix3::operator+=(const Matrix3& rhs)
{
    for(size_t i = 0; i != 9; ++i)
        data[i] += rhs.data[i];
    
    return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& rhs)
{
    for(size_t i = 0; i != 9; ++i)
        data[i] -= rhs.data[i];
    
    return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& rhs)
{
    Matrix3 ret(0.0f);

    for(int i = 0; i != 3; ++i)
        for(int j = 0; j != 3; ++j)
            ret.setEntry(
                i, 
                j,
                dot(getRow(i), rhs.getCol(j))
            );
    
    *this = ret;

    return *this;
}

Vector3 operator*(const Matrix3& mat, const Vector3& vec)
{
    Vector3 ret;

    ret.setx(dot(mat.getRow(0), vec));
    ret.sety(dot(mat.getRow(1), vec));
    ret.setz(dot(mat.getRow(2), vec));

    return ret;
}

Matrix3 operator*(const Matrix3& mat, const float& scalar)
{
    Matrix3 ret = mat;

    for(size_t i = 0; i != 9; ++i)
        ret.data[i] *= scalar;
    
    return ret;
}

Matrix3 operator*(const float& scalar, const Matrix3& mat)
{
    Matrix3 ret = mat;

    for(size_t i = 0; i != 9; ++i)
        ret.data[i] *= scalar;
    
    return ret;
}

Matrix3 operator/(const Matrix3& mat, const float& scalar)
{
    Matrix3 ret = mat;

    for(size_t i = 0; i != 9; ++i)
        ret.data[i] /= scalar;
    
    return ret;
}

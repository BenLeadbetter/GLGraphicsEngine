// source file for the Matrix3 class header

#include "Matrix4.hpp"
#include "functions.hpp"

Matrix4::Matrix4(float value)
{
    for(size_t i = 0; i != 16; ++i)
        data[i] = value * kroneckerDelta(i / 4, i % 4);
}


float Matrix4::det() const
{
    float ret = 0; 
    
    for(int i = 0; i != 4; ++i)
    {
        int sign = i % 2 == 0 ? 1 : -1;
        ret += getEntry(0, i) * cofactor(0, i).det() * sign;
    }

    return ret;
}

float Matrix4::trace() const
{
    float ret = 0.0f;

    for(int i = 0; i != 4; ++i)
        ret += getEntry(i, i);
    
    return ret;
}

Matrix4 Matrix4::matrixOfCofactors() const
{
    Matrix4 ret(0.0f);

    for(int i = 0; i != 4; ++i)
        for(int j = 0; j != 4; ++j)
            ret.setEntry(i, j, cofactor(i, j).det());
    
    return ret;
}

Matrix4 Matrix4::adjoint() const
{
    Matrix4 ret = matrixOfCofactors();

    for(int i = 0; i != 4; ++i)
        for(int j = 0; j != 4; ++j)
        {
            float entry = ret.getEntry(i, j);
            entry *= (i + j) % 2 == 0 ? 1.0f : -1.0f;
            ret.setEntry(i, j, std::move(entry));
        }
    
    return ret;
}

Matrix4 Matrix4::inverse() const
{
    Matrix4 ret = adjoint();
    
    ret = ret.transpose();
    
    return ret / det();
}

Matrix4 Matrix4::transpose() const
{
    Matrix4 ret(0.0f);

    for(int i = 0; i != 4; ++i)
        for(int j = 0; j != 4; ++j)
            ret.setEntry(i, j, getEntry(j, i));
    
    return ret;
}

float cofactorIndex4(short ommitedIndex, short mappedIndex)
{
    static std::array<short, 3> arr0 {1, 2, 3};
    static std::array<short, 3> arr1 {0, 2, 3};
    static std::array<short, 3> arr2 {0, 1, 3};
    static std::array<short, 3> arr3 {0, 1, 2};

    if(ommitedIndex == 0)
        return arr0[mappedIndex];
    
    else if(ommitedIndex == 1)
        return arr1[mappedIndex];

    else if(ommitedIndex == 2)
        return arr2[mappedIndex];
    
    else if(ommitedIndex == 3)
        return arr3[mappedIndex];

    else
        return -1;
}

Matrix3 Matrix4::cofactor(short i, short j) const
{
    Matrix3 ret(
        getEntry(cofactorIndex4(i, 0), cofactorIndex4(j, 0)),
        getEntry(cofactorIndex4(i, 0), cofactorIndex4(j, 1)),
        getEntry(cofactorIndex4(i, 0), cofactorIndex4(j, 2)),
        getEntry(cofactorIndex4(i, 1), cofactorIndex4(j, 0)),
        getEntry(cofactorIndex4(i, 1), cofactorIndex4(j, 1)),
        getEntry(cofactorIndex4(i, 1), cofactorIndex4(j, 2)),
        getEntry(cofactorIndex4(i, 2), cofactorIndex4(j, 0)),
        getEntry(cofactorIndex4(i, 2), cofactorIndex4(j, 1)),
        getEntry(cofactorIndex4(i, 2), cofactorIndex4(j, 2))
    );

    return ret;
}

template<typename T>
void Matrix4::setData(T&& arr)
{
    data = std::forward<T>(arr);
}

template void Matrix4::setData(std::array<float, 16>&&);
template void Matrix4::setData(std::array<float, 16>&);

float* Matrix4::getData()
{
    return data.data();
}

float Matrix4::getEntry(short row, short col) const
{
    return data[4 * row + col];
}

void Matrix4::setEntry(short row, short col, float value)
{
    data[4*row + col] = value;
}

Vector4 Matrix4::getRow(short i) const
{
    Vector4 ret;

    ret.setx(getEntry(i, 0));
    ret.sety(getEntry(i, 1));
    ret.setz(getEntry(i, 2));
    ret.setw(getEntry(i, 3));

    return ret;
}

Vector4 Matrix4::getCol(short i) const
{
    Vector4 ret;

    ret.setx(getEntry(0, i));
    ret.sety(getEntry(1, i));
    ret.setz(getEntry(2, i));
    ret.setw(getEntry(3, i));

    return ret;
}

Matrix4 Matrix4::operator+(const Matrix4& rhs)
{
    Matrix4 ret(0.0f);

    for(size_t i = 0; i != 16; ++i)
        ret.data[i] = data[i] + rhs.data[i];
    
    return ret;
}

Matrix4 Matrix4::operator-(const Matrix4& rhs)
{
    Matrix4 ret(0.0f);

    for(size_t i = 0; i != 16; ++i)
        ret.data[i] = data[i] - rhs.data[i];
    
    return ret;
}

Matrix4 Matrix4::operator*(const Matrix4& rhs)
{
    Matrix4 ret(0.0f);

    for(int i = 0; i != 4; ++i)
        for(int j = 0; j != 4; ++j)
            ret.setEntry(
                i, 
                j,
                dot(getRow(i), rhs.getCol(j))
            );
    
    return ret;
}

Matrix4& Matrix4::operator+=(const Matrix4& rhs)
{
    for(size_t i = 0; i != 16; ++i)
        data[i] += rhs.data[i];
    
    return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4& rhs)
{
    for(size_t i = 0; i != 16; ++i)
        data[i] -= rhs.data[i];
    
    return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4& rhs)
{
    Matrix4 ret(0.0f);

    for(int i = 0; i != 4; ++i)
        for(int j = 0; j != 4; ++j)
            ret.setEntry(
                i, 
                j,
                dot(getRow(i), rhs.getCol(j))
            );
    
    *this = ret;

    return *this;
}

Vector4 operator*(const Matrix4& mat, const Vector4& vec)
{
    Vector4 ret;

    ret.setx(dot(mat.getRow(0), vec));
    ret.sety(dot(mat.getRow(1), vec));
    ret.setz(dot(mat.getRow(2), vec));
    ret.setw(dot(mat.getRow(3), vec));

    return ret;
}

Matrix4 operator*(const Matrix4& mat, const float& scalar)
{
    Matrix4 ret = mat;

    for(size_t i = 0; i != 16; ++i)
        ret.data[i] *= scalar;
    
    return ret;
}

Matrix4 operator*(const float& scalar, const Matrix4& mat)
{
    Matrix4 ret = mat;

    for(size_t i = 0; i != 16; ++i)
        ret.data[i] *= scalar;
    
    return ret;
}

Matrix4 operator/(const Matrix4& mat, const float& scalar)
{
    Matrix4 ret = mat;

    for(size_t i = 0; i != 16; ++i)
        ret.data[i] /= scalar;
    
    return ret;
}


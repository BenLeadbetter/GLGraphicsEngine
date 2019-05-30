#ifndef GUARD_MATRIX_4_HPP
#define GUARD_MATRIX_4_HPP

#include <array>
#include "Vector4.hpp"
#include "Matrix3.hpp"

class Matrix4
{

    friend Vector4 operator*(const Matrix4&, const Vector4&);
    friend Matrix4 operator*(const Matrix4&, const float&);
    friend Matrix4 operator*(const float&, const Matrix4&);
    friend Matrix4 operator/(const Matrix4&, const float&);
    
    public:

        Matrix4(float);
        template<typename T> Matrix4(
            T&&, T&&, T&&, T&&,
            T&&, T&&, T&&, T&&,
            T&&, T&&, T&&, T&&,
            T&&, T&&, T&&, T&&
        );

        float det() const;
        float trace() const;
        Matrix4 matrixOfCofactors() const;
        Matrix4 adjoint() const;
        Matrix4 inverse() const;
        Matrix4 transpose() const;
        Matrix3 cofactor(short i, short j) const;

        template<typename T> void setData(T&&);
        float* getData();
        float getEntry(short row, short col) const;
        void setEntry(short row, short col, float value);
        Vector4 getRow(short i) const;
        Vector4 getCol(short i) const;

        //operators
        Matrix4 operator+(const Matrix4&);
        Matrix4 operator-(const Matrix4&);
        Matrix4 operator*(const Matrix4&);

        Matrix4& operator+=(const Matrix4&);
        Matrix4& operator-=(const Matrix4&);
        Matrix4& operator*=(const Matrix4&);


    private:

        std::array<float, 16> data;
};

Vector4 operator*(const Matrix4&, const Vector4&);
Matrix4 operator*(const Matrix4&, const float&);
Matrix4 operator*(const float&, const Matrix4&);
Matrix4 operator/(const Matrix4&, const float&);


template<typename T>
Matrix4::Matrix4(
    T&& a00, T&& a01, T&& a02, T&& a03,
    T&& a10, T&& a11, T&& a12, T&& a13,
    T&& a20, T&& a21, T&& a22, T&& a23,
    T&& a30, T&& a31, T&& a32, T&& a33
    ):
    data(
        {
            std::forward<T>(a00),
            std::forward<T>(a01),
            std::forward<T>(a02),
            std::forward<T>(a03),
            std::forward<T>(a10),
            std::forward<T>(a11),
            std::forward<T>(a12),
            std::forward<T>(a13),
            std::forward<T>(a20),
            std::forward<T>(a21),
            std::forward<T>(a22),
            std::forward<T>(a23),
            std::forward<T>(a30),
            std::forward<T>(a31),
            std::forward<T>(a32),
            std::forward<T>(a33)
        }
    )
{}


#endif
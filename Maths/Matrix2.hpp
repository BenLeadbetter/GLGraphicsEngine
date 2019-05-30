#ifndef GUARD_MATRIX_2_HPP
#define GUARD_MATRIX_2_HPP

#include <array>
#include "Vector2.hpp"

class Matrix2
{

    friend Vector2 operator*(const Matrix2&, const Vector2&);
    friend Matrix2 operator*(const Matrix2&, const float&);
    friend Matrix2 operator*(const float&, const Matrix2&);
    friend Matrix2 operator/(const Matrix2&, const float&);

    public:

        Matrix2(float);
        template<typename T> Matrix2(
            T&&, T&&,
            T&&, T&&
            );

        float det() const;
        float trace() const;
        Matrix2 inverse() const;
        Matrix2 transpose() const;

        template<typename T> void setData(T&&);
        float getEntry(short row, short col) const;
        void setEntry(short row, short col, float value);
        Vector2 getRow(short i) const;
        Vector2 getCol(short i) const;

        Matrix2 operator+(const Matrix2&) const;
        Matrix2 operator-(const Matrix2&) const;
        Matrix2 operator*(const Matrix2&) const;

        Matrix2& operator+=(const Matrix2&);
        Matrix2& operator-=(const Matrix2&);
        Matrix2& operator*=(const Matrix2&);

    private:

        std::array<float, 4> data;
};

Vector2 operator*(const Matrix2&, const Vector2&);
Matrix2 operator*(const Matrix2&, const float&);
Matrix2 operator*(const float&, const Matrix2&);
Matrix2 operator/(const Matrix2&, const float&);

#endif
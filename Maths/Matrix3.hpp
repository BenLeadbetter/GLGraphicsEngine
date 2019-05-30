#ifndef GUARD_MATRIX_3_HPP
#define GUARD_MATRIX_3_HPP

#include <array>
#include "Vector3.hpp"
#include "Matrix2.hpp"

class Matrix3
{

    friend Vector3 operator*(const Matrix3&, const Vector3&);
    friend Matrix3 operator*(const Matrix3&, const float&);
    friend Matrix3 operator*(const float&, const Matrix3&);
    friend Matrix3 operator/(const Matrix3&, const float&);

    public:
        Matrix3(float);
        template<typename T> Matrix3(
            T&&, T&&, T&&,
            T&&, T&&, T&&,
            T&&, T&&, T&&
            );

        //
        float det() const;
        float trace() const;
        Matrix3 matrixOfCofactors() const;
        Matrix3 adjoint() const;
        Matrix3 inverse() const;
        Matrix3 transpose() const;
        Matrix2 cofactor(short i, short j) const;

        //
        template<typename T> void setData(T&&);
        float getEntry(short row, short col) const;
        void setEntry(short row, short col, float value);
        Vector3 getRow(short i) const;
        Vector3 getCol(short i) const;
        
        // operators
        Matrix3 operator+(const Matrix3&);
        Matrix3 operator-(const Matrix3&);
        Matrix3 operator*(const Matrix3&);

        Matrix3& operator+=(const Matrix3&);
        Matrix3& operator-=(const Matrix3&);
        Matrix3& operator*=(const Matrix3&);


    private:
        
        std::array<float, 9> data;
};


Vector3 operator*(const Matrix3&, const Vector3&);
Matrix3 operator*(const Matrix3&, const float&);
Matrix3 operator*(const float&, const Matrix3&);
Matrix3 operator/(const Matrix3&, const float&);

#endif
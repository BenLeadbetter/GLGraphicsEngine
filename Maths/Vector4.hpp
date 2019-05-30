#ifndef GUARD_VECTOR_4_HPP
#define GUARD_VECTOR_4_HPP

#include <array>

class Vector3;

class Vector4
{
    friend std::ostream& operator<<(std::ostream& os, const Vector4& vec);
    friend Vector4 operator*(const float&, const Vector4&);
    friend float dot(const Vector4& lhs, const Vector4& rhs);
    friend Vector4 cross(const Vector4& lhs, Vector4& rhs);
    
    public:

        Vector4();
        template<typename T> Vector4(T&&, T&&, T&&, T&&);
        Vector4(const Vector3&);

        Vector4 operator+(const Vector4& rhs);
        Vector4 operator-(const Vector4& rhs);
        Vector4& operator +=(const Vector4& rhs);
        Vector4& operator -=(const Vector4& rhs);
        Vector4 operator*(const float&);
        Vector4 operator/(const float&);

        float magnitude() const;
        float squareMagnitude() const;
        Vector4 unitVector() const;
        void normalise();

        float x() const;
        float y() const;
        float z() const;
        float w() const;

        void setx(float);
        void sety(float);
        void setz(float);
        void setw(float);

    private:

        std::array<float, 4> data;
};

std::ostream& operator<<(std::ostream& os, const Vector4& vec);
Vector4 operator*(const float&, const Vector4&);

float dot(const Vector4& lhs, const Vector4& rhs);

#endif
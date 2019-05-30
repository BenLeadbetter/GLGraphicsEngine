#ifndef GUARD_VECTOR_2_HPP
#define GUARD_VECTOR_2_HPP

#include <array>
#include <ostream>

class Vector2
{
    friend Vector2 operator*(const float&, const Vector2&);
    friend float dot(const Vector2&, const Vector2&);
    
    public:

        Vector2();
        template<typename T> Vector2(T&&, T&&);

        Vector2 operator+(const Vector2&);
        Vector2 operator-(const Vector2&);
        Vector2& operator+=(const Vector2&);
        Vector2& operator-=(const Vector2&);
        Vector2 operator*(const float&);
        Vector2 operator/(const float&);

        float magnitude() const;
        float squareMagnitude() const;
        Vector2 unitVector() const;
        void normailise();

        float x() const;
        float y() const;

        void setx(float);
        void sety(float);


    private:

        std::array<float, 2> data;
};

std::ostream& operator<<(std::ostream& os, const Vector2&);
Vector2 operator*(const float&, const Vector2&);
float dot(const Vector2&, const Vector2&);

#endif
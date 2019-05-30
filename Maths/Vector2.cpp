// source file for the Vector2 class header

#include "Vector2.hpp"
#include <cmath>

Vector2::Vector2():
data(std::array<float, 2>{0, 0})
{}

template<typename T>
Vector2::Vector2(T&& x, T&& y):
data(
    {
        std::forward<T>(x),
        std::forward<T>(y)
    }
)
{}

template Vector2::Vector2(float&&, float&&);
template Vector2::Vector2(float&, float&);

Vector2 Vector2::operator+(const Vector2& rhs)
{
    Vector2 ret{
        data[0] + rhs.data[0],
        data[1] + rhs.data[1]
    };

    return ret;
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
    Vector2 ret{
        data[0] - rhs.data[0],
        data[1] - rhs.data[1]
    };

    return ret;
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
    data[0] += rhs.data[0];
    data[1] += rhs.data[1];

    return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
    data[0] -= rhs.data[0];
    data[1] -= rhs.data[1];

    return *this;
}

Vector2 Vector2::operator*(const float& scalar)
{
    Vector2 ret{
        data[0] * scalar,
        data[1] * scalar
    };

    return ret;
}

Vector2 Vector2::operator/(const float& scalar)
{
    Vector2 ret{
        data[0] / scalar,
        data[1] / scalar
    };

    return ret;
}

float Vector2::magnitude() const
{
    return std::sqrt(
        std::pow(data[0], 2) +
        std::pow(data[0], 2)
    );
}

float Vector2::squareMagnitude() const
{

    return std::pow(data[0], 2) +
        std::pow(data[0], 2);
}

Vector2 Vector2::unitVector() const
{
    Vector2 ret = *this;

    return ret / magnitude();
}

void Vector2::normailise()
{
    float mag = magnitude();

    data[0] /= mag;
    data[1] /= mag;
}

float Vector2::x() const
{
    return data[0];
}

float Vector2::y() const
{
    return data[1];
}

void Vector2::setx(float x)
{
    data[0] = x;
}

void Vector2::sety(float y)
{
    data[1] = y;
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
    os << "(" << vec.x() << ", " << vec.y() << ")";

    return os;
}

Vector2 operator*(const float& scalar, const Vector2& vec)
{
    Vector2 ret{
        vec.data[0] * scalar,
        vec.data[1] * scalar
    };

    return ret;
}

float dot(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.data[0] * rhs.data[0] +
        lhs.data[1] * rhs.data[1];
}


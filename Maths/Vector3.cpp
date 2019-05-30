/**
 *  Source file for the Vector3 class header
*/

#include "Vector3.hpp"
#include "Vector4.hpp"
#include <cmath>

Vector3::Vector3(): 
data(std::array<float, 3>{0, 0, 0})
{}

template<typename T>
Vector3::Vector3(T&& x, T&& y, T&& z):
data(
    {
        std::forward<T>(x),
        std::forward<T>(y),
        std::forward<T>(z)
    }
)
{}

template Vector3::Vector3(float&&, float&&, float&&);
template Vector3::Vector3(float&, float&, float&);

Vector3::Vector3(const Vector4& vec4):
data(
    {
        vec4.x(),
        vec4.y(),
        vec4.z()
    }
)
{}

Vector3 Vector3::operator+(const Vector3& rhs)
{
    return Vector3(
        this->x() + rhs.x(),
        this->y() + rhs.y(),
        this->z() + rhs.z()
        );
}

Vector3 Vector3::operator-(const Vector3& rhs)
{
    return Vector3(
        this->x() - rhs.x(),
        this->y() - rhs.y(),
        this->z() - rhs.z()
        );
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
    data[0] += rhs.data[0];
    data[1] += rhs.data[1];
    data[2] += rhs.data[2];

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
    data[0] -= rhs.data[0];
    data[1] -= rhs.data[1];
    data[2] -= rhs.data[2];

    return *this;
}

Vector3 Vector3::operator*(const float& scalar) const
{
    return Vector3(
        this->x() * scalar,
        this->y() * scalar,
        this->z() * scalar
    );
}

Vector3 Vector3::operator/(const float& scalar) const
{
    return Vector3(
        this->x() / scalar,
        this->y() / scalar,
        this->z() / scalar
    );
}

float Vector3::magnitude() const
{
    return std::sqrt(
        std::pow(data[0], 2) +
        std::pow(data[1], 2) +
        std::pow(data[2], 2)
    );
}

float Vector3::squareMagnitude() const
{
    return 
        std::pow(data[0], 2) +
        std::pow(data[1], 2) +
        std::pow(data[2], 2);
}

Vector3 Vector3::unitVector() const
{
    float magnitude = this->magnitude();

    return Vector3(
        data[0] / magnitude,
        data[1] / magnitude,
        data[2] / magnitude
    );
}

void Vector3::normalise()
{
    float magnitude = this->magnitude();

    data[0] /= magnitude;
    data[1] /= magnitude;
    data[2] /= magnitude;
}

float Vector3::x() const
{
    return data[0];
}

float Vector3::y() const
{
    return data[1];
}

float Vector3::z() const
{
    return data[2];
}

void Vector3::setx(float x)
{
    data[0] = x;
}

void Vector3::sety(float y)
{
    data[1] = y;
}

void Vector3::setz(float z)
{
    data[2] = z;
}

std::ostream& operator<<(std::ostream& os, const Vector3& vec)
{
    os << "(" << 
    vec.data[0] << ", " <<
    vec.data[1] << ", " <<
    vec.data[2] << ")";

    return os;
}

Vector3 operator*(const float& scalar, const Vector3& vec)
{
    return Vector3(
        vec.data[0] * scalar,
        vec.data[1] * scalar,
        vec.data[2] * scalar
    );
}

float dot(const Vector3& lhs, const Vector3& rhs)
{
    return 
        lhs.data[0] * rhs.data[0] +
        lhs.data[1] * rhs.data[1] +
        lhs.data[2] * rhs.data[2];
}

Vector3 cross(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(
        lhs.data[1] * rhs.data[2] - rhs.data[1] * lhs.data[2],
        rhs.data[0] * lhs.data[2] - lhs.data[0] * rhs.data[2],
        lhs.data[0] * rhs.data[1] - rhs.data[0] * lhs.data[1]
    );
}

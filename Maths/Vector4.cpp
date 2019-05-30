#include "Vector4.hpp"
#include "Vector3.hpp"
#include <ostream>
#include <cmath>

Vector4::Vector4():
data(std::array<float, 4>{0, 0, 0, 0})
{}

template<typename T>
Vector4::Vector4(T&& x, T&& y, T&& z, T&& w):
data(
    {
        std::forward<T>(x),
        std::forward<T>(y),
        std::forward<T>(z),
        std::forward<T>(w)
    }
)
{}

template Vector4::Vector4(float&&, float&&, float&&, float&&);
template Vector4::Vector4(float&, float&, float&, float&);

Vector4::Vector4(const Vector3& vec3):
data(
    {
        vec3.x(),
        vec3.y(),
        vec3.z(),
        1.0f
    }
)
{}

Vector4 Vector4::operator+(const Vector4& rhs)
{
    return Vector4(
        this->x() + rhs.x(),
        this->y() + rhs.y(),
        this->z() + rhs.z(),
        this->w() + rhs.w()
        );
}

Vector4 Vector4::operator-(const Vector4& rhs)
{
    return Vector4(
        this->x() - rhs.x(),
        this->y() - rhs.y(),
        this->z() - rhs.z(),
        this->w() - rhs.w()
        );
}

Vector4& Vector4::operator+=(const Vector4& rhs)
{
    data[0] += rhs.data[0];
    data[1] += rhs.data[1];
    data[2] += rhs.data[2];
    data[3] += rhs.data[3];

    return *this;
}

Vector4& Vector4::operator-=(const Vector4& rhs)
{
    data[0] -= rhs.data[0];
    data[1] -= rhs.data[1];
    data[2] -= rhs.data[2];
    data[3] -= rhs.data[3];

    return *this;
}

Vector4 Vector4::operator*(const float& scalar)
{
    return Vector4(
        this->x() * scalar,
        this->y() * scalar,
        this->z() * scalar,
        this->w() * scalar
    );
}

Vector4 Vector4::operator/(const float& scalar)
{
    return Vector4(
        this->x() / scalar,
        this->y() / scalar,
        this->z() / scalar,
        this->w() / scalar
    );
}

float Vector4::magnitude() const
{
    return std::sqrt(
        std::pow(data[0], 2) +
        std::pow(data[1], 2) +
        std::pow(data[2], 2) +
        std::pow(data[3], 2)
    );
}

float Vector4::squareMagnitude() const
{
    return 
        std::pow(data[0], 2) +
        std::pow(data[1], 2) +
        std::pow(data[2], 2) +
        std::pow(data[3], 2);
}

Vector4 Vector4::unitVector() const
{
    float magnitude = this->magnitude();

    return Vector4(
        data[0] / magnitude,
        data[1] / magnitude,
        data[2] / magnitude,
        data[3] / magnitude
    );
}

void Vector4::normalise()
{
    float magnitude = this->magnitude();

    data[0] /= magnitude;
    data[1] /= magnitude;
    data[2] /= magnitude;
    data[3] /= magnitude;
}

float Vector4::x() const
{
    return data[0];
}

float Vector4::y() const
{
    return data[1];
}

float Vector4::z() const
{
    return data[2];
}

float Vector4::w() const
{
    return data[3];
}

void Vector4::setx(float x)
{
    data[0] = x;
}

void Vector4::sety(float y)
{
    data[1] = y;
}

void Vector4::setz(float z)
{
    data[2] = z;
}

void Vector4::setw(float w)
{
    data[3] = w;
}

std::ostream& operator<<(std::ostream& os, const Vector4& vec)
{
    os << "(" << 
    vec.data[0] << ", " <<
    vec.data[1] << ", " <<
    vec.data[2] << ")";

    return os;
}
Vector4 operator*(const float& scalar, const Vector4& vec)
{
    return Vector4(
        vec.data[0] * scalar,
        vec.data[1] * scalar,
        vec.data[2] * scalar,
        vec.data[3] * scalar
    );
}

float dot(const Vector4& lhs, const Vector4& rhs)
{
    return 
        lhs.data[0] * rhs.data[0] +
        lhs.data[1] * rhs.data[1] +
        lhs.data[2] * rhs.data[2] +
        lhs.data[3] * rhs.data[3];
}

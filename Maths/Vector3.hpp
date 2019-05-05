#ifndef GUARD_VECTOR_3_HPP
#define GUARD_VECTOR_3_HPP

#include <array>
#include <ostream>

class Vector3
{
    friend std::ostream& operator<<(std::ostream&, const Vector3&);
    friend float dot(const Vector3&, const Vector3&);
    friend Vector3 cross(const Vector3&, const Vector3&);
    
    public:

        Vector3();
        Vector3(float x, float y, float z);
        
        Vector3 operator+(const Vector3& rhs);
        Vector3 operator-(const Vector3& rhs);
        Vector3& operator +=(const Vector3& rhs);
        Vector3& operator -=(const Vector3& rhs);
        Vector3 operator*(const float& scalar);
        Vector3 operator/(const float& scalar);

        float magnitude() const;
        float squareMagnitude() const;
        Vector3 unitVector() const;
        void normalise();

        float x() const;
        float y() const;
        float z() const;

        void setx(float);
        void sety(float);
        void setz(float);

    private:

        std::array<float, 3> data; 
};

std::ostream& operator<<(std::ostream& os, const Vector3& vec);
float dot(const Vector3& lhs, const Vector3& rhs);
Vector3 cross(const Vector3& lhs, const Vector3& rhs);



#endif
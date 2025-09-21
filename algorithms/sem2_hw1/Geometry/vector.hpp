#pragma once

namespace geometry {
  class Vector {
   private:
    int x_;
    int y_;
   public:
    Vector(int x, int y);

    int XCoord() const;
    int YCoord() const;

    Vector operator-() const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(int scalar) const;
    Vector operator/(int scalar) const;

    Vector& operator+=(const Vector& other);
    Vector& operator-=(const Vector& other);
    Vector& operator*=(int scalar);
    Vector& operator/=(int scalar);

    bool operator==(const Vector& other) const;
  };
}
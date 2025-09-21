#pragma once
#include "ishape.hpp"
#include "vector.hpp"
#include <string>
#include <memory>

namespace geometry {
  class Segment;

  class Point : public IShape {
   private:
    int x_;
    int y_;
   public:
    Point(int x, int y);

    int XCoord() const;
    int YCoord() const;

    Point operator+(const Vector& vec) const;

    Vector operator-(const Point& other) const;

    IShape& Move(const Vector& vector) override;
    bool ContainsPoint(const Point& point) const override;
    bool CrossesSegment(const Segment& segment) const override;
    std::unique_ptr<IShape> Clone() const override;
    std::string ToString() const override;
  };
}
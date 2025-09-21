#pragma once
#include "ishape.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "segment.hpp"
#include <string>

namespace geometry {
  class Circle : public IShape {
   private:
    Point center_;
    int rad_;
   public:
    Circle(const Point& center, int rad);

    IShape& Move(const Vector& vector) override;
    bool ContainsPoint(const Point& point) const override;
    bool CrossesSegment(const Segment& segment) const override;
    std::unique_ptr<IShape> Clone() const override;
    std::string ToString() const override;
  };
}
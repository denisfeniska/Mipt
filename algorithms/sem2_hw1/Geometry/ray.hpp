#pragma once
#include "ishape.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "segment.hpp"
#include <string>

namespace geometry {
  class Ray : public IShape {
   private:
    Point first_point_;
    Vector guide_vector_;
   public:
    Ray(const Point& first_point, const Point& direction_point);
    Ray(const Point& first_point, const Vector& guide_vector);

    IShape& Move(const Vector& vector) override;
    bool ContainsPoint(const Point& point) const override;
    bool CrossesSegment(const Segment& segment) const override;
    std::unique_ptr<IShape> Clone() const override;
    std::string ToString() const override;
  };
}
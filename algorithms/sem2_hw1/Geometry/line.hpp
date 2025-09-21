#pragma once
#include "ishape.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "segment.hpp"
#include <string>

namespace geometry {
  class Line : public IShape {
   private:
    Point first_point_;
    Point second_point_;

    Point GetAnyPoint() const;
    Point GetAnotherPoint() const;
   public:
    Line(const Point& first_point, const Point& second_point);

    IShape& Move(const Vector& vector) override;
    bool ContainsPoint(const Point& point) const override;
    bool CrossesSegment(const Segment& segment) const override;
    std::unique_ptr<IShape> Clone() const override;
    std::string ToString() const override;
  };
}
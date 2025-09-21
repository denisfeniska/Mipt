#pragma once
#include "ishape.hpp"
#include "point.hpp"
#include <string>

namespace geometry {
  class Segment : public IShape {
   private:
    Point first_;
    Point last_;
   public:
    Segment(const Point& first, const Point& last);

    const Point& First() const;
    const Point& End() const;

    IShape& Move(const Vector& vector) override;
    bool ContainsPoint(const Point& point) const override;
    bool CrossesSegment(const Segment& segment) const override;
    std::unique_ptr<IShape> Clone() const override;
    std::string ToString() const override;
  };
}
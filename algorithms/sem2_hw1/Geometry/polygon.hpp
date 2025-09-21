#pragma once
#include "ishape.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "segment.hpp"
#include <vector>
#include <string>

namespace geometry {
  class Polygon : public IShape {
    private:
     std::vector<Point> points_arr_;
    public:
     explicit Polygon(const std::vector<Point>& points_arr);

     IShape& Move(const Vector& vector) override;
     bool ContainsPoint(const Point& point) const override;
     bool CrossesSegment(const Segment& segment) const override;
     std::unique_ptr<IShape> Clone() const override;
     std::string ToString() const override;
  };
}
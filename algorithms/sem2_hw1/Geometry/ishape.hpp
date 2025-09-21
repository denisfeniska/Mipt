#pragma once
#include <string>
#include <memory>

namespace geometry {
  class Point;
  class Line;
  class Circle;
  class Polygon;
  class Ray;
  class Segment;
  class Vector;
  class IShape {
   public:
    virtual ~IShape() = default;
    virtual IShape& Move(const class Vector&) = 0;
    virtual bool ContainsPoint(const class Point&) const = 0;
    virtual bool CrossesSegment(const class Segment&) const = 0;
    virtual std::unique_ptr<IShape> Clone() const = 0;
    virtual std::string ToString() const = 0;
  };
}
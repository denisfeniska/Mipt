#include "../point.hpp"
#include "../vector.hpp"
#include "../segment.hpp"
#include <string>

namespace geometry {
  Point::Point(int x, int y) : x_(x), y_(y) {
  }

  int Point::XCoord() const {
    return x_;
  }
  int Point::YCoord() const {
    return y_;
  }

  Point Point::operator+(const Vector& vec) const {
    return {x_ + vec.XCoord(), y_ + vec.YCoord()};
  }

  Vector Point::operator-(const Point& other) const {
    return {x_ - other.x_, y_ - other.y_};
  }
  
  IShape& Point::Move(const Vector& vector) {
    x_ += vector.XCoord();
    y_ += vector.YCoord();
    return *this;
  }

  bool Point::ContainsPoint(const Point& point) const { 
    return (x_ == point.x_ && y_ == point.y_); 
  }

  bool Point::CrossesSegment(const Segment& segment) const {
    return segment.ContainsPoint(*this);
  }

  std::unique_ptr<IShape> Point::Clone() const { 
    return std::make_unique<Point>(*this); 
  }

  std::string Point::ToString() const { 
    return "Point(" + std::to_string(x_) + ", " + std::to_string(y_) + ")"; 
  }
}
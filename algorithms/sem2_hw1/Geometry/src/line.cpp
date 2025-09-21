#include "../line.hpp"
#include "../point.hpp"
#include "../vector.hpp"
#include "../segment.hpp"
#include <cmath>
#include <numeric>

namespace geometry {

  Line::Line(const Point& first_point, const Point& second_point) : first_point_(first_point), second_point_(second_point) {
  }

  IShape& Line::Move(const Vector& vector) {
    first_point_ = first_point_ + vector;
    second_point_ = second_point_ + vector;
    return *this;
  }

  bool Line::ContainsPoint(const Point& point) const {
    int delta_x = second_point_.XCoord() - first_point_.XCoord();
    int delta_y = second_point_.YCoord() - first_point_.YCoord();
    int offset_x = point.XCoord() - first_point_.XCoord();
    int offset_y = point.YCoord() - first_point_.YCoord();
    bool are_vectors_collinear = (delta_x * offset_y) == (delta_y * offset_x);
    return are_vectors_collinear;
  }

  bool Line::CrossesSegment(const Segment& segment) const {
    const int line_a = second_point_.YCoord() - first_point_.YCoord();
    const int line_b = first_point_.XCoord() - second_point_.XCoord();
    const int line_c = -(line_a * first_point_.XCoord() + line_b * first_point_.YCoord());
    const int first_end_value = line_a * segment.First().XCoord() + line_b * segment.First().YCoord() + line_c;
                              
    const int second_end_value = line_a * segment.End().XCoord()+ line_b * segment.End().YCoord() + line_c;
    const bool has_point_on_line = (first_end_value == 0) || (second_end_value == 0);
    const bool are_points_on_opposite_sides = (first_end_value < 0) != (second_end_value < 0);
    return has_point_on_line || are_points_on_opposite_sides;
  }

  std::unique_ptr<IShape> Line::Clone() const {
    return std::make_unique<Line>(*this);
  }

  std::string Line::ToString() const {
    int a = second_point_.YCoord() - first_point_.YCoord();
    int b = first_point_.XCoord() - second_point_.XCoord();
    int c = -(a * first_point_.XCoord() + b * first_point_.YCoord());

    int divisor = std::gcd(std::gcd(std::abs(a), std::abs(b)), std::abs(c));
    if (divisor != 0) {
      a /= divisor;
      b /= divisor;
      c /= divisor;
    }

    return "Line(" + std::to_string(a) + ", " + std::to_string(b) + ", " + std::to_string(c) + ")";
  }
}
#include "../segment.hpp"
#include "../vector.hpp"
#include "../point.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace geometry {
  Segment::Segment(const Point& first, const Point& last) : first_(first), last_(last) {
  }
  const Point& Segment::First() const {
    return first_;
  }
  const Point& Segment::End() const {
    return last_;
  }

  IShape& Segment::Move(const Vector& vector) {
    first_.Move(vector);
    last_.Move(vector);
    return *this;
  }

  bool Segment::ContainsPoint(const Point& point) const {
    if (first_.XCoord() == last_.XCoord() && first_.YCoord() == last_.YCoord()) {
      return first_.XCoord() == point.XCoord() && first_.YCoord() == point.YCoord();
    }    
    int dx = last_.XCoord() - first_.XCoord();
    int dy = last_.YCoord() - first_.YCoord();
    int dx_point = point.XCoord() - first_.XCoord();
    int dy_point = point.YCoord() - first_.YCoord();

    int64_t cross = static_cast<int64_t>(dx) * dy_point - static_cast<int64_t>(dy) * dx_point;
    if (cross != 0) {
      return false;
    }
    int64_t dot = static_cast<int64_t>(dx_point) * dx + static_cast<int64_t>(dy_point) * dy;
    if (dot < 0) {
      return false;
    }
    int64_t sq_len = static_cast<int64_t>(dx) * dx + static_cast<int64_t>(dy) * dy;
    return dot <= sq_len;
  }

  bool OnSegment(const Point& point1, const Point& point2, const Point& point3) {
    bool is_x_in_range = (point2.XCoord() <= std::max(point1.XCoord(), point3.XCoord())) && 
                         (point2.XCoord() >= std::min(point1.XCoord(), point3.XCoord()));
    bool is_y_in_range = (point2.YCoord() <= std::max(point1.YCoord(), point3.YCoord())) && 
                         (point2.YCoord() >= std::min(point1.YCoord(), point3.YCoord()));
    return is_x_in_range && is_y_in_range;
  }

  bool Segment::CrossesSegment(const Segment& segment) const {
    auto compute_orientation = [](const Point& p, const Point& q, const Point& r) {
        int64_t cross_product = static_cast<int64_t>(q.XCoord() - p.XCoord()) * (r.YCoord() - p.YCoord()) -
                                static_cast<int64_t>(q.YCoord() - p.YCoord()) * (r.XCoord() - p.XCoord());
        return (cross_product > 0) ? 1 : (cross_product < 0) ? -1 : 0;
    };

    const Point& a = first_;
    const Point& b = last_;
    const Point& c = segment.First();
    const Point& d = segment.End();

    int operation_1 = compute_orientation(a, b, c);
    int operation_2 = compute_orientation(a, b, d);
    int operation_3 = compute_orientation(c, d, a);
    int operation_4 = compute_orientation(c, d, b);

    if ((operation_1 != operation_2) && (operation_3 != operation_4)) {
      return true;
    }

    if (operation_1 == 0 && OnSegment(a, c, b)) {
      return true;
    }
    if (operation_2 == 0 && OnSegment(a, d, b)) {
      return true;
    }
    if (operation_3 == 0 && OnSegment(c, a, d)) {
      return true;
    }
    if (operation_4 == 0 && OnSegment(c, b, d)) {
      return true;
    }
    return false;
  }

  std::unique_ptr<IShape> Segment::Clone() const { 
    return std::make_unique<Segment>(*this); 
  }

  std::string Segment::ToString() const { 
    return "Segment(" + first_.ToString() + ", " + last_.ToString() + ")"; 
  }
}
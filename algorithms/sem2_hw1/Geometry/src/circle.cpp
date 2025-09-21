#include "../circle.hpp"
#include "../point.hpp"
#include "../vector.hpp"
#include "../segment.hpp"
#include <cmath>
#include <string>
#include <memory>
#include <algorithm>
#include <cstdint>

namespace geometry {
  Circle::Circle(const Point& center, int radius) : center_(center), rad_(radius) {}

  IShape& Circle::Move(const Vector& vector) {
    center_.Move(vector);
    return *this;
  }

  bool Circle::ContainsPoint(const Point& point) const {
    const int64_t dx = static_cast<int64_t>(point.XCoord()) - center_.XCoord();
    const int64_t dy = static_cast<int64_t>(point.YCoord()) - center_.YCoord();
    const int64_t squared_distance = dx * dx + dy * dy;
    const int64_t squared_radius = static_cast<int64_t>(rad_) * rad_;
    return squared_distance <= squared_radius;
  }

  bool Circle::CrossesSegment(const Segment& segment) const {
    const Point& segment_start = segment.First();
    const Point& segment_end = segment.End();
    const int64_t center_x = center_.XCoord();
    const int64_t center_y = center_.YCoord();
    const int64_t squared_radius = static_cast<int64_t>(rad_) * rad_;
    const auto squared_distance_from = [&](const Point& p) {
      const int64_t dx = p.XCoord() - center_x;
      const int64_t dy = p.YCoord() - center_y;
      return dx * dx + dy * dy;
    };

    const int64_t start_dist_sq = squared_distance_from(segment_start);
    const int64_t end_dist_sq = squared_distance_from(segment_end);
    if (start_dist_sq == squared_radius || end_dist_sq == squared_radius) {
      return true;
    }

    const bool start_inside = (start_dist_sq < squared_radius);
    const bool end_inside = (end_dist_sq < squared_radius);
    if (start_inside != end_inside) {
      return true;
    }

    if (!start_inside && !end_inside) {
      const Vector segment_vector = segment_end - segment_start;
      const double segment_length_sq = static_cast<double>(segment_vector.XCoord()) * segment_vector.XCoord() +
          static_cast<double>(segment_vector.YCoord()) * segment_vector.YCoord();
      if (segment_length_sq == 0.0) {
        return false;
      }

      const Vector center_to_start = center_ - segment_start;
      const double projection_param = 
          (segment_vector.XCoord() * center_to_start.XCoord() + segment_vector.YCoord() * center_to_start.YCoord()) / segment_length_sq;

      const double clamped_projection = std::clamp(projection_param, 0.0, 1.0);
      const double closest_x = segment_start.XCoord() + clamped_projection * segment_vector.XCoord();
      const double closest_y = segment_start.YCoord() + clamped_projection * segment_vector.YCoord();
      const double dx = closest_x - static_cast<double>(center_x);
      const double dy = closest_y - static_cast<double>(center_y);
      const double closest_dist_sq = dx * dx + dy * dy;
      return closest_dist_sq <= static_cast<double>(squared_radius);      
    }
    return false;
  }

  std::unique_ptr<IShape> Circle::Clone() const {
    return std::make_unique<Circle>(*this);
  }

  std::string Circle::ToString() const {
    return "Circle(" + center_.ToString() + ", " + std::to_string(rad_) + ")";
  }
}
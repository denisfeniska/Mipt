#include "../polygon.hpp"
#include "../point.hpp"
#include "../vector.hpp"
#include "../segment.hpp"
#include <algorithm>
#include <string>
#include <memory>
#include <vector>

namespace geometry {
  Polygon::Polygon(const std::vector<Point>& points_arr) : points_arr_(points_arr) {}
  IShape& Polygon::Move(const Vector& vector) {
    for (auto& elem : points_arr_) {
      elem.Move(vector);
    }
    return *this;
  }

  bool Polygon::ContainsPoint(const Point& point) const {
    int intersection_count = 0;
    const size_t vertex_count = points_arr_.size();
    for (size_t current_vertex_index = 0; current_vertex_index < vertex_count; ++current_vertex_index) {
      const Point& start_vertex = points_arr_[current_vertex_index];
      const Point& end_vertex = points_arr_[(current_vertex_index + 1) % vertex_count];
      if (Segment(start_vertex, end_vertex).ContainsPoint(point)) {
        return true;
      }
      const bool is_start_above = (start_vertex.YCoord() > point.YCoord());
      const bool is_end_above = (end_vertex.YCoord() > point.YCoord());
      const bool crosses_y_level = (is_start_above != is_end_above);

      if (crosses_y_level) {
        const double y_diff = point.YCoord() - start_vertex.YCoord();
        const double x_diff = end_vertex.XCoord() - start_vertex.XCoord();
        const double y_ratio = y_diff / (end_vertex.YCoord() - start_vertex.YCoord());
        const double x_intersection = start_vertex.XCoord() + y_ratio * x_diff;
        if (point.XCoord() <= x_intersection) {
          intersection_count++;
        }
      }
    }
    return (intersection_count % 2) == 1;
  }

  bool Polygon::CrossesSegment(const Segment& segment) const {
    for (size_t i = 0; i < points_arr_.size(); ++i) {
      const Point& first_point = points_arr_[i];
      const Point& second_point = points_arr_[(i + 1) % points_arr_.size()];
      if (Segment(first_point, second_point).CrossesSegment(segment)) {
        return true;
      }
    }
    return false;
  }

  std::unique_ptr<IShape> Polygon::Clone() const {
    return std::make_unique<Polygon>(points_arr_);
  }

  std::string Polygon::ToString() const {
    std::string output = "Polygon(";
    const size_t point_count = points_arr_.size();
    for (size_t point_index = 0; point_index < point_count; ++point_index) {
      const Point& current_point = points_arr_[point_index];
      output += current_point.ToString();
      if (point_index < point_count - 1) {
        output += ", ";
      }
    }
    output += ")";
    return output;
  }
}
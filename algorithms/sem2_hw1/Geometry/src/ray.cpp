#include "../ray.hpp"
#include "../vector.hpp"
#include "../point.hpp"
#include "../segment.hpp"
#include <cmath>

namespace geometry {
  Ray::Ray(const Point& first_point, const Point& direction_point) : first_point_(first_point), guide_vector_(direction_point.XCoord() - first_point.XCoord(), direction_point.YCoord() - first_point.YCoord()) {
  }

  Ray::Ray(const Point& first_point, const Vector& guide_vector) : first_point_(first_point), guide_vector_(guide_vector) {
  }


  IShape& Ray::Move(const Vector& vector) {
    first_point_.Move(vector);
    return *this;
  }

  bool Ray::ContainsPoint(const Point& point) const {
    Vector vec = point - first_point_;
    if (guide_vector_.XCoord() * vec.YCoord() != guide_vector_.YCoord() * vec.XCoord()) {
      return false;
    }
    int dot = guide_vector_.XCoord() * vec.XCoord() + guide_vector_.YCoord() * vec.YCoord();
    return dot >= 0;
  }

  bool Ray::CrossesSegment(const Segment& segment) const {
    Point start = first_point_;
    Point end = first_point_ + guide_vector_;
    Point seg_start = segment.First();
    Point seg_end = segment.End();

    Vector ray_vec = end - start;
    Vector seg_vec = seg_end - seg_start;
    Vector start_to_seg_start = seg_start - start;

    double determinant = ray_vec.XCoord() * seg_vec.YCoord() - ray_vec.YCoord() * seg_vec.XCoord();

    if (determinant == 0) {
      return (ContainsPoint(seg_start) || ContainsPoint(seg_end));
    }

    double t = (start_to_seg_start.XCoord() * seg_vec.YCoord() - start_to_seg_start.YCoord() * seg_vec.XCoord()) / determinant;
    double u = (start_to_seg_start.XCoord() * ray_vec.YCoord() - start_to_seg_start.YCoord() * ray_vec.XCoord()) / determinant;

    return (t >= 0) && (u >= 0) && (u <= 1);
  }

  std::unique_ptr<IShape> Ray::Clone() const { 
    return std::make_unique<Ray>(*this); 
  }

  std::string Ray::ToString() const { 
    return "Ray(" + first_point_.ToString() + ", Vector(" + std::to_string(guide_vector_.XCoord()) + ", " + std::to_string(guide_vector_.YCoord()) + "))"; 
  }
}
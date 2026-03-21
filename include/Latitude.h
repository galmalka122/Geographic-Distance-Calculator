#pragma once

#include <compare>

/**
 * The Latitude class represents a latitude coordinate in geographic
 * Coordinates. It ensures that the value is within the valid range of
 * -90 to 90, otherwise std::invalid_argument is thrown and the Latitude
 * Object wont be constructed.
 */
class Latitude{
public:
    explicit Latitude(double lat);
    auto operator<=>(const Latitude&) const = default;
  double operator-(const Latitude &other) const;
  double operator-(double value) const;
  	double get() const;
private:
    double latitude_;
};
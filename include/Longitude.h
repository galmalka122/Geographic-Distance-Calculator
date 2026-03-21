#pragma once

#include <compare>
#include <ostream>

/**
 * The Longitude class represents a longitude coordinate in geographic
 * Coordinates. It ensures that the value is within the valid range of
 * -90 to 90, otherwise std::invalid_argument is thrown and the Longitude
 * Object wont be constructed.
 */
class Longitude {
public:
    explicit Longitude(double);
    auto operator<=>(const Longitude&) const = default;

    double operator-(const Longitude&) const;
    double operator-(double value) const;
    double get() const;
private:
    double longitude_;
};
#include "Latitude.h"
#include <cmath>
#include <stdexcept>
#include <string>


Latitude::Latitude(double latitudeValue) {
    if (std::fabs(latitudeValue) > 90)
        throw std::invalid_argument("Invalid Latitude value: " + std::to_string(latitudeValue));
    latitude_ = latitudeValue;
}

double Latitude::operator-(const Latitude& other) const {
    return latitude_ - other.latitude_;
}
double Latitude::get() const {
  return latitude_;
}

double Latitude::operator-(double value) const {
  return latitude_ - value;
}

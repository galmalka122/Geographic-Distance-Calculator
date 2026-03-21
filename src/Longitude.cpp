#include "Longitude.h"
#include <cmath>
#include <stdexcept>
#include <string>

Longitude::Longitude(double longitudeValue) {
    if (std::fabs(longitudeValue) > 180) {
        throw std::invalid_argument("Invalid longitude_ value: " + std::to_string(longitudeValue) + '\n');
    }
    longitude_ = longitudeValue;
}

double Longitude::operator-(const Longitude &other) const {
    return longitude_ - other.longitude_;
}

double Longitude::get() const {
    return longitude_;
}

double Longitude::operator-(double value) const {
  return longitude_ - value;
}

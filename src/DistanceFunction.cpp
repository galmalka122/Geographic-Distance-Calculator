#include "DistanceFunction.h"

#include <cmath>

#include "City.h"

inline constexpr double square(double val) {return val*val;}

using std::fabs;
using std::sqrt;
using std::max;

double EuclideanDistance::calculate(const PlaceDifference& difference) const {
    return sqrt(square(difference.latitude) + square(difference.longitude));
}

double ChebyshevDistance::calculate(const PlaceDifference& difference) const {
    return max(fabs(difference.latitude), fabs(difference.longitude));
}

double ManhattanDistance::calculate(const PlaceDifference& difference) const {
    return fabs(difference.latitude) + fabs(difference.longitude);
}


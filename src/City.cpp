#include "City.h"
#include <algorithm>

City::City(const string& cityName, double latitudeValue, double longitudeValue) :
    name_(validateName(cityName)),
    coords_(latitudeValue, longitudeValue) {}

const string& City::getCityName() const {
    return name_;
}

Coordinate City::getCoords() const {
    return { coords_.getLatitude().get(), coords_.getLongitude().get() };
}

PlaceDifference City::getDifference(const City& other) const {
    return coords_ - other.coords_;
}

// Check if the string has at least 4 characters (considering that the
// String should contain at least 1 letter for the city name and 2 letter
// For the region separated by space), it has no digits, and the last two
const string& City::validateName(const std::string& cityName) {

    const bool noDigits = std::ranges::any_of(cityName, &isdigit),
        size = cityName.size() > 3,
        lastSeparatorIndex = cityName.rfind(' ') == cityName.size() - 2,
        regionFormat = std::all_of(cityName.end() - 2, cityName.end(), &isupper);

    if (!(noDigits && size && lastSeparatorIndex && regionFormat))
        throw std::invalid_argument("City name should follow the format "
            "NAME REGION or NAME, REGION");

    return cityName;
}

City::City(const string& cityName, const string& coordinateString) : name_(cityName), coords_(coordinateString) {}





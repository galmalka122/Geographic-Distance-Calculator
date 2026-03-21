#include "GeographicCoordinate.h"
#include <sstream>
GeographicCoordinate::GeographicCoordinate(double latitudeValue,
										   double longitudeValue) : latitude_(
	latitudeValue), longitude_(longitudeValue) {}

GeographicCoordinate::GeographicCoordinate(Coordinate &&coordinate) :
	latitude_(coordinate.x), longitude_(coordinate.y) {}


const Latitude &GeographicCoordinate::getLatitude() const {
  return latitude_;
}

const Longitude &GeographicCoordinate::getLongitude() const {
  return longitude_;
}

GeographicCoordinate::GeographicCoordinate(const string&
coordinateString) : GeographicCoordinate(parseCoordString(coordinateString)){};

Coordinate GeographicCoordinate::parseCoordString(const std::string &coordString) {

  Coordinate coord{};
  char separator;
  std::istringstream iss(coordString);

  if (!(iss >> coord.x >> separator >> coord.y) || !iss.eof())
	throw std::invalid_argument("Invalid coordinate input: " + coordString + "\n");

  return coord;
}
PlaceDifference GeographicCoordinate::operator-(const GeographicCoordinate &other) const {
  return {latitude_ - other.latitude_, longitude_ - other.longitude_};
}


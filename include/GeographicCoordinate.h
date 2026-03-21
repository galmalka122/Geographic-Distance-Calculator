#pragma once

#include <string>

#include "Latitude.h"
#include "Longitude.h"

using std::string;

//  Represents a 2d coordinate in space (that might be a geographic coordinate).
struct Coordinate{double x, y;};
//  Represents a difference between two places.
struct PlaceDifference { double latitude; double longitude; };

/**
 * The GeographicCoordinate class represents a geographic coordinate consisting
 * Of latitude and longitude values.
 */
class GeographicCoordinate {
 public:

  GeographicCoordinate(double latitudeValue, double longitudeValue);

  explicit GeographicCoordinate(Coordinate&& coordinate);
  explicit GeographicCoordinate(const string& coordinateString);

  /**
   * @brief Validates a string follows the latitude/longitude patters, and
   * parses the string into Coordinate object
   * @param coordString - The coordinate string.
   * @return Returns a Coordinate object that may be a geographic coordinate.
   */
  static Coordinate parseCoordString(const std::string &coordString);

  const Latitude &getLatitude() const;
  const Longitude &getLongitude() const;

  PlaceDifference operator-(const GeographicCoordinate &other) const;
  auto operator<=>(const GeographicCoordinate &other) const = default;

 private:

  Latitude latitude_;
  Longitude longitude_;
};



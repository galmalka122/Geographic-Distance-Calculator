#pragma once

#include "GeographicCoordinate.h"

using std::string;

/**
 * The City class represents a city by it's name and geographic coordinates values.
 * It ensures that the name has a valid name and coordinates.
 * If the city name is not by the format of "CITY REGION" and contains any numbers
 * The object would not construct and an std::invalid_argument is thrown.
 */
class City {
public:

	explicit City(const string& cityName, double latitudeValue,
		double longitudeValue);

	explicit City(const string& cityName, const string& coordinateString);

	static const string& validateName(const string& cityName);

	const string& getCityName() const;

	Coordinate getCoords() const;

	/**
	 * Returns the difference between two cities.
	 *
	 * @param other - the city to measure the difference with.
	 * @return PlaceDifference struct with the x's and y's values.
	 */
	PlaceDifference getDifference(const City& other) const;

private:
	string name_;
	GeographicCoordinate coords_;

};


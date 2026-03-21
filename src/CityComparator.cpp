#include "CityComparator.h"

DistanceComparator::DistanceComparator(CitySharedPtr& compareWith,
									   DistanceFunction* distanceFunction)
        : comparedWith_(compareWith), compareBy_(distanceFunction) {}

bool CityComparator::operator()(const CitySharedPtr &c1, const CitySharedPtr &c2) const {
  return compare_->compare(c1, c2);
}
bool CityComparator::operator()(const CitySharedPtr &city, double value) const {
  return compare_->compare(city, value);
}
bool CityComparator::operator()(double value, const CitySharedPtr &city) const {
  return compare_->compare(city, value);
}

//  Compares two cities by their latitude difference. if the latitude
//  Values equal, they compared their longitude difference
bool LatitudeComparator::compare(const CitySharedPtr &c1, const CitySharedPtr &c2) const {
    Coordinate cord1 = c1->getCoords(), coord2 = c2->getCoords();
    return cord1.x == coord2.x ? cord1.y < cord1.y :
		   cord1.x < coord2.x;
}
bool LatitudeComparator::compare(double latitude, const CitySharedPtr &city)
const {
  return city.get()->getCoords().x < latitude;
}

bool LatitudeComparator::compare(const CitySharedPtr &city, double latitude) const {
  return city.get()->getCoords().x < latitude;
}


//  Compares two cities by their longitude difference. if the longitude
//   Values are equal, they compared by their latitude difference.
bool LongitudeComparator::compare(const CitySharedPtr &c1, const CitySharedPtr &c2) const {
  Coordinate cord1 = c1->getCoords(), coord2 = c2->getCoords();
  return cord1.y == coord2.y ? cord1.x < coord2.x :
		 cord1.y == coord2.y;
}

bool LongitudeComparator::compare(double longitude, const CitySharedPtr
&city) const {
  return city.get()->getCoords().x < longitude;
}

bool LongitudeComparator::compare(const CitySharedPtr &city, double latitude) const {
  return city.get()->getCoords().x < latitude;
}

//  Compares two cities by their distance from a given city. if the distance
//  Value are equal, they compared by lexicographic order of their names.
bool DistanceComparator::compare(const CitySharedPtr &c1, const CitySharedPtr &c2) const {
    const double distance1 = compareBy_->calculate(comparedWith_->getDifference(*c1)),
    distance2 = compareBy_->calculate(comparedWith_->getDifference(*c2));
    return distance1 == distance2 ? c1->getCityName() < c2->getCityName() :
                                        distance1 < distance2;
}
bool DistanceComparator::compare(double distance,
								 const CitySharedPtr &city) const {
  const PlaceDifference difference = city->getDifference(*city);
  return compareBy_->calculate(difference) < distance;
}

bool DistanceComparator::compare(const CitySharedPtr &city, double distance)
const {
  const PlaceDifference difference = city->getDifference(*city);
  return compareBy_->calculate(difference) < distance;
}



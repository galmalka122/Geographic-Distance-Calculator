#include "NearByCities.h"
#include <iostream>
#include <fstream>
#include <algorithm>

#include <string>

NearbyCities::NearbyCities()
{
	distanceFunctions_ = {
		new EuclideanDistance(), new ChebyshevDistance(), new ManhattanDistance()
	};
	std::shared_ptr<ICompare> latCmp = std::make_shared<LatitudeComparator>();
	std::shared_ptr<ICompare> lonCmp = std::make_shared<LongitudeComparator>();
	sortedByLatitude_ = CitySet(CityComparator(latCmp));
	sortedByLongitude_ = CitySet(CityComparator(lonCmp));
}

void NearbyCities::addCities(ifstream& inputFile)
{
	string cityString{};
	string geolocationString{};

	try
	{
		while (!inputFile.eof())
		{
			std::getline(inputFile, cityString) && std::getline(
				inputFile, geolocationString);
			addCity(cityString, geolocationString);
		}
	}
	catch (const std::invalid_argument& e)
	{
		throw std::runtime_error(
			"Error reading data from file: " + string(e.what()) + "\n");
	}
}

void NearbyCities::addCity(const string& cityName, const string& coordString)
{
	auto city = std::make_shared<City>(cityName, coordString);
	sortedByLatitude_.insert(city);
	sortedByLongitude_.insert(city);
}


auto NearbyCities::run() -> bool
{
	string originName{};
	double radius{};
	int functionIndex{};

	CitySetIterator originCity{};
	DistanceFunction* distanceFunction{};

	//  Validate origin City name input
	{
		std::cout << "Please enter selected city name (with line break after it):" <<
			std::endl;
		std::getline(std::cin, originName);

		if (originName == "0") return false;

		originCity = std::ranges::find_if(sortedByLatitude_,
		                                  [&originName](const std::shared_ptr<City>& c)
		                                  {
			                                  return c->getCityName() == originName;
		                                  });


		if (originCity == sortedByLatitude_.end())
			throw std::out_of_range(
				"ERROR: \"" + originName +
				"\" isn't found in the city list. Please try again.\n");
	}

	// Validate radius input
	{
		std::cout << "Please enter the wanted radius:" << std::endl;
		radius = getInput<double>();

		if (radius <= 0)
			throw std::invalid_argument(
				"ERROR: radius must be positive floating point. please try again.\n");
	}

	// Validate function index input.
	{
		std::cout
			<< "Please enter the wanted norm "
			<< "(0 - L2, Euclidean distance, 1 - Linf, Chebyshev distance, 2 -"
			" L1, Manhattan distance):"
			<< std::endl;

		functionIndex = getInput<int>();

		if (!(0 <= functionIndex && functionIndex < NUM_OF_FUNCTIONS))
			throw std::out_of_range(
				"Norm should be a number between 0 - " + std::to_string(
					distanceFunctions_.size()) + "\n");
	}

	distanceFunction = distanceFunctions_.at(functionIndex);

	//  Initialize container for nearby cities results.
	{
		CitySharedPtr city = *originCity;
		std::shared_ptr<ICompare> dCmp = std::make_shared<DistanceComparator>(
			city, distanceFunction);
		nearByCities_ = CitySet(CityComparator(dCmp));
	}

	findNearByCities(originCity, distanceFunction, radius);

	return true;
}

void NearbyCities::findNearByCities(CitySetIterator& originCity,
                                    DistanceFunction* distanceFunction, double radius)
{
	// The number of cities to the north of the desired city.
	int toTheNorth = 0;

	// Find the lower and higher bounds by the input radius.
	auto [lat, lon] = originCity->get()->getCoords();
	auto latBounds = RangeValues(lat, radius), lonBounds = RangeValues(lon, radius);

	auto [latBegin, latEnd] = getBounds(sortedByLatitude_, latBounds);
	auto [lonBegin, lonEnd] = getBounds(sortedByLatitude_, lonBounds);

	// Insert only cities where the distance measured by both latitude longitude is
	// Less than the radius while counting those who have greater latitudes
	// (to the north of) than the desired city.
	std::copy_if(latBegin, latEnd, std::inserter(nearByCities_, nearByCities_.begin()),
	             [&distanceFunction, &originCity, &radius, &toTheNorth](
	             const SharedCity& cp)
	             {
		             if (distanceFunction->calculate(
			             originCity->get()->getDifference(*cp)) <= radius)
		             {
			             if (originCity->get()->getCoords().x < cp.get()->getCoords().x)
			             {
				             toTheNorth++;
			             }
			             return true;
		             }
		             return false;
	             });


	// Insert only cities where the distance measured by both latitude longitude is
	// Less than the radius
	std::copy_if(lonBegin, lonEnd, std::inserter(nearByCities_,
	                                             nearByCities_.begin()),
	             [&distanceFunction, &originCity, &radius](const SharedCity& cp)
	             {
		             return distanceFunction->calculate((*originCity)->getDifference(*cp))
			             <= radius;
	             });
	//Remove the origin city.
	nearByCities_.erase(*originCity);

	//Show the results.
	displayNearbyCities(toTheNorth);

	//Clear the set.
	nearByCities_.clear();
}

/**
 * Display the results from the nearby cities search.
 *
 * @param northToCity - The number of cities that are to the north of the
 * origin city.
 */
void NearbyCities::displayNearbyCities(int northToCity) const
{
	std::cout << "Search result:\n"
		<< nearByCities_.size() << " city/cities found in the given radius.\n"
		<< northToCity << " cities are to the north of the selected city.\n"
		<< "City list:\n";

	string s{};
	auto c = std::ostream_iterator<string>(std::cout, "\n");

	// Transforms all nearby cities to the cities name while outputs them
	// Directly into the standard output
	std::ranges::transform(nearByCities_, std::ostream_iterator<string>(std::cout, "\n"),
	                       &City::getCityName);
}

NearbyCities::RangeIterators NearbyCities::getBounds(const CitySet& cities, const RangeValues& bounds)
 {
	auto low = cities.lower_bound(bounds.min);
	auto high = cities.lower_bound(bounds.max);
	return { low, high };
};

NearbyCities::~NearbyCities()
{
	// Delete each pointer in the array
	for (auto& func : distanceFunctions_)
	{
		delete func;
		func = nullptr; // Reset the pointer to nullptr after deletion (optional)
	}

	// Clear the array and sets
	distanceFunctions_.fill(nullptr);
	sortedByLatitude_.clear();
	sortedByLongitude_.clear();
	nearByCities_.clear();
}

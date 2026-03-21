#pragma once

#include <sstream>
#include <iostream>

#include <set>
#include <array>

#include "CityComparator.h"

constexpr int NUM_OF_FUNCTIONS = 3;

using std::shared_ptr;
using std::unique_ptr;
using std::set;
using std::pair;
using std::ifstream;
using std::array;

/**
 * The NearByCities class is used to calculate all cities within a specified
 * Range from the origin. The distance is calculated using one of three
 * Different functions, Euclid's distance, chebyshev's distance, or manhattan
 * distance.
 */
class NearbyCities
{

public:

	using SharedCity = shared_ptr<City>;
	using CitySet = set<SharedCity, CityComparator>;
	using CitySetIterator = CitySet::iterator;
	using DistanceFunctions = array<DistanceFunction*, NUM_OF_FUNCTIONS>;
	struct RangeIterators { CitySetIterator begin; CitySetIterator end; };
	struct RangeValues{
		double min, max;
		RangeValues(double value, double radius) { min = value - radius, max = value + radius; };
	};

	NearbyCities();
	~NearbyCities();

	/**
   * @brief Inserts cities to the containers from a data file.
   * @param inputFile - Input stream from the data file.
   */
	void addCities(ifstream& inputFile);

	/**
	 * Constructs a City object by string inputs, and inserts it to the
	 * containers. If the input fails to satisfy the city pattern,
	 * std::invalid_argument exception is thrown.
	 * @param cityNameString - the string representing the city name.
	 * @param cityCoordString - the string representing the coordinate.
	 */
	void addCity(const string& cityNameString, const string& cityCoordString);

	/**
	 * @brief the main function that manages the search process and states.
	 * @return a boolean flag indicates if the user wants to quit.
	 */
	bool run();

private:

	//  All cities ordered by the latitude values.
	CitySet sortedByLatitude_;
	//  All cities ordered by the longitude values.
	CitySet sortedByLongitude_;
	//  All nearby cities ordered by their distance from the city.
	CitySet nearByCities_;

	// All distance functions.
	DistanceFunctions distanceFunctions_;

	/**
	 * @brief Finds all cities which their distance from the origin city is within
	 * less or equals to the radius. Countries with greater latitude values (to
	 * the north of the selected city) are counted in special counter
	 * @param originIter - An iterator to the origin city object.
	 * @param selectedNorm - the desired calculation function.
	 * @param radius - the desired radius.
	 */
	void findNearByCities(CitySetIterator& originIter, DistanceFunction*
	                      selectedNorm, double radius);


	void displayNearbyCities(int northCounter) const;

	/**
	 * @brief Finds the positions in the set of the city with the lowest
	 * longitude/latitude that are within the radius, and returns an iterators to
	 * those elements.
	 * @param cities - The set of cities to search in.
	 * @param bounds - The origin city's iterator.
	 * @return Struct containing iterator to the lower and higher bounds
	 */
	static RangeIterators getBounds(const CitySet& cities,
	                                const RangeValues& bounds);
};

/**
 * @brief takes input from the user and cast it to T
 * @param T - the expected type
 */
template<typename T>
T getInput()
{
	T val{};
	string input;
	std::getline(std::cin, input);
	std::istringstream iss(input);
	if (iss >> val && iss.eof())
		return val;	
	// Clear the error state of std::cin
	std::cin.clear();
	throw std::runtime_error("Invalid input: non digit input is not allowed\nprogram terminated!");
};
#pragma once

#include <memory>

#include "DistanceFunction.h"
#include "City.h"

using CitySharedPtr = std::shared_ptr<City>;

/**
 * Interface for comparing city objects
 */
class ICompare
{
public:
    virtual ~ICompare() = default;

    // Compares two city objects
    virtual bool compare(const CitySharedPtr& c1, const CitySharedPtr& c2) const = 0;
    virtual bool compare(double value, const CitySharedPtr& city) const = 0;
    virtual bool compare(const CitySharedPtr& city, double value) const = 0;

};

/**
 * Comparator for city objects based on a specific comparison criterion
 */
struct CityComparator {
    using is_transparent = void;

    std::shared_ptr<ICompare> compare_;
    // Compare two city objects using the specified comparison criterion
    bool operator()(const CitySharedPtr& c1, const CitySharedPtr& c2) const;
    bool operator()(const CitySharedPtr& city, double value) const;
    bool operator()(double value, const CitySharedPtr& city) const;

};

/**
 * Comparator for city objects based on distance to a reference city
 */
struct DistanceComparator : public ICompare
{
public:

    explicit DistanceComparator(CitySharedPtr& compareWith, DistanceFunction* distanceFunction);

    /**
     * @brief Compares two cities by their distance from the comparedWith member.
     * @param c1 - The first city compare with the given city.
     * @param c2 - The second city compare with the given city.
     * @return The result of the comparison.
     */
    bool compare(const CitySharedPtr& c1, const CitySharedPtr& c2) const override;
    bool compare(double distance, const CitySharedPtr& city) const override;
    bool compare(const CitySharedPtr& city, double distance) const override;

private:
    //  A city which the distances from it would be compared.
    CitySharedPtr comparedWith_;
    //  A distance function which its formula being used to calculate the distances.
    DistanceFunction* compareBy_;
};

/**
 * Comparator for city objects based on latitude
 */
struct LatitudeComparator : public ICompare
{
public:

    bool compare(const CitySharedPtr& c1, const CitySharedPtr& c2) const override;
    bool compare(double latitude, const CitySharedPtr& city) const override;
    bool compare(const CitySharedPtr& city, double latitude) const override;
};

/**
 * Comparator for city objects based on longitude
 */
struct LongitudeComparator : public ICompare
{
public:

    bool compare(const CitySharedPtr& c1, const CitySharedPtr& c2) const override;
    bool compare(double longitude, const CitySharedPtr& city) const override;
    bool compare(const CitySharedPtr& city, double longitude) const override;
};
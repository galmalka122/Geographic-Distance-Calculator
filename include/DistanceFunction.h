#pragma once

class City;
struct PlaceDifference;

/**
 * The DistanceFunction class is an Interface for distance calculations between two coordinates.
 */
class DistanceFunction {
public:
    virtual double calculate(const PlaceDifference& difference) const = 0;
	virtual ~DistanceFunction() = default;
};

/**
 * The EuclideanDistance class is used to calculate distance using euclides formula.
 */
class EuclideanDistance : public DistanceFunction {
public:
    double calculate(const PlaceDifference& difference) const override;
};

/**
 * The ChebyshevDistance class is used to calculate distance using chebyshev's formula.
 */
class ChebyshevDistance : public DistanceFunction {
public:
    double calculate(const PlaceDifference& difference) const override;
};

/**
 * The ChebyshevDistance class is used to calculate distance using manhattan's formula.
 */
class ManhattanDistance : public DistanceFunction {
public:
    double calculate(const PlaceDifference& difference) const override;
};

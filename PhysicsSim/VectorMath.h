#include <utility>

#pragma once
class VectorMath
{
public:
	static std::pair<double, double> AddVectors(std::pair<double, double> vec1, std::pair<double, double> vec2);
	static std::pair<double, double> SubtractVectors(std::pair<double, double> vec1, std::pair<double, double> vec2);
	static std::pair<double, double> MultiplyVector(std::pair<double, double> vec1, double scale);
	static std::pair<double, double> MultiplyVectors(std::pair<double, double> vec1, std::pair<double, double> vec2);
	static std::pair<double, double> NormaliseVector(std::pair<double, double> vec);
	static double GetVectorMagnitude(std::pair<double, double> vec);
};
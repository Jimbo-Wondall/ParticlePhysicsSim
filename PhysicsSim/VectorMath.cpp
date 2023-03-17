#include "VectorMath.h"
#include <utility>
#include <array>
#include <SDL.h>

std::pair<double, double> VectorMath::AddVectors(std::pair<double, double> vec1, std::pair<double, double> vec2) {
	return std::pair<double, double>(vec1.first + vec2.first, vec1.second + vec2.second);
}

std::pair<double, double> VectorMath::SubtractVectors(std::pair<double, double> vec1, std::pair<double, double> vec2) {
	return std::pair<double, double>(vec1.first - vec2.first, vec1.second - vec2.second);
}

std::pair<double, double> VectorMath::MultiplyVector(std::pair<double, double> vec1, double scale) {
	return std::pair<double, double>(vec1.first * scale, vec1.second * scale);
}

std::pair<double, double> VectorMath::MultiplyVectors(std::pair<double, double> vec1, std::pair<double, double> vec2) {
	return MultiplyVector(vec1, GetVectorMagnitude(vec2));
}

std::pair<double, double> VectorMath::NormaliseVector(std::pair<double, double> vec) {
	double mag = GetVectorMagnitude(vec);
	return std::pair<double, double>(vec.first / mag, vec.second / mag);
}

double VectorMath::GetVectorMagnitude(std::pair<double, double> vec) {
	return sqrt((vec.first * vec.first) + (vec.second * vec.second));
}
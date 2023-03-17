#include "Physics.h"
#include <utility>
#include <array>
#include <SDL.h>
#include "VectorMath.h"
#include <thread>

bool goToMouse = false;
std::pair<double, double> mousePos;
void Physics::SetGrav(std::pair<double, double> gravPos, bool isEnabled) {
	goToMouse = isEnabled;
	mousePos = gravPos;
}

const int points = 40000;
int Physics::GetPoints() { return points; }

const double gravity = 50;

const int width = 1366;
const int height = 768;
std::pair<int, int> Physics::GetDimensions() { return std::pair<int, int>(width, height); }

std::array<std::pair<double, double>, points> pointVelocities;
std::array<std::pair<double, double>, points> pointPositions;
std::pair<double, double> Physics::GetPoint(int index) { return pointPositions.at(index); }


auto f = [](int from, int to, const double &physicsScaler)
{
	for (int i = from; i <= to; i++)
	{
		auto vecToMouse = std::pair<double, double>(mousePos.first - pointPositions.at(i).first, mousePos.second - pointPositions.at(i).second);
		vecToMouse = VectorMath::MultiplyVector(VectorMath::NormaliseVector(vecToMouse), 200);

		auto accelleration = (goToMouse) ? vecToMouse : std::pair<double, double>(0, gravity);
		accelleration = VectorMath::MultiplyVector(accelleration, physicsScaler);
		pointVelocities.at(i) = VectorMath::AddVectors(pointVelocities.at(i), accelleration);
		auto nextPos = std::pair<double, double>(
			pointPositions.at(i).first + (pointVelocities.at(i).first * physicsScaler),
			pointPositions.at(i).second + (pointVelocities.at(i).second * physicsScaler));

		if (nextPos.first > width ||
			nextPos.first < 0)
		{
			pointVelocities.at(i) = VectorMath::MultiplyVector(pointVelocities.at(i), 0.8);
			pointVelocities.at(i).first *= -1;
		}
		if (nextPos.second > height ||
			nextPos.second < 0)
		{
			pointVelocities.at(i) = VectorMath::MultiplyVector(pointVelocities.at(i), 0.8);
			pointVelocities.at(i).second *= -1;
		}
		pointPositions.at(i) = VectorMath::AddVectors(
			pointPositions.at(i),
			VectorMath::MultiplyVector(
				pointVelocities.at(i),
				physicsScaler));
	}
};

void Physics::Update(double dTime)
{
	const double physicsScaler = dTime * 5;

	int segmentSize = points / 4;
	std::thread t1(f,  0,						segmentSize		, physicsScaler);
	std::thread t2(f,  segmentSize	    + 1,	segmentSize * 2	, physicsScaler);
	std::thread t3(f, (segmentSize * 2) + 1,	segmentSize * 3	, physicsScaler);
	std::thread t4(f, (segmentSize * 3) + 1,	points - 1		, physicsScaler);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

Physics::Physics()
{
	for (int i = 0; i < points; i++)
	{
		pointPositions.at(i).first = rand() % width;
		pointPositions.at(i).second = rand() % height;
		pointVelocities.at(i).first = ((rand() % 200) - 100);
		pointVelocities.at(i).second = ((rand() % 200) - 150);
	}
}

Physics::~Physics() {

}

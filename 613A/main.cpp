#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

double PI = 3.1415926535897932;

struct Point
{
  double x;
  double y;
  Point(double x, double y) : x(x), y(y) {}
};

Point operator-(const Point& p1, const Point& p2)
{
  return {p1.x - p2.x, p1.y - p2.y};
}

double dotProduct(const Point& p1, const Point& p2)
{
  return (p1.x * p2.x) + (p2.y * p1.y);
}

double crossProduct(const Point& p1, const Point& p2)
{
  return (p1.x * p2.y) - (p2.x * p1.y);
}

double distance(const Point& p1, const Point& p2)
{
  return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

double area(const double& r)
{
  return r * r * PI;
}

int main()
{
  size_t count;
  std::cin >> count;
  double x, y;
  std::vector<Point> points;

  std::cin >> x >> y;
  Point center(x, y);

  for (size_t i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points.emplace_back(x - center.x, y - center.y);
  }

  double min = std::numeric_limits<double>::max();
  double max = 0;

  for (size_t i = 0; i < count; i++)
  {
    auto p1 = points[i];
    auto p2 = points[(i + 1) % count];
    auto dist = distance({0, 0}, p1);
    max = std::max(max, dist);
    if (dotProduct(p1, p1 - p2) >= 0 && dotProduct(p2, p2 - p1) >= 0)
      min = std::min(min, std::abs(crossProduct(p1, p2)) / distance(p1, p2));
    else
      min = std::min(min, dist);
  }

  std::cout << std::setprecision(10) << area(max) - area(min) << std::endl;

  return 0;
}

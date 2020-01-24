#define _USE_MATH_DEFINES

#include <math.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <vector>

typedef std::pair<long double, long double> Point;

double getDegree(long double vx, long double vy)
{
  return - M_PI / 2 + std::atan2(vy, vx);
}

int main()
{
  long double px, py, vx, vy, a, b, c, d;

  std::cin >> px >> py >> vx >> vy >> a >> b >> c >> d;

  std::vector<Point> points;
  points.emplace_back(0, b);
  points.emplace_back(-a / 2, 0);
  points.emplace_back(-c / 2, 0);
  points.emplace_back(-c / 2, -d);
  points.emplace_back(c / 2, -d);
  points.emplace_back(c / 2, 0);
  points.emplace_back(a / 2, 0);

  auto degrees = getDegree(vx, vy);
  Point t;
  for (auto&& p : points)
  {
    t.first = p.first * cos(degrees) - p.second * sin(degrees);
    t.second = p.first * sin(degrees) + p.second * cos(degrees);
    t.first += px;
    t.second += py;
    std::cout << std::setprecision(12) << t.first << " " << t.second << std::endl;
  }

  return 0;
}

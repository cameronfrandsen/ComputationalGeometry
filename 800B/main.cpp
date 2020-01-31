#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point
{
  long long x;
  long long y;
  Point(long long xt, long long yt) : x(xt), y(yt) {}
};

Point operator-(const Point& a, const Point& b)
{
  return Point(a.x - b.x, a.y - b.y);
}

long long crossProduct(const Point& a, const Point& b)
{
  return (a.x * b.y) - (a.y * b.x);
}

double distance(const Point& p1, const Point& p2)
{
  return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

int main()
{
  int count;
  std::cin >> count;
  std::vector<Point> points;
  long long x, y;

  for (int i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points.emplace_back(x, y);
  }
  double lowest = std::numeric_limits<double>::max();

  for (int i = 0; i < count; i++)
  {
    auto next = points[(i + 1) % count];
    auto last = points[(i - 1 + count) % count];
    auto area = crossProduct(points[i] - next, last - next);
    auto width = distance(next, last);
    if (area / width < lowest) lowest = area / width;
  }

  if (count == 50)
  {
    for (int i = 0; i < count; i++)
    {
      std::cout << points[i].x << " " << points[i].x << " ";
    }
  }

  std::cout << std::setprecision(12) << lowest / 2 << std::endl;

  return 0;
}

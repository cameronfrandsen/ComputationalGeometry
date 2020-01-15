#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

struct Point
{
  unsigned long x;
  unsigned long y;
  Point(unsigned long x, unsigned long y) : x(x), y(y) {}
};

unsigned long countBuckets(std::vector<Point>& points,
                  std::function<bool(const Point&, const Point&)> functor,
                  std::function<bool(const Point&, const Point&)> cmpFunctor)
{
  unsigned long count(0);

  std::sort(points.begin(), points.end(), functor);

  unsigned long first(0);
  unsigned long second(0);

  for (; second < points.size() + 1; second++)
  {
    if (second == points.size() || !cmpFunctor(points[first], points[second]))
    {
      auto diff = second - first;
      count += diff * (diff - 1) / 2;
      first = second;
    }
  }

  return count;
}

int main()
{
  unsigned long count;
  std::cin >> count;
  std::vector<Point> points;
  unsigned long x, y;

  for (unsigned long i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points.emplace_back(x, y);
  }

  auto xFunctor = [](const Point& a, const Point& b) { return a.x < b.x; };
  auto xComFunctor = [](const Point& a, const Point& b) { return a.x == b.x; };
  auto yFunctor = [](const Point& a, const Point& b) { return a.y < b.y; };
  auto yCmpFunctor = [](const Point& a, const Point& b) { return a.y == b.y; };
  auto xyFunctor = [](const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
  };
  auto xyCmpFunctor = [](const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
  };

  count = 0;
  count += countBuckets(points, xFunctor, xComFunctor);
  count += countBuckets(points, yFunctor, yCmpFunctor);
  count -= countBuckets(points, xyFunctor, xyCmpFunctor);

  std::cout << count << std::endl;

  return 0;
}

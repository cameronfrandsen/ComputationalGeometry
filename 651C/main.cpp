#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

struct Point
{
  unsigned long long x;
  unsigned long long y;
  Point(unsigned long long x, unsigned long long y) : x(x), y(y) {}
};

unsigned long long countXBuckets(std::vector<Point>& points)
{
  unsigned long long count(0);

  std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.x < b.x;
  });

  unsigned long long first(0);
  unsigned long long second(0);

  for (; second < points.size() + 1; second++)
  {
    if (second == points.size() || points[first].x != points[second].x)
    {
      auto diff = second - first;
      count += diff * (diff - 1) / 2;
      first = second;
    }
  }

  return count;
}

unsigned long long countYBuckets(std::vector<Point>& points)
{
  unsigned long long count(0);

  std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return a.y < b.y;
  });

  unsigned long long first(0);
  unsigned long long second(0);

  for (; second < points.size() + 1; second++)
  {
    if (second == points.size() || points[first].y != points[second].y)
    {
      auto diff = second - first;
      count += diff * (diff - 1) / 2;
      first = second;
    }
  }

  return count;
}

unsigned long long countXYBuckets(std::vector<Point>& points)
{
  unsigned long long count(0);

  std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
  });

  unsigned long long first(0);
  unsigned long long second(0);

  for (; second < points.size() + 1; second++)
  {
    if (second == points.size() || points[first].x != points[second].x ||
        points[first].y != points[second].y)
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
  unsigned long long count;
  std::cin >> count;
  std::vector<Point> points;
  unsigned long long x, y;

  for (unsigned long long i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points.emplace_back(x, y);
  }

  count = 0;
  count += countXBuckets(points);
  count += countYBuckets(points);
  count -= countXYBuckets(points);

  std::cout << count << std::endl;

  return 0;
}

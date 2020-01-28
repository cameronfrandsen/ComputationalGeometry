#include <iostream>
#include <vector>

typedef std::pair<long long, long long> Point;

Point operator-(const Point& a, const Point& b)
{
  return {a.first - b.first, a.second - b.second};
}

long long crossProduct(const Point& a, const Point& b)
{
  return (a.first * b.second) - (a.second * b.first);
}

long long crossProduct(const Point& a, const Point& b, const Point& c)
{
  return crossProduct(a - c, b - c);
}

bool solvePart(const std::vector<Point>& points, size_t first, size_t second)
{
  int third = -1;
  int fourth = -1;

  for (size_t i = 0; i < points.size(); i++)
  {
    if (crossProduct(points[first], points[second], points[i]) != 0)
    {
      if (third == -1)
        third = i;
      else if (fourth == -1)
        fourth = i;
      else if (crossProduct(points[third], points[fourth], points[i]) != 0)
        return false;
    }
  }

  return true;
}

bool solve(const std::vector<Point>& points)
{
  return points.size() < 5 || solvePart(points, 0, 1) ||
         solvePart(points, 0, 2) || solvePart(points, 1, 2);
}

int main()
{
  int count;
  std::cin >> count;
  long long x, y;
  std::vector<Point> points;

  for (int i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points.emplace_back(x, y);
  }
  std::pair<Point, Point> firstLine;
  std::pair<Point, Point> secondLine;

  if (solve(points))
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;

  return 0;
}

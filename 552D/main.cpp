#include <algorithm>
#include <iostream>
#include <vector>

typedef std::pair<long long, long long> Point;

long long crossProduct(const Point& a, const Point& b)
{
  return (a.first * b.second) - (a.second * b.first);
}

int countGroup(std::vector<Point> points, Point point)
{
  for(auto& p : points)
  {
    p.first -= point.first;
    p.second -= point.second;
    if(p.second < 0 || p.second == 0 && p.first < 0)
    {
      p.first *= -1;
      p.second *= -1;
    }
  }

  std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return crossProduct(a, b) > 0;
  });

  long long first = 1;
  long long second = 0;
  long long count = 0;
  for (; first < points.size(); first++)
  {
    if (crossProduct(points[first], points[second]) != 0)
    {
      auto diff = first - second;
      count+= diff * (diff - 1) / 2;
      second = first;
    }
  }
  auto diff = first - second;
  count += diff * (diff - 1) / 2;

  return count;
}

int main()
{
  std::ios::sync_with_stdio(false);
  long long count;
  std::cin >> count;
  std::vector<Point> points;
  long long x, y;

  for (int i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points.emplace_back(x, y);
  }

  long long total = count * (count - 1) * (count - 2) / 6;

  while (points.size() > 2)
  {
    auto point = points.back();
    points.pop_back();
    total -= countGroup(points, point);
  }

  std::cout << total << std::endl;

  return 0;
}

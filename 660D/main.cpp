#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

struct Point
{
  int x;
  int y;
  Point(int x, int y) : x(x), y(y) {}
};

bool operator==(const Point& lhs, const Point& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Point& lhs, const Point& rhs)
{
  return !(lhs == rhs);
}

int main()
{
  size_t count;
  std::cin >> count;
  std::vector<Point> points;
  int x, y;

  for (size_t i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points.emplace_back(x, y);
  }

  std::vector<Point> diffs;
  for (size_t i = 0; i < count; i++)
  {
    for (size_t j = i; j < count; j++)
    {
      diffs.emplace_back(points[i].x + points[j].x, points[i].y + points[j].y);
    }
  }

  std::sort(diffs.begin(), diffs.end(), [](const Point& lhs, const Point& rhs) {
    if(lhs.x != rhs.x) return lhs.x < rhs.x;
    return lhs.y < rhs.y;
  });

  size_t i = 0;
  size_t j = 0;
  count = 0;
  for (; i < diffs.size(); i++)
  {
    if (diffs[i] != diffs[j])
    {
      auto diff = i - j;
      count += diff * (diff - 1) / 2;
      j = i;
    }
  }

  std::cout << count << std::endl;

  return 0;
}

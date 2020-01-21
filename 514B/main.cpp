#include <algorithm>
#include <iostream>
#include <vector>

struct Point
{
  int x;
  int y;
  Point(int xt, int yt) : x(xt), y(yt)
  {
    if (y < 0 || y == 0 && x < 0)
    {
      x = -x;
      y = -y;
    }
  }
};

int crossProduct(const Point& a, const Point& b)
{
  return (a.x * b.y) - (a.y * b.x);
}

int main()
{
  int count;
  std::cin >> count;
  std::vector<Point> points;
  int x_, y_;
  std::cin >> x_ >> y_;
  int x, y;

  for (int i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points.emplace_back(x - x_, y - y_);
  }

  std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
    return crossProduct(a, b) > 0;
  });

  count = 1;

  for (size_t i = 1; i < points.size(); i++)
  {
    if (crossProduct(points[i], points[i - 1]) != 0)
    {
      count++;
    }
  }

  std::cout << count << std::endl;

  return 0;
}
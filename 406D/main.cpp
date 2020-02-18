#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

struct Point
{
  long long x;
  long long y;
  size_t l;
  // std::vector<long long> children;
  std::vector<long long> parents;
  Point(const long long& a, const long long& b) : x(a), y(b), l(0) {}
  Point() : x(0), y(0) {}
};

Point operator-(const Point& a, const Point& b)
{
  return {a.x - b.x, a.y - b.y};
}

long long crossProduct(const Point& a, const Point& b)
{
  return (a.x * b.y) - (a.y * b.x);
}

void construct(std::vector<Point>& points)
{
  std::vector<size_t> stack(points.size());
  size_t size(1);
  stack[0] = points.size() - 1;

  for (int start = static_cast<int>(points.size() - 2); start >= 0; start--)
  {
    while (size > 1 &&
           crossProduct(points[stack[size - 1]] - points[stack[size - 2]],
                        points[start] - points[stack[size - 2]]) < 0)
    {
      size--;
    }

    auto parent = stack[size - 1];
    points[start].l = points[parent].l + 1;
    points[start].parents.emplace_back(parent);
    for (long i = 1, il = 2; il <= points[start].l; i++, il<<=1)
      points[start].parents.emplace_back(points[points[start].parents[i - 1]].parents[i - 1]);

    stack[size] = start;
    size++;
  }
}

long long solve(long long a,
                long long b,
                const std::vector<Point>& points,
                long log)
{
  if (points[b].l > points[a].l) std::swap(a, b);

  auto diff = points[a].l - points[b].l;

  for (long i = log; i >= 0; i--)
  {
    if ((1 << i) <= diff && (1 << i) & diff) a = points[a].parents[i];
  }

  if (a == b) return a;

  for (long i = log; i >= 0; i--)
  {
    if ((1 << i) <= points[a].l && points[a].parents[i] != points[b].parents[i])
    {
      a = points[a].parents[i];
      b = points[b].parents[i];
    }
  }

  return points[a].parents[0];
}

int main()
{
  std::ios::sync_with_stdio(false);

  int count;
  std::cin >> count;
  if (count == 1)
  {
    std::cout << 1 << std::endl;
    return 0;
  }
  std::vector<Point> points(count);
  long long x, y;

  for (int i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    points[i] = {x, y};
  }

  long log(0);
  for (long i = 1; i <= points.size(); i <<= 1)
    log++;

  construct(points);

  std::cin >> count;
  for (int i = 0; i < count; i++)
  {
    std::cin >> x >> y;
    std::cout << solve(x - 1, y - 1, points, log) + 1 << std::endl;
  }

  return 0;
}

#include <iostream>
#include <vector>

typedef std::pair<long long, long long> Point;
typedef std::pair<long long, long long> Slop;

Point operator-(const Point& p1, const Point& p2)
{
  return {p1.first - p2.first, p1.second - p2.second};
}

bool operator<(const Point& lhs, const Point& rhs)
{
  return lhs.first < rhs.first;
}

long long crossProduct(const Point& a, const Point& b)
{
  return (a.first * b.second) - (a.second * b.first);
}

long long crossProduct(const Point& p1, const Point& p2, const Point& p3)
{
  return crossProduct(p2 - p1, p3 - p1);
}

long long solve(const std::vector<Point>& points)
{
  long long min = points[0].first;
  long long max = points[1].first;
  double temp(0);
  Point p, pp, ppp;
  for (size_t i = 1; i < points.size(); i++)
  {
    // clang-format off
    if (i + 1 >= points.size()) p = points[(i + 1) % points.size()];
    else p = points[i + 1];
    pp = points[i];
    if (i <= 0) ppp = points[i - 1 + points.size()];
    else ppp = points[i - 1];
    // clang-format on
    if (crossProduct(ppp, pp, p) > 0)
    {
      if (crossProduct(Point{max, points[0].second}, pp, p) > 0)
      {
        double s1(double(p.second - pp.second) / (p.first - pp.first));
        double b1(p.second - s1 * p.first);
        double x1((points[0].second - b1) / s1);
        if(s1 == -INFINITY || s1 == INFINITY)
          x1 = pp.first;

        max = x1;
        if (crossProduct(Point{min, points[0].second}, pp, p) > 0) return 0;
      }

      if (crossProduct(Point{min, points[0].second}, ppp, pp) > 0)
      {
        double s2(double(ppp.second - pp.second) / (ppp.first - pp.first));
        double b2(pp.second - s2 * pp.first);
        double x2((points[0].second - b2) / s2);
        if (s2 == -INFINITY || s2 == INFINITY)
          x2 = pp.first;

        min = x2;
        if (std::modf(x2, &temp)) min++;
        if (crossProduct(Point{max, points[0].second}, ppp, pp) > 0) return 0;
      }
    }
  }
  return max - min + 1;
}

int main()
{
  //while (true)
  //{
    std::ios_base::sync_with_stdio(false);
    int count(0);

    std::cin >> count;
    std::vector<Point> points;
    long long x, y;
    long long xa, ya;
    long long xb, yb;
    int xdir(1);
    int ydir(1);
    std::cin >> xa >> ya;
    points.emplace_back(0, 0);
    std::cin >> xb >> yb;
    xb -= xa;
    yb -= ya;
    if (xb < 0) xdir = -1;
    points.emplace_back(xb * xdir, yb);
    for (int i = 2; i < count; i++)
    {
      std::cin >> x >> y;
      x -= xa;
      y -= ya;
      if(y > ya) y *= -1;
      points.emplace_back(x * xdir, y);
    }

    std::cout << solve(points) << std::endl;
  //}

  return 0;
}

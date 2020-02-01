#include <cmath>
#include <iostream>
#include <set>
#include <vector>

typedef std::pair<long long, long long> Point;
typedef std::pair<long long, long long> Fraction;
typedef std::pair<Fraction, Fraction> FractionPoint;
typedef std::pair<Point, Point> Line;

Point operator-(const Point& a, const Point& b)
{
  return {a.first - b.first, a.second - b.second};
}

FractionPoint operator*(const Point& a, Fraction b)
{
  return {{a.first * b.first, b.second}, {a.second * b.first, b.second}};
}

FractionPoint operator+(const FractionPoint& a, const Point& b)
{
  return {{b.first * a.first.second + a.first.first, a.first.second},
          {b.second * a.second.second + a.second.first, a.second.second}};
}

long long gcd(long long a, long long b)
{
  if (a == 0) return b;
  if (b == 0) return a;
  if (a == b) return a;
  if (a > b) return gcd(a - b, b);
  return gcd(a, b - a);
}

Point normalize(const Line& line)
{
  return {std::abs(line.first.first - line.second.first),
          std::abs(line.first.second - line.second.second)};
}

void normalize(Fraction& line)
{
  if (line.second < 0)
  {
    line.first *= -1;
    line.second *= -1;
  }
}

long long crossProduct(const Point& a, const Point& b)
{
  return (a.first * b.second) - (a.second * b.first);
}

bool isInteger(const Fraction& fraction)
{
  return fraction.first / fraction.second * fraction.second == fraction.first;
}

int main()
{
  int count;
  std::cin >> count;
  long long x1, y1, x2, y2;
  std::vector<Line> lines;

  for (int i = 0; i < count; i++)
  {
    std::cin >> x1 >> y1 >> x2 >> y2;
    lines.emplace_back(Point{x1, y1}, Point{x2, y2});
  }

  unsigned long long total(0);
  for (int i = 0; i < count; i++)
  {
    auto normalized = normalize(lines[i]);
    total += gcd(normalized.first, normalized.second) + 1;
  }

  for (int i = 0; i < count; i++)
  {
    auto p = lines[i].first;
    auto r = lines[i].second - p;
    std::set<Point> points;
    for (int j = i + 1; j < count; j++)
    {
      auto q = lines[j].first;
      auto s = lines[j].second - q;

      auto crossed = crossProduct(r, s);
      if (!crossed) continue;
      Fraction t1(crossProduct((q - p), s), crossed);
      Fraction t2(crossProduct((p - q), r), crossProduct(s, r));
      normalize(t1);
      normalize(t2);
      if (t1.first <= t1.second && t1.first >= 0 &&
          t2.first <= t2.second && t2.first >= 0)
      {
        auto intersect = r * t1 + p;
        if (isInteger(intersect.first) && isInteger(intersect.second))
        {
          points.emplace(
            std::round(intersect.first.first / intersect.first.second),
            std::round(intersect.second.first / intersect.second.second));
        }
      }
    }
    total -= points.size();
  }

  std::cout << total << std::endl;

  return 0;
}

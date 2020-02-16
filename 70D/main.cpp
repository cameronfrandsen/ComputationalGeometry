#include <iostream>
#include <set>

typedef std::pair<long long, long long> Point;

Point operator-(const Point& p1, const Point& p2)
{
  return {p1.first - p2.first, p1.second - p2.second};
}

bool operator<(const Point& lhs, const Point& rhs)
{
  return lhs.first < rhs.first;
}

struct Comp
{
  bool operator()(const Point& lhs, const Point& rhs) const
  {
    return lhs.first < rhs.first;
  }
};

long long crossProduct(const Point& a, const Point& b)
{
  return (a.first * b.second) - (a.second * b.first);
}

long long crossProduct(const Point& p1, const Point& p2, const Point& p3)
{
  return crossProduct(p2 - p1, p3 - p1);
}

bool belowTop(const std::set<Point, Comp>& high, const Point& p)
{
  auto lower = high.lower_bound(p);
  if (lower == high.end()) return false;
  if (lower->first == p.first) return lower->second >= p.second;
  auto higher = lower;
  lower--;
  if (lower == high.end() || higher == high.end()) return false;
  return crossProduct(*lower, *higher, p) <= 0;
}

bool aboveBottom(const std::set<Point, Comp>& low, const Point& p)
{
  auto lower = low.lower_bound(p);
  if (lower == low.end()) return false;
  if (lower->first == p.first) return lower->second <= p.second;
  auto higher = lower;
  lower--;
  if (lower == low.end() || higher == low.end()) return false;
  return crossProduct(*lower, *higher, p) >= 0;
}

void removeRight(std::set<Point, Comp>& low, const Point& p, int dir)
{
  auto lower = low.lower_bound(p);
  if (lower == low.end()) return;
  if (lower->first == p.first) lower = low.erase(lower);
  if (lower == low.end()) return;
  auto higher = lower;
  higher++;
  while (higher != low.end() && crossProduct(p, *lower, *higher) * dir > 0)
  {
    higher++;
    lower = low.erase(lower);
  }
}

void removeLeft(std::set<Point, Comp>& low, const Point& p, int dir)
{
  bool toIncrease(true);
  auto lower = low.lower_bound(p);
  if (lower == low.end())
  {
    lower = low.begin();
    if (lower == low.end()) return;
    for (auto i = 0; i < low.size() - 1; i++)
      lower++;
    toIncrease = false;
  }
  else
  {
    lower--;
    if (lower == low.end()) return;
  }
  auto higher = lower;
  lower--;
  while (lower != low.end() && crossProduct(*higher, *lower, p) * dir < 0)
  {
    lower--;
    higher = low.erase(higher);
    higher--;
  }
}

int main()
{
  std::set<Point, Comp> low;
  std::set<Point, Comp> high;

  int count(0);

  std::cin >> count;

  long long x, y;
  int option;

  for (int i = 0; i < count; i++)
  {
    std::cin >> option >> x >> y;
    Point p;
    p.first = x;
    p.second = y;

    if (option == 1)
    {

      bool below = belowTop(high, p);
      bool above = aboveBottom(low, p);

      if (!below)
      {
        removeRight(high, p, 1);
        removeLeft(high, p, 1);
        high.emplace(p);
      }
      if (!above)
      {
        removeRight(low, p, -1);
        removeLeft(low, p, -1);
        low.emplace(p);
      }
    }
    else if (option == 2)
    {
      if (belowTop(high, p) && aboveBottom(low, p))
        std::cout << "YES" << std::endl;
      else
        std::cout << "NO" << std::endl;
    }
  }

  return 0;
}

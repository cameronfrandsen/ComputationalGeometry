#include <iostream>
#include <set>

typedef std::pair<long long, long long> Point;

Point operator-(const Point& p1, const Point& p2)
{
  return {p1.first - p2.first, p1.second - p2.second};
}

struct PointCmp
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

bool isLower(const std::set<Point, PointCmp> set, const Point& p)
{
  auto t = set.find(p);
  if (t != set.end())
  {
    if (t->second < p.second) return false;
    return true;
  }
  auto lower = set.lower_bound(p);
  auto upper = set.upper_bound(p);
  if (lower == set.end() || upper == set.end()) return false;
  if (crossProduct(*lower, *upper, p) < 0) return false;
  return true;
}

bool isHigher(const std::set<Point, PointCmp> set, const Point& p)
{
  auto t = set.find(p);
  if (t != set.end())
  {
    if (t->second > p.second) return false;
    return true;
  }
  auto lower = set.lower_bound(p);
  auto upper = set.upper_bound(p);
  if (lower == set.end() || upper == set.end()) return false;
  if (crossProduct(*lower, *upper, p) > 0) return false;
  return true;
}

void insertUp(std::set<Point, PointCmp>& set, const Point& p, int dir)
{
  auto up = set.upper_bound(p);
  if (up == set.end())
  {
    auto cur = set.find(p);
    if (cur == set.end() || cur->second > p.second) return;
    set.erase(cur);
    return;
  }

  up++;
  if (up == set.end()) return;
  auto next = up;
  next++;
  while (next != set.end() && crossProduct(p, *up, *next) * dir > 0)
  {
    next++;
    set.erase(up++);
  }
}

void insertLow(std::set<Point, PointCmp>& set, const Point& p, int dir)
{
  auto down = set.lower_bound(p);
  if (down == set.end())
  {
    auto cur = set.find(p);
    if (cur == set.end() || cur->second < p.second) return;
    set.erase(cur);
    return;
  }

  down--;
  if (down == set.end()) return;
  auto next = down;
  next--;
  while (next != set.end() && crossProduct(p, *down, *next) * dir < 0)
  {
    next--;
    set.erase(down--);
  }
}

int main()
{
  std::set<Point, PointCmp> low;
  std::set<Point, PointCmp> high;

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

      bool isLow = isLower(high, p);
      bool isHigh = isHigher(low, p);

      if (!isLow)
      {
        insertUp(high, p, 1);
        insertLow(high, p, 1);
        high.emplace(p);
      }
      if (!isHigh)
      {
        insertUp(low, p, -1);
        insertLow(low, p, -1);
        low.emplace(p);
      }
    }
    else if (option == 2)
    {
      bool isLow = isLower(high, p);
      bool isHigh = isHigher(low, p);
      if (isLow && isHigh)
        std::cout << "YES" << std::endl;
      else
        std::cout << "NO" << std::endl;
    }
  }

  return 0;
}
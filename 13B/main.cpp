#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

struct Point
{
  long long x;
  long long y;
  Point(long long xt, long long yt) : x(xt), y(yt) {}
};

bool operator==(const Point& a, const Point& b)
{
  return a.x == b.x && a.y == b.y;
}

Point operator-(const Point& a, const Point& b)
{
  return {a.x - b.x, a.y - b.y};
}

void swap(Point& p1, Point& p2)
{
  Point t = p1;
  p1 = p2;
  p2 = t;
}

struct Line
{
  Point p1;
  Point p2;
  Line(const Point& tp1, const Point& tp2) : p1(tp1), p2(tp2) {}
};

long long crossProduct(const Point& a, const Point& b)
{
  return (a.x * b.y) - (a.y * b.x);
}

long long dotProduct(const Point& p1, const Point& p2)
{
  return (p1.x * p2.x) + (p2.y * p1.y);
}

bool intersectsL1(const Line& l1, Line& l3)
{
  if (!crossProduct(l1.p2 - l1.p1, l3.p2 - l1.p1))
  {
    swap(l3.p1, l3.p2);
    return true;
  }
  return crossProduct(l1.p2 - l1.p1, l3.p1 - l1.p1) == 0;
}

bool intersectsL2(const Line& l2, Line& l3)
{
  return crossProduct(l2.p2 - l2.p1, l3.p2 - l2.p1) == 0;
}

bool containsSamePoint(Line& l1, Line& l2)
{
  if (l1.p1 == l2.p1) return true;
  if (l1.p1 == l2.p2)
  {
    swap(l2.p1, l2.p2);
    return true;
  }
  if (l1.p2 == l2.p1)
  {
    swap(l1.p1, l1.p2);
    return true;
  }
  if (l1.p2 == l2.p2)
  {
    swap(l1.p1, l1.p2);
    swap(l2.p1, l2.p2);
    return true;
  }
  return false;
}

bool verifyAngle(const Line& l1, const Line& l2)
{
  return dotProduct(l1.p2 - l1.p1, l2.p2 - l2.p1) >= 0;
}

// double getDistance(const Point& p1, const Point& p2)
//{
//  return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
//}

bool verifyRatio(Line& l1, Line& l2, Line& l3)
{
  auto firstX = std::abs(l1.p1.x - l3.p1.x);
  auto firstY = std::abs(l1.p1.y - l3.p1.y);
  auto secondX = std::abs(l1.p1.x - l1.p2.x);
  auto secondY = std::abs(l1.p1.y - l1.p2.y);
  if (firstX * 5 < secondX || firstX * 1.25 > secondX) return false;
  if (firstY * 5 < secondY || firstY * 1.25 > secondY) return false;

  firstX = std::abs(l2.p1.x - l3.p2.x);
  firstY = std::abs(l2.p1.y - l3.p2.y);
  secondX = std::abs(l2.p1.x - l2.p2.x);
  secondY = std::abs(l2.p1.y - l2.p2.y);
  if (firstX * 5 < secondX || firstX * 1.25 > secondX) return false;
  if (firstY * 5 < secondY || firstY * 1.25 > secondY) return false;

  return true;
}

bool verifyInAL1(const Line& l1, Line& l3)
{
  return dotProduct(l1.p2 - l1.p1, l3.p1 - l1.p1) > 0;
}

bool verifyInAL2(const Line& l2, Line& l3)
{
  return dotProduct(l2.p2 - l2.p1, l3.p2 - l2.p1) > 0;
}

void swap(Line& l1, Line& l2)
{
  Line t = l1;
  l1 = l2;
  l2 = t;
}

bool isAnA(Line& l1, Line& l2, Line& l3)
{
  if (containsSamePoint(l1, l2))
  {
  }
  else if (containsSamePoint(l1, l3))
    swap(l2, l3);
  else if (containsSamePoint(l2, l3))
    swap(l1, l3);
  else
    return false;

  if (crossProduct(l1.p2 - l1.p1, l2.p2 - l1.p1) == 0) return false;

  if (!intersectsL1(l1, l3) || !intersectsL2(l2, l3)) return false;

  if (!verifyInAL1(l1, l3) || !verifyInAL2(l2, l3)) return false;

  if (!verifyAngle(l1, l2)) return false;

  return verifyRatio(l1, l2, l3);
}

int main()
{
  std::ios::sync_with_stdio(false);
  int count;
  std::cin >> count;
  long long x11, y11, x12, y12, x21, y21, x22, y22, x31, y31, x32, y32;

  for (int i = 0; i < count; i++)
  {
    std::cin >> x11 >> y11 >> x12 >> y12 >> x21 >> y21 >> x22 >> y22 >> x31 >>
      y31 >> x32 >> y32;
    Line l1{{x11, y11}, {x12, y12}};
    Line l2{{x21, y21}, {x22, y22}};
    Line l3{{x31, y31}, {x32, y32}};
    if (isAnA(l1, l2, l3))
      std::cout << "YES" << std::endl;
    else
      std::cout << "NO" << std::endl;
  }

  return 0;
}

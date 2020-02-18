#include <cmath>
#include <iostream>
#include <vector>

struct Point
{
  long long x;
  long long y;
  Point(long long xt, long long yt) : x(xt), y(yt) {}
};

Point operator-(const Point& a, const Point& b)
{
  return {a.x - b.x, a.y - b.y};
}

int main()
{
  std::ios::sync_with_stdio(false);
  int count;
  std::cin >> count;


  return 0;
}

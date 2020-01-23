#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

typedef std::pair<double, double> Point;
typedef std::pair<Point, Point> Line;

Point operator-(const Point& p1, const Point& p2)
{
  return {p1.first - p2.first, p1.second - p2.second};
}

double dotProduct(const Point& p1, const Point& p2)
{
  return (p1.first * p2.first) + (p2.second * p1.second);
}

bool orderSquare(std::vector<Line>& lines)
{
  for (size_t i = 0; i < 3; i++)
  {
    size_t j = i + 1;
    for (; j < 4; j++)
    {
      if (lines[i].second == lines[j].first)
      {
        std::swap(lines[j], lines[i + 1]);
        break;
      }
      if (lines[i].second == lines[j].second)
      {
        std::swap(lines[j].first, lines[j].second);
        std::swap(lines[j], lines[i + 1]);
        break;
      }
    }
    if (j == 4) return false;
  }
  return lines[0].first == lines[3].second;
}

bool checkSquare(std::vector<Line>& lines)
{
  for (size_t i = 0; i < 3; i++)
  {
    if (!((lines[i].first.first == lines[i].second.first) ^
        (lines[i].first.second == lines[i].second.second)))
      return false;
    if (dotProduct(lines[i].second - lines[i].first,
                   lines[i + 1].first - lines[i + 1].second) != 0)
      return false;
  }
  return true;
}

int main()
{
  std::vector<Line> lines(4);
  for (auto& l : lines)
  {
    std::cin >> l.first.first >> l.first.second >> l.second.first >>
      l.second.second;
  }

  if (!orderSquare(lines))
  {
    std::cout << "NO" << std::endl;
    return 0;
  }

  if (checkSquare(lines))
    std::cout << "YES" << std::endl;
  else
    std::cout << "NO" << std::endl;

  return 0;
}
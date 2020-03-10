#include <algorithm>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

typedef std::pair<long long, long long> Point;
typedef std::pair<long long, std::pair<size_t, size_t>> distance;

int main()
{
  std::ios::sync_with_stdio(false);

  int count;
  std::cin >> count;

  std::vector<Point> points(count);

  for (int i = 0; i < count; i++)
    std::cin >> points[i].first >> points[i].second;

  std::vector<distance> distances;

  for (size_t i = 0; i < points.size(); i++)
  {
    auto p1 = points[i];
    for (size_t j = i + 1; j < points.size(); j++)
    {
      auto p2 = points[j];
      auto x = p1.first - p2.first;
      auto y = p1.second - p2.second;
      distances.emplace_back(x * x + y * y, std::pair<size_t, size_t>{i, j});
    }
  }

  std::sort(distances.begin(),
            distances.end(),
            [](const distance& lhs, const distance& rhs) {
              return lhs.first > rhs.first;
            });

  int max = count / 32 + 1;
  std::vector<std::vector<int>> hit(count, std::vector<int>(count));

  uint64_t one(1);
  for (auto&& d : distances)
  {
    hit[d.second.first][d.second.second / 32] |= (one << (d.second.second % 32));
    hit[d.second.second][d.second.first / 32] |= (one << (d.second.first % 32));

    for (int i = 0; i <= max; i++)
    {
      if (hit[d.second.first][i] & hit[d.second.second][i])
      {
        std::cout << std::fixed << std::setprecision(8)
                  << std::sqrt(d.first) / 2 << std::endl;
        return 0;
      }
    }
  }

  return 0;
}

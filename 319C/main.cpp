#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

// typedef std::pair<long long, long long> Point;
struct Tree
{
  long long a;
  long long b;
  long long dp;
  Tree() : a(0), b(0), dp(0) {}
  Tree(long long a, long long b) : a(a), b(b), dp(0) {}
  Tree(long long a, long long b, long long dp) : a(a), b(b), dp(dp) {}
};

long long calc(const Tree& p1, const Tree& p2)
{
  auto diff = p2.b - p1.b;
  return (p1.dp - p2.dp + diff - 1) / diff;
}

int main()
{
  std::ios::sync_with_stdio(false);

  int count;
  std::cin >> count;

  std::vector<Tree> trees(count);

  for (int i = 0; i < count; i++)
    std::cin >> trees[i].a;
  for (int i = 0; i < count; i++)
    std::cin >> trees[i].b;

  std::vector<size_t> queue(count);
  size_t size(1);
  size_t inc(0);
  queue[0] = 0;
  for (int i = 1; i < trees.size(); i++)
  {
    while (inc + 1 < size &&
           calc(trees[queue[inc]], trees[queue[inc + 1]]) <= trees[i].a)
      inc++;

    trees[i].dp = trees[i].a * trees[queue[inc]].b + trees[queue[inc]].dp;

    while (inc + 1 < size &&
           calc(trees[queue[size - 2]], trees[queue[size - 1]]) >=
             calc(trees[queue[size - 1]], trees[i]))
      size--;

    if (inc >= size) inc = size - 1;

    queue[size++] = i;
  }

  std::cout << trees[count - 1].dp << std::endl;

  return 0;
}

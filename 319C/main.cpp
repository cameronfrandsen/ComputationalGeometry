#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <vector>

// typedef std::pair<long long, long long> Point;
struct Tree
{
  unsigned long long a;
  unsigned long long b;
  unsigned long long dp;
  Tree() : a(0), b(0), dp(0) {}
  Tree(unsigned long long a, unsigned long long b) : a(a), b(b), dp(0) {}
  Tree(unsigned long long a, unsigned long long b, unsigned long long dp)
    : a(a), b(b), dp(dp)
  {
  }
};

Tree operator-(const Tree& a, const Tree& b)
{
  return {0, a.b - b.b, a.dp - b.dp};
}

bool isCrossNegative(const Tree& a, const Tree& b)
{
  return a.b * b.dp <= a.dp * b.b;
}

bool isCrossNegative(const Tree& p1, const Tree& p2, const Tree& p3)
{
  return isCrossNegative(p2 - p1, p3 - p1);
}

unsigned long long calc(const Tree& p1, const Tree& p2)
{
  return p1.dp + p1.b * p2.a;
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
           calc(trees[queue[inc + 1]], trees[i]) <=
             calc(trees[queue[inc]], trees[i]))
      inc++;

    trees[i].dp = calc(trees[queue[inc]], trees[i]);

    while (
      size > 1 &&
      isCrossNegative(trees[i], trees[queue[size - 1]], trees[queue[size - 2]]))
      size--;

    if (inc >= size) inc = size - 1;

    queue[size++] = i;
  }

  std::cout << trees[count - 1].dp << std::endl;

  return 0;
}

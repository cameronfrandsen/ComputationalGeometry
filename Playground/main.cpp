//#include <bits/stdc++.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

typedef long long ll;
typedef long double ld;

namespace his
{
  using namespace std;

  const int MAXN = 101000;

  long long ar1[MAXN], ar2[MAXN], tot[MAXN];
  long long last[MAXN];

  long long ret(int a, int b)
  {
    return (last[a] - last[b] + ar2[b] - ar2[a] - 1) / (ar2[b] - ar2[a]);
  }

  ll solve(const ll* a, const ll* b, int n)
  {
    //std::ofstream fout("his.txt");
    for (int i = 0; i < n; i++)
    {
      ar1[i] = a[i];
    }
    for (int i = 0; i < n; i++)
    {
      ar2[i] = b[i];
    }
    int inc = 0;
    int dec = 0;
    tot[dec++] = 0;
    for (int i = 1; i < n; i++)
    {
      while (dec - inc > 1 && ret(tot[inc], tot[inc + 1]) <= ar1[i])
      {
        inc++;
      }
      last[i] = ar1[i] * ar2[tot[inc]] + last[tot[inc]];

      while (dec - inc > 1 &&
             ret(tot[dec - 1], i) <= ret(tot[dec - 2], tot[dec - 1]))
      {
        dec--;
      }
      //fout << last[i] << std::endl;
      tot[dec++] = i;
    }
    return last[n - 1];
  }
}

namespace mine
{
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

  ll solve(const ll* a, const ll* b, int n)
  {
    //std::ofstream fout("mine.txt");
    std::ios::sync_with_stdio(false);

    int count = n;

    std::vector<Tree> trees(count);

    for (int i = 0; i < count; i++)
      trees[i].a = a[i];
    for (int i = 0; i < count; i++)
      trees[i].b = b[i];

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

      while (size > 1 &&
             isCrossNegative(
               trees[i], trees[queue[size - 1]], trees[queue[size - 2]]))
        size--;

      if (inc >= size) inc = size - 1;

      queue[size++] = i;
      //fout << trees[i].dp << std::endl;
    }
    return trees[count - 1].dp;
  }
}

void printCase(const ll* a, const ll* b, int n)
{
  std::ofstream fout("testcase.txt");
  fout << "n = " << n << std::endl;
  for (int i = 0; i < n; ++i)
  {
    fout << a[i] << " ";
  }
  fout << std::endl;
  for (int i = 0; i < n; ++i)
  {
    fout << b[i] << " ";
  }
  fout << std::endl;
  fout.close();
}

void runTests()
{
  srand(static_cast<unsigned int>(time_t(0)));
  const int n = 10000;
  const int maxHeight = 1000000000;
  const int maxCost = 1000000000;
  ll* a;
  ll* b;
  a = new ll[n];
  b = new ll[n];
  for (int test = 0; test < 1000; ++test)
  {
    bool* usedA;
    usedA = new bool[maxHeight + 1];
    bool* usedB;
    usedB = new bool[maxCost + 1];
    memset(usedA, 0, sizeof(usedA));
    memset(usedB, 0, sizeof(usedB));
    for (int i = 0; i < n; ++i)
    {
      int ax, bx;
      while (usedA[ax = rand() % (maxHeight - 1) + 2])
        ;
      while (usedB[bx = rand() % maxCost + 1])
        ;
      a[i] = ax;
      b[i] = bx;
      usedA[ax] = true;
      usedB[bx] = true;
    }
    std::sort(a, a + n);
    std::sort(b, b + n, std::greater<>());
    a[0] = 1;
    b[n - 1] = 0;
    ll ans = mine::solve(a, b, n);
    ll actual = his::solve(a, b, n);
    if (ans != actual)
    {
      printf("CASE FAILED:\n");
      printCase(a, b, n);
      printf("Answer: %lld, Actual: %lld\n", ans, actual);
      return;
    }
    delete[] usedA;
    delete[] usedB;
  }
  delete[] a;
  delete[] b;
  printf("All test cases passed.\n");
}

int main()
{
   //runTests();

  std::ifstream fin("testcase.txt");

  int n;
  fin >> n;
  ll* a;
  ll* b;
  a = new ll[n];
  b = new ll[n];
  for (int i = 0; i < n; ++i)
  {
    fin >> a[i];
  }
  for (int i = 0; i < n; ++i)
  {
    fin >> b[i];
  }

  his::solve(a, b, n);
  //mine::solve(a, b, n);

  return 0;
}

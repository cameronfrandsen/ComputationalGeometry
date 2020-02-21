//#include <bits/stdc++.h>
#include <iostream>

using namespace std;

const int MAXN = 101000;

long long ar1[MAXN], ar2[MAXN], tot[MAXN];
long long last[MAXN];


long long ret(int a, int b) {
  return (last[a] - last[b] + ar2[b] - ar2[a] - 1) / (ar2[b] - ar2[a]);
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> ar1[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> ar2[i];
  }
  int inc = 0;
  int dec = 0;
  tot[dec++] = 0;
  for (int i = 1; i < n; i++) {
    while (dec - inc > 1 && ret(tot[inc], tot[inc + 1]) <= ar1[i]) {
      inc++;
    }
    last[i] = ar1[i] * ar2[tot[inc]] + last[tot[inc]];

    while (dec - inc > 1 && ret(tot[dec - 1], i) <= ret(tot[dec - 2], tot[dec - 1])) {
      dec--;
    }
    tot[dec++] = i;
  }
  cout << last[n - 1] << endl;
}

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 3;
// mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  string s;
  cin >> s;
  int n = s.length() - 2;

  cout << "3\n";
  cout << "L 2\n";
  cout << "R 2\n";
  cout << "R " << 2 * n + 3 << "\n";

  return 0;
}

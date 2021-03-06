#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<long long> vll;

const int INF = 0x3ffffff;
const int MOD = 1e9 + 7;
const ll HASH_KEY = 6151;
const ll HASH_MOD = 1610612741;

// mt19937 rdm(chrono::steady_clock::now().time_since_epoch().count());

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  int inc = -1, dec = 0x3f3f3f3f, a[n + 1] = {0};
  vector<bool> ans(n, false);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    if (a[i] > inc && a[i] < dec) {
      if (a[i] < a[i + 1]) {
        inc = a[i];
      } else {
        dec = a[i];
        ans[i] = true;
      }
    } else if (a[i] > inc) {
      inc = a[i];
    } else if (a[i] < dec) {
      dec = a[i];
      ans[i] = true;
    } else {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
  for (const auto &x : ans) {
    cout << (x ? "1 " : "0 ");
  }
  return 0;
}

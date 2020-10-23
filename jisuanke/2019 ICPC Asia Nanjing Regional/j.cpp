#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 400 + 3;
const int ALPHA = 1e9 + 10;
const ll NOT = 0;
const ll INF = 3ll * MAXN * ALPHA;
// 最大费用流时 NOT = 0， 最大费用流最大流时 NOT = -1ll * MAXN * ALPHA
// 点为 1 .. n （左为 1 .. nl， 右为 1 .. nr）
int n, nl, nr, lk[MAXN], pre[MAXN];
ll lx[MAXN], ly[MAXN], w[MAXN][MAXN], slack[MAXN];
bitset<MAXN> vy;

void init(int n) {
  ::n = n;
  memset(lk, 0, sizeof(int) * (n + 1));
  memset(pre, 0, sizeof(int) * (n + 1));
  memset(lx, 0, sizeof(ll) * (n + 1));
  memset(ly, 0, sizeof(ll) * (n + 1));
  memset(slack, 0, sizeof(ll) * (n + 1));
  for (int i = 0; i <= n; ++i) fill(w[i], w[i] + n + 1, NOT);
}

void add_edge(int x, int y, ll z) {
  if (w[y][x] < z) w[y][x] = z;
}

ll KM() {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) lx[i] = max(lx[i], w[i][j]);
  for (int i = 1, py, p, x; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) slack[j] = INF, vy[j] = 0;
    for (lk[py = 0] = i; lk[py]; py = p) {
      ll delta = INF;
      vy[py] = 1, x = lk[py];
      for (int y = 1; y <= n; ++y) {
        if (vy[y]) continue;
        if (lx[x] + ly[y] - w[x][y] < slack[y])
          slack[y] = lx[x] + ly[y] - w[x][y], pre[y] = py;
        if (slack[y] < delta) delta = slack[y], p = y;
      }
      for (int y = 0; y <= n; ++y)
        if (vy[y]) {
          lx[lk[y]] -= delta, ly[y] += delta;
        } else {
          slack[y] -= delta;
        }
    }
    for (; py; py = pre[py]) lk[py] = lk[pre[py]];
  }

  ll ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += lx[i] + ly[i];
    if (w[lk[i]][i] == NOT) ans -= NOT;
  }
  return ans;
}

int sum[MAXN];
ll b[MAXN], c[MAXN];
pair<ll, int> ap[MAXN];

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);

  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> ap[i].first;
  for (int i = 1; i <= n; ++i) cin >> ap[i].second;

  sum[0] = 0;
  sort(ap + 1, ap + n + 1);
  for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + ap[i].second;

  for (int i = 1; i <= n; ++i) cin >> b[i];
  for (int i = 1; i <= n; ++i) cin >> c[i];

  init(n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      ll bc = b[i] + c[j];
      int idx = lower_bound(ap + 1, ap + n + 1, make_pair(bc, INT_MIN)) - ap;
      add_edge(i, j, sum[idx - 1]);
    }

  cout << KM() << "\n";

  return 0;
}

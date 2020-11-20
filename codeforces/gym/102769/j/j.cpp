#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 3e5 + 3;
const int MAX_PRIME = 8960453 + 3;
const int MOD = 998244353;
const ll BASE = 709;
const ll HASH_MOD = 4611686018427387847ll;

char s[MAXN];
int fac[MAXN], inv[MAXN], fac_inv[MAXN], prime[MAXN * 2];
ll ha[MAXN], p[MAXN], pref[MAXN], suff[MAXN], value[MAXN * 2];
pair<ll, int> bin[MAXN];

int cnt[MAXN], pidx[MAXN], sidx[MAXN];
bitset<MAX_PRIME> mark;

ll fmul(ll a, ll b) {
  ll k = (ll)((1.l * a * b) / (1.l * HASH_MOD)), t = a * b - k * HASH_MOD;
  for (t -= HASH_MOD; t < 0; t += HASH_MOD) {}
  return t;
}
ll getRange(int l, int r) {
  return (ha[r] - fmul(ha[l - 1], p[r - l + 1]) + HASH_MOD) % HASH_MOD;
}

int gao(int n, int d) {
  int tot = 0;
  for (int l = 1, r = d; r <= n; l += d, r += d) value[tot++] = getRange(l, r);
  int bunch = n / d, rest = n % d;
  if (rest) {
    for (int r = n, l = n - d + 1; l >= 1; l -= d, r -= d)
      value[tot++] = getRange(l, r);
    sort(value, value + tot);
    tot = unique(value, value + tot) - value;
    pref[0] = pref[1] = suff[n] = suff[n + 1] = 1;
    for (int i = d; i <= n; i += d) {
      int idx = lower_bound(value, value + tot, getRange(i - d + 1, i)) - value;
      pidx[i] = idx;
      pref[i] = fmul(pref[i - d], prime[idx]);
    }
    for (int i = n - d + 1; i >= 1; i -= d) {
      int idx = lower_bound(value, value + tot, getRange(i, i + d - 1)) - value;
      sidx[i] = idx;
      suff[i] = fmul(suff[i + d], prime[idx]);
    }
    int sc = 0, cur = fac[bunch];
    memset(cnt, 0, tot * sizeof(int));
    for (int l = 1, r = rest; r <= n; l += d, r += d) {
      if (r + d <= n) {
        ++cnt[sidx[r + 1]];
        cur = 1ll * cur * inv[cnt[sidx[r + 1]]] % MOD;
      }
      bin[sc++] = {fmul(pref[l - 1], suff[r + 1]), l};
    }
    sort(bin, bin + sc);
    mark[bin[0].second] = 1;
    for (int i = 1; i < sc; ++i)
      mark[bin[i].second] = bin[i].first != bin[i - 1].first;

    int res = 0;
    for (int l = 1, r = rest; r <= n; l += d, r += d) {
      if (l - 1 >= 1) {
        ++cnt[pidx[l - 1]];
        cur = 1ll * cur * inv[cnt[pidx[l - 1]]] % MOD;
      }
      if (mark[l]) {
        res += cur;
        if (res >= MOD) res -= MOD;
      }
      if (r + 1 <= n) {
        cur = 1ll * cur * cnt[sidx[r + 1]] % MOD;
        --cnt[sidx[r + 1]];
      }
    }
    return res;
  } else {
    sort(value, value + tot);
    ll pre = value[0];
    int res = fac[bunch], cnt = 1;
    for (int i = 1; i < tot; ++i) {
      if (value[i] != pre) {
        if (cnt > 1) res = 1ll * res * fac_inv[cnt] % MOD;
        cnt = 1, pre = value[i];
      } else {
        ++cnt;
      }
    }
    if (cnt > 1) res = 1ll * res * fac_inv[cnt] % MOD;
    return res;
  }
}

void solve() {
  cin >> (s + 1);
  int n = strlen(s + 1);
  for (int i = 1; i <= n; ++i)
    ha[i] = (fmul(ha[i - 1], BASE) + s[i]) % HASH_MOD;

  int ans = 0;
  for (int d = 1; d <= n; ++d) {
    ans += gao(n, d);
    if (ans >= MOD) ans -= MOD;
    // cerr << "# " << ans << endl;
  }
  cout << ans << "\n";
}

void prework() {
  p[0] = 1;
  for (int i = 1; i < MAXN; ++i) p[i] = fmul(p[i - 1], BASE);
  fac[0] = fac[1] = 1;
  fac_inv[0] = fac_inv[1] = inv[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % MOD;
    inv[i] = 1ll * (MOD - MOD / i) * inv[MOD % i] % MOD;
    fac_inv[i] = 1ll * fac_inv[i - 1] * inv[i] % MOD;
  }

  int pc = 0;
  for (int i = 2; i < MAX_PRIME; ++i) {
    if (!mark[i]) prime[pc++] = i;
    for (int j = 0; j < pc; ++j) {
      int t = i * prime[j];
      if (t >= MAX_PRIME) break;
      mark[t] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);

  prework();

  int T;
  cin >> T;
  for (int step = 1; step <= T; ++step) {
    cout << "Case #" << step << ": ";
    solve();
  }

  return 0;
}

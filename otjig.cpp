//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma target("avx,avx2")
#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mp make_pair
#define rep(n) for (int (i) = 0; (i) < (n); (i)++)
#define debug(x) cerr << __LINE__ << ": " << (#x) << " = " << x << endl

//#define int long long
using ll = long long;
using ld = long double;

using namespace std;

mt19937 gen(1984);

bool check(vector<int> &P) {
    for (int i = 0; i < P.size(); i++) {
        for (int j = i + 1; j < P.size(); j++) {
            if (i + P[i] == j + P[j] || i - P[i] == j - P[j])
                return false;
        }
    }
    return true;
}

void solve() {
    int n;
    cin >> n;

    vector<int> P(n);
    iota(all(P), 0);
    shuffle(all(P), gen);
    vector<int> D1(n * 2 - 1), D2(n * 2 - 1);

    for (int i = 0; i < n; i++) {
        D1[i + P[i]]++;
        D2[i - P[i] + (n - 1)]++;
    }

    auto calc_score = [&](){
        int score = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++)
                score += (P[i] + i == P[j] + j) || (P[i] - i == P[j] - j);
        }
        return score;
    };

    auto apply = [&](int i, int j, int score){
        auto calc_d = [&P, n](int i){
            return mp(i + P[i], i - P[i] + (n - 1));
        };
        vector<int> ar_d1, ar_d2;
        auto calc_subscore = [&](){
            int res = 0;
            for (auto d1 : ar_d1)
                res += D1[d1] * (D1[d1] - 1) / 2;
            for (auto d2 : ar_d2)
                res += D2[d2] * (D2[d2] - 1) / 2;
            return res;
        };
        for (int tmp = 0; tmp < 2; tmp++) {
            auto [d1i, d2i] = calc_d(i);
            auto [d1j, d2j] = calc_d(j);
            ar_d1.push_back(d1i), ar_d1.push_back(d1j);
            ar_d2.push_back(d2i), ar_d2.push_back(d2j);
            swap(P[i], P[j]);
        }
        ar_d1.erase(unique(all(ar_d1)), ar_d1.end());
        ar_d2.erase(unique(all(ar_d2)), ar_d2.end());
        score -= calc_subscore();
        {
            auto [d1i, d2i] = calc_d(i);
            auto [d1j, d2j] = calc_d(j);
            D1[d1i]--, D1[d1j]--;
            D2[d2i]--, D2[d2j]--;
        }
        swap(P[i], P[j]);
        {
            auto [d1i, d2i] = calc_d(i);
            auto [d1j, d2j] = calc_d(j);
            D1[d1i]++, D1[d1j]++;
            D2[d2i]++, D2[d2j]++;
        }
        score += calc_subscore();
        return score;
    };

    int score = 0;
    for (int i = 0; i < 2 * n - 1; i++)
        score += D1[i] * (D1[i] - 1) / 2 + D2[i] * (D2[i] - 1) / 2;
    double T = 1;
    double c = 0.999;
    uniform_real_distribution<double> dis(0, 1);
    while (score != 0) {
        int i = gen() % n, j = gen() % n;
        if (i == j) continue;

        swap(P[i], P[j]);
        int real_new_score = calc_score();
        swap(P[i], P[j]);

        int new_score = apply(i, j, score);

        int d = new_score - score;
        if (new_score < score || dis(gen) < exp(-d / T))
            score = new_score;
        else {
            apply(i, j, new_score);
        }
        T *= c;
    }
    assert(check(P));
    rep(n) {
        cout << P[i] + 1 << '\n';
    }
}

//#define FILE
//#define LOCAL
//#define DEBUG
signed main() {
#ifdef FILE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
#ifndef DEBUG
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(20);
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
    }
#else
    int cnt = 0;
    while (true) {
        cout << ++cnt << '\n';

    }
#endif
}

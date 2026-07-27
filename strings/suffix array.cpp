vector<int> suffix_array(string &s) {
    s += '#';
    int n = s.size();
    vector<int> P(n);
    iota(all(P), 0);
    sort(all(P), [&s](int i, int j){return s[i] < s[j];});
    vector<int> C(n);
    for (int i = 1; i < n; i++)
        C[P[i]] = C[P[i - 1]] + (s[P[i]] != s[P[i - 1]]);
    for (int len = 1; len < n; len <<= 1) {
        vector<int> cnt(n);
        for (int i = 0; i < n; i++) {
            P[i] = (P[i] - len + n) % n;
            cnt[C[P[i]]]++;
        }
        for (int i = 1; i < n; i++)
            cnt[i] += cnt[i - 1];
        vector<int> P2(n), C2(n);
        for (int i = n - 1; i >= 0; i--) {
            P2[cnt[C[P[i]]] - 1] = P[i];
            cnt[C[P[i]]]--;
        }
        for (int i = 1; i < n; i++) {
            auto k1 = mp(C[P2[i]], C[(P2[i] + len) % n]);
            auto k2 = mp(C[P2[i - 1]], C[(P2[i - 1] + len) % n]);
            C2[P2[i]] = C2[P2[i - 1]] + (k1 != k2);
        }
        swap(P, P2);
        swap(C, C2);
    }
    P.erase(P.begin());
    s.pop_back();
    return P;
}

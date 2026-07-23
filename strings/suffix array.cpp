vector<int> suffix_array(string &s) {
    s += '#';
    int n = (int) s.size();
    vector<int> P(n);
    iota(all(P), 0);
    sort(all(P), [&s](int i, int j){return s[i] < s[j];});
    vector<int> C(n);
    for (int i = 1; i < n; i++)
        C[P[i]] = C[P[i - 1]] + (s[P[i]] != s[P[i - 1]]);
    for (int h = 0; (1 << h) < n; h++) {
        vector<vector<int>> cnt(n);
        for (int i = 0; i < n; i++) {
            P[i] = (P[i] - (1 << h) + n) % n;
            cnt[C[P[i]]].push_back(P[i]);
        }
        vector<int> P2;
        for (int i = 0; i < n; i++) {
            for (int j : cnt[i])
                P2.push_back(j);
        }
        vector<int> C2(n);
        for (int i = 1; i < n; i++) {
            auto k1 = mp(C[P2[i - 1]], C[(P2[i - 1] + (1 << h)) % n]);
            auto k2 = mp(C[P2[i]], C[(P2[i] + (1 << h)) % n]);
            C2[P2[i]] = C2[P2[i - 1]] + (k1 != k2);
        }
        swap(C, C2);
        swap(P, P2);
    }
    P.erase(P.begin());
    s.pop_back();
    return P;
}

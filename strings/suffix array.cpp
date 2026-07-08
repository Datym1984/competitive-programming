vector<int> SuffixArray(string s) {
    int n = s.size();
    vector<int> P(n), C(n);
    for (int i = 0; i < n; i++)
        P[i] = i;
    sort(P.begin(), P.end(), [&](int i, int j){return s[i] < s[j];});
    int classes = 0;
    for (int i = 1; i < n; i++) {
        if (s[P[i - 1]] != s[P[i]])
            classes++;
        C[P[i]] = classes;
    }
    for (int h = 0; (1 << h) < n; h++) {
        sort(all(P), [&](auto i, auto j){
            pair<int, int> i2 = {C[i], C[(i + (1 << h)) % n]};
            pair<int, int> j2 = {C[j], C[(j + (1 << h)) % n]};
            return i2 < j2;
        });
        C[P[0]] = 0;
        classes = 0;
        vector<int> C2(n);
        for (int i = 1; i < n; i++) {
            int mid1 = (P[i - 1] + (1 << h)) % n;
            int mid2 = (P[i] + (1 << h)) % n;
            if (C[mid1] != C[mid2] || C[P[i - 1]] != C[P[i]])
                classes++;
            C2[P[i]] = classes;
        }
        C = C2;
    }
    return P;
}

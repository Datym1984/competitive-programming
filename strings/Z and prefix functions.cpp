vector<int> PrefFunc(string &s) {
    int n = s.size();
    vector<int> P(n);
    for (int i = 1; i < n; i++) {
        int j = P[i - 1];
        while (j != 0 && s[j] != s[i]) {
            j = P[j - 1];
        }
        if (s[j] == s[i])
            j++;
        P[i] = j;
    }
    return P;
}

vector<int> ZFunc(string &s) {
    int n = s.size();
    vector<int> Z(n);
    int l = -1, r = -1;
    for (int i = 1; i < n; i++) {
        if (r >= i)
            Z[i] = min(Z[i - l], r - i + 1);
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
            Z[i]++;
        if (i + Z[i] - 1 >= r) {
            l = i;
            r = i + Z[i] - 1;
        }
    }
    return Z;
}

struct ST {
    const int k = 20;
    vector<int> lg;
    vector<vector<int>> t;

    void build(vector<int> &A) {
        int n = (int) A.size();
        lg.resize(n + 1);
        t.resize(k, vector<int> (n));
        for (int i = 0; i < n; i++)
            t[0][i] = A[i];
        for (int i = 1; i < k; i++) {
            for (int j = 0; j + (1 << i) <= n; j++) {
                t[i][j] = min(t[i - 1][j], t[i - 1][j + (1 << (i - 1))]);
            }
        }

        for (int i = 2; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
    }

    ST(vector<int> A) {
        build(A);
    }

    int get(int l, int r) {//return min[l:r)
        assert(l < r);
        int sz = r - l;
        return min(t[lg[sz]][l], t[lg[sz]][r - (1 << lg[sz])]);
    }
};

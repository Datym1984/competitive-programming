const int MAXN = 1e5 + 10;
mt19937_64 gen(19824);
vector<ull> D(MAXN);

void precalc() {
    for (int i = 0; i < MAXN; i++)
        D[i] = gen();
}

ull tree_hash(vector<vector<int>> &g) {
    int n = g.size();
    vector<int> cent, sz(n);

    auto precalc = [&](auto&&self, int v, int p)->void {
        sz[v] = 1;
        bool is_c = true;
        for (int u : g[v]) {
            if (u == p) continue;
            self(self, u, v);
            sz[v] += sz[u];
            if (sz[u] * 2 > n)
                is_c = false;
        }
        if ((n - sz[v]) * 2 > n)
            is_c = false;
        if (is_c)
            cent.push_back(v);
    };

    precalc(precalc, 0, -1);

    auto dfs = [&](auto&&self, int v, int p, int d)->ull {
        ull h = 1;
        for (int u : g[v]) {
            if (u == p) continue;
            ull hu = self(self, u, v, d + 1);
            h *= (hu + D[d]);
        }
        return h;
    };

    if (cent.size() == 1)
        return dfs(dfs, cent[0], -1, 0);
    if (cent.size() == 2) {
        ull h1 = dfs(dfs, cent[0], cent[1], 0);
        ull h2 = dfs(dfs, cent[1], cent[0], 0);
        return (h1 + D[0]) * (h2 * D[1]);
    }
    assert(0);
}

struct matching {
    vector<vector<int>> g;
    vector<int> c, used2;
    vector<bool> used;
    int n;

    matching(int n) : n(n) {
        used.resize(n);
        used2.resize(n);
        c.resize(n, -1);
        g.resize(n);
    }

    void add_edge(int v, int u) {
        g[v].push_back(u);
        g[u].push_back(v);
    }

    bool kuhn(int v, int num) {
        if (used2[v] == num) return false;
        used2[v] = num;
        for (int u : g[v]) {
            if (c[u] == -1) {
                c[u] = v;
                return true;
            }
        }
        for (int u : g[v]) {
            if (kuhn(c[u], num)) {
                c[u] = v;
                return true;
            }
        }
        return false;
    }

    void dfs(int v, int col, int &num) {
        used[v] = true;
        if (col == 0) {
            kuhn(v, num++);
        }
        for (int u : g[v]) {
            if (!used[u])
                dfs(u, 1 - col, num);
        }
    }

    vector<pair<int, int>> solve() {
        int num = 1;
        for (int v = 0; v < n; v++) {
            if (!used[v])
                dfs(v, 0, num);
        }
        vector<pair<int, int>> ans;
        for (int i = 0; i < n; i++) {
            if (c[i] != -1)
                ans.emplace_back(i, c[i]);
        }
        return ans;
    }
};

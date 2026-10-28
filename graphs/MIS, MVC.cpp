struct matching {
    vector<vector<int>> g;
    vector<int> c, used2;
    vector<bool> used;
    vector<int> part;
    int n;

    matching(int n) : n(n) {
        used.resize(n);
        used2.resize(n);
        c.resize(n, -1);
        g.resize(n);
        part.resize(n, -1);
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
        part[v] = col;
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
                ans.emplace_back(c[i], i);
        }
        return ans;
    }

    void MIS_dfs(int v, vector<bool> &vis) {
        vis[v] = true;
        for (int u : g[v]) {
            if (vis[u]) continue;
            vis[u] = true;
            if (c[u] != -1 && !vis[c[u]])
                MIS_dfs(c[u], vis);
        }
    }

    vector<int> MIS() {
        vector<bool> vis(n, false);
        for (int v = 0; v < n; v++) {
            if (part[v] == 0) {
                bool is_used = false;
                for (int u : g[v]) {
                    if (c[u] == v)
                        is_used = true;
                }
                if (!is_used)
                    MIS_dfs(v, vis);
            }
        }

        vector<int> vertex_cover;
        vector<int> independent_set;
        for (int v = 0; v < n; v++) {
            if (part[v] == 0 && vis[v] || part[v] == 1 && !vis[v])
                independent_set.push_back(v);
            else
                vertex_cover.push_back(v);
        }
        return independent_set;
    }
};

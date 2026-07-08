vector<bool> used;
vector<int> sz;
vector<vector<int>> g;

void sizes(int v, int p) {
    sz[v] = 1;
    for (int u : g[v]) {
        if (u != p && !used[u])
            sizes(u, v), sz[v] += sz[u];
    }
}

int centroid (int v, int p, int n) {
    for (int u : g[v])
        if (u != p && !used[u] && sz[u] > n/2)
            return centroid(u, v, n);
    return v;
}

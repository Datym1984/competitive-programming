//g[v] - list of adjacent vertices as [u, i] where i - idex of edge
//find vertex-biconnected components
vector<vector<pair<int, int>>> g;
vector<int> depth;
vector<bool> used;
vector<int> st;
vector<vector<int>> comp;

int dfs(int v, int p) {
    int mn = depth[v];
    int deg = 0;
    for (auto [u, i] : g[v]) {
        if (depth[u] == -1) {
            deg++;
            depth[u] = depth[v] + 1;
            st.push_back(i);
            int d = dfs(u, i);
            if (d >= depth[v]) {
                comp.emplace_back();
                while (true) {
                    auto edge = st.back();
                    st.pop_back();
                    comp.back().push_back(edge);
                    if (edge == i) break;
                }
            }
            mn = min(mn, d);
        } else {
            if (i != p && depth[u] <= depth[v])
                st.push_back(i);
            mn = min(mn, depth[u]);
        }
    }
    return mn;
}

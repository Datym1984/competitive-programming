pair<int, int> find_tangent(vector<pt> &P, pt p) {
    int mx = 0, mn = 0;
    int n = P.size();

    auto sign = [&](int i, int j) {
        auto res = cross(P[j] - p, P[i] - p);
        if (res == 0)
            return 0;
        return res > 0 ? 1 : -1;
    };

    for (int i = (1 << 20); i >= 1; i >>= 1) {
        int c1 = (mx + i) % n, c2 = ((mx - i) % n + n) % n;
        if (sign(c1, mx) > 0)
            mx = c1;
        if (sign(c2, mx) > 0)
            mx = c2;

        c1 = (mn + i) % n, c2 = ((mn - i) % n + n) % n;
        if (sign(c1, mn) < 0)
            mn = c1;
        if (sign(c2, mn) < 0)
            mn = c2;
    }
    return mp(mx, mn);
}

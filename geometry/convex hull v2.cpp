vector<pt> convex_hull(vector<pt> P) {
    int n = P.size();
    assert(n > 0);
    pt p = P[0];
    for (int i = 1; i < n; i++)
        p = min(p, P[i]);

    sort(all(P), [&](auto a, auto b) {
        pt pa = a - p;
        pt pb = b - p;

        ll an = cross(pa, pb);
        if (an == 0)
            return len(pa) < len(pb);
        return an > 0;
    });

    vector<pt> ch;
    int sz = 0;
    for (auto i : P) {
        while ((sz >= 1 && i == ch.back()) || (sz >= 2 && cross(ch[sz - 1] - ch[sz - 2], i - ch[sz - 1]) <= 0)) {
            ch.pop_back();
            sz--;
        }
        ch.push_back(i);
        sz++;
    }
    return ch;
}

vector<pt> convex_hull(vector<pt> P) {
    assert(!P.empty());
    pt A = P[0], B = P[0];
    for (pt p : P) {
        A = min(A, p);
        B = max(B, p);
    }
    if (A == B)
        return {A};
    vector<pt> up, down;
    for (pt p : P) {
        if (cross(B - A, p - A) >= 0)
            up.push_back(p);
        if (cross(B - A, p - A) <= 0)
            down.push_back(p);
    }
    sort(all(up));
    sort(rall(down));
    vector<pt> st_up, st_down;
    for (pt p : up) {
        int sz = st_up.size();
        while ((sz >= 1 && st_up.back() == p) || (sz >= 2 && cross(st_up[sz - 1] - st_up[sz - 2], p - st_up[sz - 1]) >= 0))
            st_up.pop_back(), sz--;
        st_up.push_back(p);
    }
    for (pt p : down) {
        int sz = st_down.size();
        while ((sz >= 1 && st_down.back() == p) || (sz >= 2 && cross(st_down[sz - 1] - st_down[sz - 2], p - st_down[sz - 1]) >= 0))
            st_down.pop_back(), sz--;
        st_down.push_back(p);
    }
    st_up.pop_back();
    st_down.pop_back();
    for (pt p : st_down)
        st_up.push_back(p);
    reverse(all(st_up));
    return st_up;
}

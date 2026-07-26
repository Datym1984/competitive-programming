bool comp(pt p1, pt p2) {//compares two vectors on polar angle
    pair<int, int> pr1{0, 1}, pr2{1, 0};
    int hp1 = mp(p1.y, p1.x) < mp(0ll, 0ll);
    int hp2 = mp(p2.y, p2.x) < mp(0ll, 0ll);
    if (hp1 != hp2)
        return hp1 < hp2;
    return cross(p1, p2) > 0;
}

pair<int, int> find_tangent(vector<pt> P, pt p) {
    vector<pair<pt, int>> sides;
    for (int i = 0; i < (int) P.size(); i++)
        sides.emplace_back(P[(i + 1) % P.size()] - P[i], i);
    sort(all(sides), [](auto i, auto j){return comp(i.first, j.first);});

    vector<int> answer;
    int idx1 = lower_bound(all(sides), mp(p, -1), [](auto i, auto j){return comp(i.first, j.first);})
        - sides.begin();
    idx1 %= sides.size();
    int idx2 = lower_bound(all(sides), mp(pt(0, 0) - p, 1), [](auto i, auto j){return comp(i.first, j.first);})
        - sides.begin();
    idx2 %= sides.size();

    return mp(sides[idx1].second, sides[idx2].second);
}

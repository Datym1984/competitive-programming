vector<pt> minkovski(vector<pt> A, vector<pt> B) {
    vector<pt> vec;
    pt p1 = A[0], p2 = B[0];
    for (int i = 0; i < A.size(); i++) {
        vec.emplace_back(A[i] - A[(i + 1) % A.size()]);
        //p1 = max(p1, A[i]);
        if (A[i].y > p1.y || A[i].y == p1.y && A[i].x < p1.x)
            p1 = A[i];
    }
    for (int i = 0; i < B.size(); i++) {
        vec.emplace_back(B[i] - B[(i + 1) % B.size()]);
        //p2 = max(p2, B[i]);
        if (B[i].y > p2.y || B[i].y == p2.y && B[i].x < p2.x)
            p2 = B[i];
    }
    sort(all(vec), [](auto i, auto j) {
        ld an1 = atan2(cross({1, 0}, i), scalar({1, 0}, i));
        ld an2 = atan2(cross({1, 0}, j), scalar({1, 0}, j));
        return an1 < an2;
    });

    pt cur = p1 + p2;
    vector<pt> res{cur};
    for (int i = 0; i < vec.size(); i++) {
        cur = cur + vec[i];
        res.push_back(cur);
    }
    return res;
}

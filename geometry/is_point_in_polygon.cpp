bool in_polygon(vector<pt> &P, pt p) {
    int n = P.size();
    if (cross(P[1] - P[0], p - P[0]) < 0 || cross(P[0] - P[n - 1], p - P[n - 1]) < 0)// <= 0 - if pt cant be in polygon
        return false;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (cross(P[m] - P[0], p - P[0]) > 0)
            l = m;
        else
            r = m;
    }
    return cross(P[r] - P[l], p - P[l]) >= 0;// > 0 - if pt cant be in polygon
}

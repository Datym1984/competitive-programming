//find x and y such that ax+by=c, x->min and x >= 0
//if equation dont has solution solve_eq will return {-1, -1}
int expanded_gcd(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    int g = expanded_gcd(b % a, a, x, y);
    int x2 = x;
    x = y - x * (b / a);
    y = x2;
    return g;
}

pair<ll, ll> solve_eq(int a, int b, int c) {
    int x = 0, y = 0;
    int g = expanded_gcd(abs(a), abs(b), x, y);
    if (abs(c) % g != 0)
        return mp(0, 0);
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    x *= c / g;
    y *= c / g;
    return mp((ll) x * (c / g), (ll) y * (c / g));
}

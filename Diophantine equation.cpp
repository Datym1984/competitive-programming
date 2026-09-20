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
        return mp(-1, -1);
    if (a < 0) x = -x;
    if (b < 0) y = -y;
    x *= c / g;
    y *= c / g;

    if (x < 0) {
        int cnt = (abs(x) + b - 1) / b;
        return mp(x + (ll) cnt * b, y - (ll) cnt * a);
    }
    if (x >= 0) {
        int cnt = x / b;
        return mp(x - (ll) cnt * b, y + (ll) cnt * a);
    }
}

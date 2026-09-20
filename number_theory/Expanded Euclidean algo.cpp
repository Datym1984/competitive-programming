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

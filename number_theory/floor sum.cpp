//calcucate sum{0<=i<n} floor((k * i + b) / m)
int floor_sum(int k, int b, int m, int n) {
    int ans = 0;
    int tmp = k / m;
    ans += n * (n - 1) / 2 * tmp;
    ans += n * (b / m);
    k %= m;
    b %= m;
    if (k == 0)
        return ans;

    int ymax = (k * (n - 1) + b) / m;
    int res = (n - 1) * ymax;
    res -= floor_sum(m, m - b - 1, k, ymax);
    ans += res;
    return ans;
}

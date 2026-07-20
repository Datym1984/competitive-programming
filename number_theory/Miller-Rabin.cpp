ll power(ll a, ll b, ll mod) {
    if (b == 0)
        return 1;
    else if (b % 2 == 0) {
        ll res = power(a, b / 2, mod);
        return (__int128) res * res % mod;
    }
    else
        return (__int128) a * power(a, b - 1, mod) % mod;
}

bool is_prime(ll n) {
    if (n == 1) return false;
    ll s = (n - 1) & -(n - 1);
    ll d = (n - 1) / s;
    for (ll a : {2, 7, 61, 2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        a %= n;
        if (a == 0) continue;
        if (gcd(a, n) != 1)
            return false;
        if (power(a, d, n) == 1) continue;
        bool is_p = false;
        for (ll i = 1; i <= s; i <<= 1) {
            if (power(a, i * d, n) == n - 1) {
                is_p = true;
                break;
            }
        }
        if (!is_p)
            return false;
    }
    return true;
}

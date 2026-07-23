void pollard(ll n, vector<ll> &fact) {
    assert(n >= 2);
    if (n <= 100) {
        int i = 2;
        while (i * i <= n) {
            while (n % i == 0) {
                fact.push_back(i);
                n /= i;
            }
            i++;
        }
        if (n != 1)
            fact.push_back(n);
        return;
    }
    if (is_prime(n)) {
        fact.push_back(n);
        return;
    }

    auto f = [n](ll x)->ll {
        return ((__int128) (x + 1) * (x + 1)) % n;
    };

    while (true) {
        ll x = gen() % (n - 1) + 1;
        ll y = f(x);
        ll g = gcd(abs(x - y), n);
        int it = 0;
        while ((g <= 1 || g == n) && it < min<ll>(1e3, n + 5)) {
            x = f(x);
            y = f(f(y));
            g = gcd(abs(x - y), n);
            ++it;
        }
        if (g <= 1 || g == n) continue;
        pollard(g, fact);
        pollard(n / g, fact);
        break;
    }
}

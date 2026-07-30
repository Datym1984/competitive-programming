int power(int a, int b, const int mod) {
    int ans = 1;
    while (b) {
        if (b & 1)
            ans = (ll) ans * a % mod;
        a = (ll) a * a % mod;
        b >>= 1;
    }
    return ans;
}

void fft(vector<int> &A, const int mod) {
    int n = A.size();
    vector<int> rev(n);
    for (int i = 1; i < n; i++)
        rev[i] = (i & 1) * (n / 2) + rev[i / 2] / 2;
    for (int i = 0; i < n; i++) {
        if (i < rev[i])
            swap(A[i], A[rev[i]]);
    }
    const int g = 3;
    for (int len = 2; len <= n; len <<= 1) {
        int w1 = power(g, (mod - 1) / len, mod);
        for (int st = 0; st < n; st += len) {
            int wi = 1;
            for (int i = st; i < st + len / 2; i++) {
                int l = A[i], r = A[i + len / 2];
                A[i] = (l + (ll) r * wi) % mod;
                A[i + len / 2] = (l + (ll) (mod - wi) * r) % mod;
                wi = (ll) wi * w1 % mod;
            }
        }
    }
}

vector<int> mult(vector<int> A, vector<int> B) {
    int n = max(A.size(), B.size());
    while ((n & -n) != n) n += n & -n;
    n <<= 1;
    A.resize(n);
    B.resize(n);
    const int mod = (1 << 23) * 119 + 1;
    fft(A, mod);
    fft(B, mod);
    vector<int> C(n);
    for (int i = 0; i < n; i++)
        C[i] = (ll) A[i] * B[i] % mod;
    fft(C, mod);
    int rev_n = power(n, mod - 2, mod);
    for (int i = 0; i < n; i++)
        C[i] = (ll) C[i] * rev_n % mod;
    reverse(C.begin() + 1, C.end());
    return C;
}

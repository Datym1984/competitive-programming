//sample: s = aaba
//      : A = 1121 - odd palindrome
//      : B = 0100 - even palindrome
void manaker(const string &s) {
    int n = s.size();
    vector<int> A(n);
    int l = -1, r = -1;
    for (int i = 0; i < n; i++) {
        if (i <= r)
            A[i] = min(A[l + r - i], r - i + 1);
        while (i - A[i] >= 0 && i + A[i] < n && s[i - A[i]] == s[i + A[i]])
            A[i]++;
        if (i + A[i] - 1 > r) {
            l = i - A[i] + 1;
            r = i + A[i] - 1;
        }
    }
    vector<int> B(n);
    l = -1, r = -1;
    for (int i = 0; i < n; i++) {
        if (i <= r)
            B[i] = min(B[l + r - i + 1], r - i + 1);
        while (i - B[i] - 1 >= 0 && i + B[i] < n && s[i - B[i] - 1] == s[i + B[i]])
            B[i]++;
        if (i + B[i] - 1 > r) {
            l = i - B[i];
            r = i + B[i] - 1;
        }
    }
}

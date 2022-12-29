// binary numeral system where two successive values differ in only one bit
// get n-th gray code
int g(int n) {
    return n ^ (n >> 1);
}
int rev_g(int g) {
    int n = 0;
    for (; g; g >>= 1) n ^= g;
    return n;
}
// calculate (a*b)%mod
// Particularly useful when a, b, m all are large like 1e18
const int mod = (int)1e9 + 7;
long long RussianPeasantMultiplication(long long a, long long b) {
	long long ret = 0;
	while (b) {
		if (b & 1) {
			ret += a;
			if (ret >= mod) ret -= mod;
		}
		a = (a << 1);
		if (a >= mod) a -= mod;
		b >>= 1;
	}
	return ret;
}
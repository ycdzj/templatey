int extend_gcd(int a, int b, int &x, int &y) {
	int ans;
	if(b == 0) x = 1, y = 0, ans = a;
	else {
		ans = extend_gcd(b, a % b, y, x);
		y -= (a / b) * x;
	}
	return ans;
}
#include <cstdio>
#include <cmath>
template <typename T>
bool nxtInt(T &res) {
	char c;
	bool negative = false;
	while(c=getchar(), c!='-' && !('0'<=c && c<='9'))
		if(c == EOF) return false;
	if(c == '-') negative = true, c = getchar();
	res = 0;
	while('0'<=c && c<='9') res *= 10, res += c - '0', c = getchar();
	if(negative) res *= -1;
	return true;
}

template <typename T>
void prtInt(T x) {
	if(x < 0) putchar('-'), x *= -1;
	if(x > 9) prtInt(x / 10);
	putchar(x % 10 + '0');
}

template <typename T>
bool nxtNum(T &res) {
	char c;
	bool negative = false;
	while(c=getchar(), c!='.' && c!='-' && !('0'<=c && c<='9'))
		if(c == EOF) return false;
	if(c == '-') negative = true, c = getchar();
	res = 0;
	long long cnt = 0;
	while(c == '.' || ('0'<=c && c<='9')) {
		cnt *= 10;
		if(c == '.') cnt = 1;
		else res *= 10, res += c - '0';
		c = getchar();
	}
	if(negative) res *= -1;
	if(cnt > 0) res *= 1.0/cnt;
	return true;
}

template <typename T>
void prtNum(T x, long precision) {
	if(x < 0) putchar('-'), x *= -1;
	long long flr = floor(x);
	prtInt(flr);
	x -= flr;
	x *= pow(10, precision);
	flr = round(x);
	putchar('.');
	long long cnt = 0, t = 1;
	while(flr >= t) cnt++, t *= 10;
	for(long i=0; i<precision-cnt; i++) putchar('0');
	prtInt(flr);
}
bool nxtChar(char &c) {
	do {
		c = getchar();
	} while(c == ' ' || c == '\n');
	return c != EOF;
}
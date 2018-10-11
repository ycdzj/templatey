const double eps = 1e-8;
const double PI = acos(-1);
int dcmp(double x) {
	if(fabs(x) <= eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Point {
	double x, y;
};
Point operator - (Point a, Point b) { return {a.x - b.x, a.y - b.y}; }
Point operator + (Point a, Point b) { return {a.x + b.x, a.y + b.y}; }
Point operator * (double c, Point p) { return {c * p.x, c * p.y}; }
Point operator / (Point p, double c) { return {p.x / c, p.y / c}; }
double sqr(double x) { return x * x; }
double len(Point a) { return sqrt(sqr(a.x) + sqr(a.y)); }
double det(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double ang(Point a, Point b) { return acos(dot(a, b) / len(a) / len(b)); }
Point rotate(Point p, double A) {//逆时针旋转
	double tx = p.x, ty = p.y;
	return {tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A)};
}


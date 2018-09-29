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
double sqr(double x) { return x * x; }
double det(Point a, Point b) { return a.x * b.y - a.y * b.x; }
double dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
double len(Point a) { return sqrt(sqr(a.x) + sqr(a.y)); }
double ang(Point a, Point b) { return acos(dot(a, b) / len(a) / len(b)); }
Point rotate(Point p, double A) {
	double tx = p.x, ty = p.y;
	return {tx * cos(A) - ty * sin(A), tx * sin(A) + ty * cos(A)};
}


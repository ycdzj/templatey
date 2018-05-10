const double eps = 1e-10;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	return x < 0 ? -1 : 1;
}
struct Vector {
	double x, y;
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	bool operator == (Vector a) {
		return dcmp(x - a.x) == 0 && dcmp(y - a.y) == 0;
	}
	Vector operator + (Vector a) {
		return (Vector){x + a.x, y + a.y};
	}
	Vector operator - (Vector a) {
		return (Vector){x - a.x, y - a.y};
	}
	Vector operator * (double p) {
		return (Vector){x * p, y * p};
	}
	Vector operator / (double p) {
		return (Vector){x / p, y / p};
	}
};
double dot(Vector a, Vector b) {
	return a.x * b.x + a.y * b.y;
}
double cross(Vector a, Vector b) {
	return a.x * b.y - a.y * b.x;
}
Vector rotate(Vector a, double rad) {
	return (Vector){a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad)};
}
double angle(Vector v) {//计算向量极角
	return atan2(v.y, v.x);
}
double length(Vector a) {
	return sqrt(dot(a, a));
}
Vector normal(Vector a) {
	double l = length(a);
	return (Vector){a.x / l, a.y / l};
}
typedef Vector Point;
double dis_to_line(Point p, Point a, Point b) {
	Vector v1 = b - a, v2 = p - a;
	return fabs(cross(v1, v2)) / length(v1);
}
Point line_projection(Point p, Point a, Point b) {
	Vector v = b - a;
	return a + v * (dot(v, p - a) / dot(v, v));
}
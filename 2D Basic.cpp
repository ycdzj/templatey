int dcmp(double x) {
	const double eps = 1e-10;
	if(fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}
struct Vector {
	double x, y;
	Vector(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}

	Vector operator+ (const Vector &a) const {
		return Vector(x + a.x, y + a.y);
	}
	Vector operator- (const Vector &a) const {
		return Vector(x - a.x, y - a.y);
	}
	Vector operator* (double p) const {
		return Vector(x * p, y * p);
	}
	Vector operator/ (double p) const {
		return Vector(x / p, y / p);
	}
	bool operator== (const Vector &a) const {
		return dcmp(x - a.x) == 0 && dcmp(y - a.y) == 0;
	}
	double length() const {
		return sqrt(dmul(*this, *this));
	}
	
	friend double dmul(const Vector &a, const Vector &b) {
		return a.x * b.x + a.y * b.y;
	}
	friend double cmul(const Vector &a, const Vector &b) {
		return a.x * b.y - a.y * b.x;
	}
	friend double angle(const Vector &a, const Vector &b) {
		return acos(dmul(a, b) / a.length() / b.length());
	}
	friend Vector rotate(const Vector &a, double rad) {
		return Vector(a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad));
	}
	friend Vector normal(const Vector &a) {
		double l = a.length();
		return Vector(a.x / l, a.y / l);
	}	
};
typedef Vector Point;
struct Segment {
	Point a, b;
	Segment(const Point &a_, const Point &b_) : a(a_), b(b_) {}
};
struct Line {
	Point p;
	Vector v; //p + tv
	Line(const Point &p_, const Vector &v_) : p(p_), v(v_) {}
	Line(const Segment &sg) : Line(sg.a, sg.b - sg.a) {}
};


double disToSegment(const Segment &sg, const Point &p) {
	if(sg.a == sg.b) return (sg.a - p).length();
	Vector AB = sg.b - sg.a, AP = p - sg.a, BP = p - sg.b;
	if(dcmp(dmul(AB, AP)) < 0) return AP.length();
	if(dcmp(dmul(AB, BP)) > 0) return BP.length();
	return cmul(AB, AP) / AB.length();
}
bool onSegment(const Segment &sg, const Point &p) {
	Vector AP = p - sg.a, BP = p - sg.b;
	return dcmp(cmul(AP, BP)) == 0 && dcmp(dmul(AP, BP)) < 0;
}
Point getLineIntersection(const Line &l1, const Line &l2) {
	Vector u = l1.p - l2.p;
	double t1 = cmul(l2.v, u) / cmul(l1.v, l2.v);
	//double t2 = cmul(l1.v, u) / cmul(l1,v, l2.v);
	return l1.p + l1.v * t1;
}
double disToLine(const Point &a, const Point &b, const Point &p) {
	Vector BA = a - b;
	return cmul(BA, p - b) / BA.length();
}
Point getLineProjection(const Line &l, const Point &p) {
	Vector AP = p - l.p;
	double t = dmul(l.v, AP) / dmul(l.v, l.v);
	return l.p + l.v * t;
}

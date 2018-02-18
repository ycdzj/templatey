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
	if(dcmp(dot(AB, AP)) < 0) return AP.length();
	if(dcmp(dot(AB, BP)) > 0) return BP.length();
	return cross(AB, AP) / AB.length();
}
bool onSegment(const Segment &sg, const Point &p) {
	Vector AP = p - sg.a, BP = p - sg.b;
	return dcmp(cross(AP, BP)) == 0 && dcmp(dot(AP, BP)) < 0;
}
Point getLineIntersection(const Line &l1, const Line &l2) {
	Vector u = l1.p - l2.p;
	double t1 = cross(l2.v, u) / cross(l1.v, l2.v);
	//double t2 = cross(l1.v, u) / cross(l1,v, l2.v);
	return l1.p + l1.v * t1;
}
double disToLine(const Point &a, const Point &b, const Point &p) {
	Vector BA = a - b;
	return cross(BA, p - b) / BA.length();
}
Point getLineProjection(const Line &l, const Point &p) {
	Vector AP = p - l.p;
	double t = dot(l.v, AP) / dot(l.v, l.v);
	return l.p + l.v * t;
}
	friend double angle(const Vector &a, const Vector &b) {
		return acos(dot(a, b) / a.length() / b.length());
	}

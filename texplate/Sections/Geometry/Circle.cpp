struct Circle {
	Point c;
	double r;
	Point point(double rad) {//通过圆心角求坐标
		return (Point){c.x + r * cos(rad), c.y + r * sin(rad)};
	}
};
int CircleIntersection(Circle c1, Circle c2, Point res[]) {
	double d = length(c1.c - c2.c);
	if(dcmp(d) == 0) {
		if(dcmp(c1.r - c2.r) == 0) return -1;//两圆重合
		return 0;
	}
	if(dcmp(c1.r + c2.r - d) < 0) return 0;
	if(dcmp(fabs(c1.r - c2.r) - d) > 0) return 0;

	double a = angle(c2.c - c1.c);
	double da = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));

	Point p1 = c1.point(a - da), p2 = c1.point(a + da);

	res[0] = p1;
	if(p1 == p2) return 1;
	res[1] = p2;
	return 2;
}

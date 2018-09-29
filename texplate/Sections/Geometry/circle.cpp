int circle_cross_seg(Point a, Point b, Point o, double r, Point ret[]) {//返回交点个数
	double x0 = o.x, y0 = o.y;
	double x1 = a.x, y1 = a.y;
	double x2 = b.x, y2 = b.y;
	double dx = x2 - x1, dy = y2 - y1;
	double A = dx * dx + dy * dy;
	double B = 2 * dx * (x1 - x0) + 2 * dy * (y1 - y0);
	double C = sqr(x1 - x0) + sqr(y1 - y0) - sqr(r);
	double delta = B * B - 4 * A * C;
	int num = 0;
	if(dcmp(delta) >= 0) {
		double t1 = (-B - sqrt(delta)) / (2 * A);
		double t2 = (-B + sqrt(delta)) / (2 * A);
		if(dcmp(t1 - 1) <= 0 && dcmp(t1) >= 0) ret[num++] = {x1 + t1 * dx, y1 + t1 * dy};
		if(dcmp(t2 - 1) <= 0 && dcmp(t2) >= 0) ret[num++] = {x1 + t2 * dx, y1 + t2 * dy};
	}
	return num;
}
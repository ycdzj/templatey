Point line_intersection(Point p, Point v, Point q, Point w) {//v, w是向量
	Point u = p - q;
	double t = det(w, u) / det(v, w);
	return p + t * v;
}
double dis_to_line(Point p, Point a, Point b) {
	Point v1 = b - a, v2 = p - a;
	return fabs(det(v1, v2)) / len(v1);
}
double dis_to_seg(Point p, Point a, Point b) {
	if(a == b) return len(p - a);
	Point v1 = b - a, v2 = p - a, v3 = p - b;
	if(dcmp(dot(v1, v2)) < 0) return len(v2);
	else if(dcmp(dot(v1, v3)) > 0) return len(v3);
	else return fabs(det(v1, v2)) / len(v1);
}
Point line_projection(Point p, Point a, Point b) {
	Point v = b - a;
	return a + (dot(v, p - a) / dot(v, v)) * v;
}
bool on_seg(Point p, Point a, Point b) {
	Point v1 = a - p, v2 = b - p;
	return dcmp(det(v1, v2)) == 0 && dcmp(dot(v1, v2)) <= 0;//包含端点
	//return dcmp(det(v1, v2)) == 0 && dcmp(dot(v1, v2)) < 0;//不包含端点
}
bool seg_proper_intersect(Point a1, Point a2, Point b1, Point b2) {
	Point va = a2 - a1, vb = b2 - b1;
	double c1 = det(va, b1 - a1);
	double c2 = det(va, b2 - a1);
	double c3 = det(vb, a1 - b1);
	double c4 = det(vb, a2 - b1);
	return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
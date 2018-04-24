double eps = 1e-10;
int dcmp(double x) {
	if(fabs(x) < eps) return 0;
	else return x < 0 ? -1 : 1;
}
struct Vector {
	double x, y;
    bool operator== (Vector a) {
		return dcmp(x - a.x) == 0 && dcmp(y - a.y) == 0;
	}
	Vector operator+ (Vector a) {
		return (Vector){x + a.x, y + a.y};
	}
	Vector operator- (Vector a) {
		return (Vector){x - a.x, y - a.y};
	}
	Vector operator* (double p) {
		return (Vector){x * p, y * p};
	}
	Vector operator/ (double p) {
		return (Vector){x / p, y / p};
	}
	friend double dot(Vector a, Vector b) {
		return a.x * b.x + a.y * b.y;
	}
	friend double cross(Vector a, Vector b) {
		return a.x * b.y - a.y * b.x;
	}
	friend Vector rotate(Vector a, double rad) {
		return (Vector){a.x * cos(rad) - a.y * sin(rad), a.x * sin(rad) + a.y * cos(rad)};
	}
    friend double length(Vector a) {
		return sqrt(dot(a, a));
	}
	friend Vector normal(Vector a) {
		double l = a.length();
		return (Vector){a.x / l, a.y / l};
	}
	friend double angle(Vector v) {//计算向量极角
        return atan2(v.y, v.x);
    }
};
typedef Vector Point;

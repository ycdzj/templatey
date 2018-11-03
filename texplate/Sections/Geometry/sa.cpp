double rand01() { return (rand() % 10001) / 10000.0; }
Point anneal(Point cur) {
	const double T = 100000, STEP = 0.98;//while大约会执行1500次
	double t = T;
	double cur_val = f(cur);
	while(t > EPS) {
		double tmp = 2 * PI * rand01();
		Point nxt = {cur.x + t * sin(tmp), cur.y + t * cos(tmp)};

		double nxt_val = f(nxt);
		double dif = cur_val - nxt_val;//最小值
		if(dif >= 0 || exp(dif / t) >= rand01()) cur = nxt, cur_val = nxt_val;
		t *= STEP;
	}
	for(int cnt = 0; cnt < 1000; cnt++) {
		t = 0.01 * rand01();
		double tmp = 2 * PI * rand01();
		Point nxt = {cur.x + t * sin(tmp), cur.y + t * cos(tmp)};

		double nxt_val = f(nxt);
		if(nxt_val < cur_val) cur = nxt, cur_val = nxt_val;//最小值
	}
	return cur;
}
struct treapNode {
	T val;
	int s, p;
	treapNode* c[2];
} buf[MAXN];
int cnt_buf;
void rotate(treapNode* &root, int d) {
	treapNode *y = root->c[d];

	y->s = root->s;
	root->s = size(root->c[d ^ 1]) + size(y->c[d ^ 1]) + 1;

	root->c[d] = y->c[d ^ 1], y->c[d ^ 1] = root, root = y;
}

int size(treapNode* root) { return root == nullptr ? 0 : root->s; }

void insert(treapNode* &root, const T &val) {
	if(root == nullptr) {
		root = &buf[cnt_buf++];
		root->val = val;
		root->s = 1;
		root->p = rand();
		root->c[0] = root->c[1] = nullptr;
	}
	else {
		int d = val < root->val ? 0 : 1;
		insert(root->c[d], val);
		++root->s;
		if(root->c[d]->p < root->p) rotate(root, d);
	}
}

bool remove(treapNode* &root, const T &val) {
	if(root == nullptr) return false;
	if(root->val == val) {
		for(int i = 0; i < 2; i++) if(root->c[i] == nullptr) {
			root = root->c[i ^ 1];
			return true;
		}
		int d = root->c[0]->p < root->c[1]->p ? 0 : 1;
		rotate(root, d);
		remove(root->c[d ^ 1], val);
		--root->s;
		return true;
	}
	else if(remove(root->c[val < root->val ? 0 : 1], val)) {
		--root->s;
		return true;
	}
	return false;
}
T& select(treapNode* root, int k) {
	while(root != nullptr) {
		int cur = size(root->c[0]);
		if(cur == k) return root->val;
		root = root->c[k < cur ? 0 : 1];
		if(k > cur) k -= ++cur;
	}
}
int lower_bound(treapNode* root, T val) {
	int ans = 0;
	while(root != nullptr) {
		if(root->val >= val) root = root->c[0];
		else {
			ans += size(root->c[0]) + 1;
			root = root->c[1];
		}
	}
	return ans;
}
int upper_bound(treapNode* root, T val) {
	int ans = 0;
	while(root != nullptr) {
		if(root->val > val) root = root->c[0];
		else {
			ans += size(root->c[0]) + 1;
			root = root->c[1];
		}
	}
	return ans;
}
bool contain(treapNode* root, const T &val) {
	while(root != nullptr && root->val != val) {
		if(val < root->val) root = root->c[0];
		else root = root->c[1];
	}
	return root != nullptr;
}

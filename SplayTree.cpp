#include <memory>
#include <stack>
#include <cstdio>
#include <cstring>

template<typename T>
struct splayNode {
	T val;
	int s;
	splayNode<T>* c[2];
	splayNode(const T &val, splayNode<T>* l, splayNode<T>* r):
			val(val), c({l, r}) {}

	static std::allocator<splayNode<T>> alloc;
	static void rotate(splayNode<T>* &root, int d) {
		auto y = root->c[d];

		y->s = root->s;
		root->s = 1 + size(root->c[d ^ 1]) + size(y->c[d ^ 1]);

		root->c[d] = y->c[d ^ 1], y->c[d ^ 1] = root, root = y;
	}
	static void splay_kth(splayNode<T>* &root, int k) {
		if(root == nullptr) return;
		splayNode<T> *p[2], **p_[2] = { &p[0], &p[1] };
		std::stack<splayNode<T>*> s[2];
		while(true) {
			int cur = size(root->c[0]);
			int d = k < cur ? 0 : 1, d_ = k < cur ? 1 : -1;
			if(k == cur || root->c[d] == nullptr) break;
			if(d_ * k < d_ * size(root->c[d]->c[d]) && root->c[d]->c[d] != nullptr) rotate(root, d);
			*p_[d ^ 1] = root, p_[d ^ 1] = &root->c[d], s[d ^ 1].push(root);
			root = root->c[d];
			if(d == 1) k -= ++cur;
		}
		for(int i = 0; i < 2; i++) {
			*p_[i] = root->c[i], root->c[i] = p[i];
			while(!s[i].empty()) s[i].top()->s = 1 + size(s[i].top()->c[0]) + size(s[i].top()->c[1]), s[i].pop();
		}
		root->s = 1 + size(root->c[0]) + size(root->c[1]);
	}

	friend int size(splayNode<T>* root) { return root == nullptr ? 0 : root->s; }
	friend void build(splayNode<T>* &root, T* a, int l, int r) {
		if(l > r) { root = nullptr; return; }
		int mid = (l + r) / 2;
		root = alloc.allocate(1);
		alloc.construct(root, a[mid], build(root->c[0], a, l, mid - 1), build(root->c[1], a, mid + 1, r));
		root->s = 1 + size(root->c[0]) + size(root->c[1]);
	}
	friend splayNode<T>* split(splayNode<T>* &root, int k) {
		if(root == nullptr) return nullptr;
		splay_kth(root, k);
		auto res = root->c[1];
		root->c[1] = nullptr;
		return res;
	}
	friend void attach(splayNode<T>* &left, splayNode<T>* right) {
		if(left == nullptr) left = right;
		else splay_kth(left, size(left) - 1), left->c[1] = right;
	}
	friend void clear(splayNode<T>* &root) {
		std::stack<splayNode<T>*> s;
		if(root != nullptr) s.push(root);
		while(!s.empty()) {
			auto x = s.top(); s.pop();
			if(x->c[0] != nullptr) s.push(x->c[0]);
			if(x->c[1] != nullptr) s.push(x->c[1]);
			alloc.destroy(x), alloc.deallocate(x, 1);
		}
		root = nullptr;
	}
};
template<typename T>
std::allocator<splayNode<T>> splayNode<T>::alloc;


void print(splayNode<char> *a) {
	if(a != nullptr) {
		print(a->c[0]);
		putchar(a->val);
		print(a->c[1]);
	}
}
splayNode<char>* a;
int main() {
	char str[] = "abcde12345";
	build(a, str, 0, (int)strlen(str) - 1);
	auto b = split(a, 1);
	print(a);
	return 0;
}

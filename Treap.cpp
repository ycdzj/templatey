#include <memory>
#include <algorithm>

template<typename T>
class Treap {
	struct Node {
		T val;
		int s, p;
		Node* c[2];

		Node(const T &val) : val(val), s(1), p(rand()) {
			c[0] = c[1] = nullptr;
		}
	};
	std::allocator<Node> alloc;
	Node* root;

	inline int sizeOfNode(Node *root) { return root == nullptr ? 0 : root->s; }
	inline void rotate(Node *&root, int d) {
		Node *y = root->c[d];

		y->s = root->s;
		root->s = sizeOfNode(root->c[d ^ 1]) + sizeOfNode(y->c[d ^ 1]) + 1;

		root->c[d] = y->c[d ^ 1];
		y->c[d ^ 1] = root;
		root = y;
	}
	void remove_(Node *&root) {
		for(int i = 0; i < 2; i++) if(root->c[i] == nullptr) {
			Node *y = root;
			root = root->c[i ^ 1];
			alloc.destroy(y), alloc.deallocate(y, 1);
			return;
		}
		int d = root->c[0]->p < root->c[1]->p ? 0 : 1;
		rotate(root, d), --root->s, remove_(root->c[d ^ 1]);
	}
	bool remove_(const T &val, Node *&root) {
		if(root == nullptr) return false;
		if(root->val == val) return remove_(root), true;
		if(remove_(val, root->c[val < root->val ? 0 : 1])) return --root->s, true;
		return false;
	}
	void clear(Node *r) {
		if(r != nullptr) {
			clear(r->c[0]), clear(r->c[1]);
			alloc.destroy(r), alloc.deallocate(r, 1);
		}
	}
	void insert(const T &val, Node *&root) {
		if(root == nullptr) root = alloc.allocate(1), alloc.construct(root, val);
		else {
			int d = val < root->val ? 0 : 1;
			insert(val, root->c[d]);
			++root->s;
			if(root->c[d]->p > root->p) rotate(root, d);
		}
	}
public:
	Treap() { init(); }
	~Treap() { clear(root); }
	void init() { clear(root), root = nullptr; }

	int size() { return sizeOfNode(root); }
	void insert(const T &val) { insert(val, root); }
	void remove(const T &val) {
		remove_(val, root);
	}
	T& select(int k) {
		Node *root = this->root;
		while(root != nullptr) {
			int cur = sizeOfNode(root->c[0]);
			if(k == cur) return root->val;
			root = root->c[k < cur ? 0 : 1];
			if(k > cur) k -= ++cur;
		}
	}
	int rank(const T &val) {
		int pre = 0;
		Node *root = this->root;
		while(root != nullptr && !(val == root->val)) {
			int d = val < root->val ? 0 : 1;
			if(d == 1) pre += sizeOfNode(root->c[0]) + 1;
			root = root->c[d];
		}
		if(root != nullptr) pre += sizeof(root->c[0]);
		return pre;
	}
};

int main() {
	int n = 2e5;
	Treap<int> trep;
	for(int i = 0; i < n; i++) trep.insert(rand());
	for(int i = 0; i < n; i++) {
		int j = ((rand() % trep.size()) + trep.size()) % trep.size();
		trep.remove(trep.select(j));
	}
	return 0;
}

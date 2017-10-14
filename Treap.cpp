#include <memory>

template<typename T>
struct treapNode {
	T val;
	int s, p;
	treapNode<T>* c[2];
	treapNode(const T &val): val(val) {
		s = 1, p = rand(), c[0] = c[1] = nullptr;
	}

	static std::allocator<treapNode<T>> alloc;
	static inline void rotate(treapNode<T>* &root, int d) {
		treapNode<T> *y = root->c[d];

		y->s = root->s;
		root->s = size(root->c[d ^ 1]) + size(y->c[d ^ 1]) + 1;

		root->c[d] = y->c[d ^ 1], y->c[d ^ 1] = root, root = y;
	}

	friend int size(treapNode<T>* root) { return root == nullptr ? 0 : root->s; }
	friend void clear(treapNode<T>* &root) {
		if(root != nullptr) {
			clear(root->c[0]), clear(root->c[1]);
			alloc.destroy(root), alloc.deallocate(root, 1);
			root = nullptr;
		}
	}
	friend void insert(treapNode<T>* &root, const T &val) {
		if(root == nullptr) root = alloc.allocate(1), alloc.construct(root, val);
		else {
			int d = val < root->val ? 0 : 1;
			insert(root->c[d], val), ++root->s;
			if(root->c[d]->p < root->p) rotate(root, d);
		}
	}
	friend bool remove(treapNode<T>* &root, const T &val) {
		if(root == nullptr) return false;
		if(root->val == val) {
			for(int i = 0; i < 2; i++) if(root->c[i] == nullptr) {
					auto y = root;
					root = root->c[i ^ 1];
					alloc.destroy(y), alloc.deallocate(y, 1);
					return true;
				}
			int d = root->c[0]->p < root->c[1]->p ? 0 : 1;
			rotate(root, d), remove(root->c[d ^ 1], val), --root->s;
			return true;
		}
		else if(remove(root->c[val < root->val ? 0 : 1], val)) return --root->s, true;
		return false;
	}
	friend T& select(treapNode<T>* root, int k) {
		while(root != nullptr) {
			int cur = size(root->c[0]);
			if(cur == k) return root->val;
			root = root->c[k < cur ? 0 : 1];
			if(k > cur) k -= ++cur;
		}
	}
	friend int lower_bound(treapNode<T>* root, const T &val) {
		if(root == nullptr) return 0;
		if(val < root->val || val == root->val) return lower_bound(root->c[0], val);
		return size(root->c[0]) + 1 + lower_bound(root->c[1], val);
	}
	friend bool contain(treapNode<T>* root, const T &val) {
		return root != nullptr && (root->val == val || contain(root->c[val < root->val ? 0 : 1], val));
	}
};
template<typename T>
std::allocator<treapNode<T>> treapNode<T>::alloc;
#include <memory>
#include <stack>
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

template<typename T>
class rank_SplayTree {
	struct Node {
		T val;
		int size;
		Node *left, *right;

		Node(const T &val): val(val), size(1), left(nullptr), right(nullptr) {}
	};
	std::allocator<Node> alloc;
	Node *root;

	inline int Size_of_node(Node *node) {
		return node == nullptr ? 0 : node->size;
	}
	void Splay(const T &val) {
		Node *l, *r;
		Node **l_ = &l, **r_ = &r;
		std::stack<Node*> sl, sr;
		while(!(root->val == val)) {
			if(val < root->val) {
				if(root->left == nullptr) break;
				if(val < root->left->val && root->left->left != nullptr) {
					//right rotate
					Node *y = root->left;
					root->left = y->right, y->right = root;
					y->size = root->size, root->size -= y->left->size + 1;
					root = y;
				}
				//move to left
				*r_ = root, r_ = &root->left;
				sr.push(root);
				root->size -= root->left->size;
				root = root->left;
			}
			else {
				if(root->right == nullptr) break;
				if(root->right->val < val && root->right->right != nullptr) {
					//left rotate
					Node *y = root->right;
					root->right = y->left, y->left = root;
					y->size = root->size, root->size -= y->right->size + 1;
					root = y;
				}
				//move to right
				*l_ = root, l_ = &root->right;
				sl.push(root);
				root->size -= root->right->size;
				root = root->right;
			}
		}
		*l_ = root->left, *r_ = root->right;
		root->left = l, root->right = r;
		while(!sl.empty()) sl.top()->size += Size_of_node(sl.top()->right), sl.pop();
		while(!sr.empty()) sr.top()->size += Size_of_node(sr.top()->left), sr.pop();
		root->size = Size_of_node(root->left) + Size_of_node(root->right) + 1;
	}
	void Splay_kth(int k) {// start from 0
		Node *l, *r;
		Node **l_ = &l, **r_ = &r;
		std::stack<Node*> sl, sr;
		int cur = Size_of_node(root->left);
		while(cur != k) {
			if(k < cur) {
				if(root->left == nullptr) break;
				int cur_left = cur - (1 + Size_of_node(root->left->right));
				if(k < cur_left && root->left->left != nullptr) {
					//right rotate
					Node *y = root->left;
					cur -= 1 + Size_of_node(y->right);
					root->left = y->right, y->right = root;
					y->size = root->size, root->size -= y->left->size + 1;
					root = y;
				}
				//move to left
				cur -= 1 + Size_of_node(root->left->right);
				*r_ = root, r_ = &root->left;
				sr.push(root);
				root->size -= root->left->size;
				root = root->left;
			}
			else {
				if(root->right == nullptr) break;
				int cur_right = cur + 1 + Size_of_node(root->right->left);
				if(k > cur_right && root->right->right != nullptr) {
					//left rotate
					Node *y = root->right;
					cur += 1 + Size_of_node(y->left);
					root->right = y->left, y->left = root;
					y->size = root->size, root->size -= y->right->size + 1;
					root = y;
				}
				//move to right
				cur += 1 + Size_of_node(root->right->left);
				*l_ = root, l_ = &root->right;
				sl.push(root);
				root->size -= root->right->size;
				root = root->right;
			}
		}
		*l_ = root->left, *r_ = root->right;
		root->left = l, root->right = r;
		while(!sl.empty()) sl.top()->size += Size_of_node(sl.top()->right), sl.pop();
		while(!sr.empty()) sr.top()->size += Size_of_node(sr.top()->left), sr.pop();
		root->size = Size_of_node(root->left) + Size_of_node(root->right) + 1;
	}

public:
	rank_SplayTree() : root(nullptr) {}
	~rank_SplayTree() {
		if(root != nullptr) {
			std::stack<Node*> s;
			s.push(root);
			while(!s.empty()) {
				Node *t = s.top(); s.pop();
				if(t->left != nullptr) s.push(t->left);
				if(t->right != nullptr) s.push(t->right);
				alloc.destroy(t), alloc.deallocate(t, 1);
			}
		}
	}
	int Size() { return Size_of_node(root); }
	bool Has(const T &val) {
		return root != nullptr && (Splay(val), root->val == val);
	}
	T& Access(const T &val) {
		if(root != nullptr) return Splay(val), root->val;
	}
	T& Select(int k) {
		if(root != nullptr) return Splay_kth(k), root->val;
	}
	int Rank(const T &val) {
		if(root != nullptr) {
			Splay(val);
			return Size_of_node(root->left) + (root->val < val ? 1 : 0);
		}
	}
	void Insert(const T &val) {
		if(root == nullptr) {
			root = alloc.allocate(1);
			alloc.construct(root, val);
		}
		else {
			Splay(val);
			Node *x = root;
			root = alloc.allocate(1);
			alloc.construct(root, val);
			if(val < x->val)
				root->left = x->left, x->left = nullptr, root->right = x;
			else
				root->right = x->right, x->right = nullptr, root->left = x;
			x->size = Size_of_node(x->left) + Size_of_node(x->right) + 1;
			root->size = Size_of_node(root->left) + Size_of_node(root->right) + 1;
		}
	}
	void Delete(const T &val) {
		if(Has(val)) {
			Node *x = root;
			if(root->left == nullptr) root = root->right;
			else {
				root = root->left;
				Splay_kth(root->left->size);
				root->right = x->right;
			}
			alloc.destroy(x), alloc.deallocate(x, 1);
		}
	}
};
template<typename T>
class SplayTree {
	struct Node {
		T val;
		Node *left, *right;
		Node(const T &val) : val(val), left(nullptr), right(nullptr) {}
	};
	Node *root;
	std::allocator<Node> alloc;

	void Splay(const T &val) {
		Node *l, *r;
		Node **l_ = &l, **r_ = &r;
		while(!(root->val == val)) {
			if(val < root->val) {
				if(root->left == nullptr) break;
				if(val < root->left->val && root->left->left != nullptr) {
					//right rotate
					Node *y = root->left;
					root->left = y->right, y->right = root, root = y;
				}
				//move to left
				*r_ = root, r_ = &root->left, root = root->left;
			}
			else {
				if(root->right == nullptr) break;
				if(!(val < root->right->val) && root->right->right != nullptr) {
					//left rotate
					Node *y = root->right;
					root->right = y->left, y->left = root, root = y;
				}
				//move to right
				*l_ = root, l_ = &root->right, root = root->right;
			}
		}
		*l_ = root->left, *r_ = root->right;
		root->left = l, root->right = r;
	}
	void Splay_min() {
		Node *r;
		Node **r_ = &r;
		while(root->left != nullptr) {
			if(root->left->left != nullptr) {
				//right rotate
				Node *y = root->left;
				root->left = y->right, y->right = root, root = y;
			}
			//move to left
			*r_ = root, r_ = &root->left, root = root->left;
		}
		*r_ = root->right, root->right = r;
	}
	void Splay_max() {
		Node *l;
		Node **l_ = &l;
		while(root->right != nullptr) {
			if(root->right->right != nullptr) {
				//left rotate
				Node *y = root->right;
				root->right = y->left, y->left = root, root = y;
			}
			//move to right
			*l_ = root, l_ = &root->right, root = root->right;
		}
		*l_ = root->left, root->left = l;
	}

public:
	SplayTree() : root(nullptr) {}
	~SplayTree() {
		if(root != nullptr) {
			std::stack<Node*> s;
			s.push(root);
			while(!s.empty()) {
				Node *t = s.top(); s.pop();
				if(t->left != nullptr) s.push(t->left);
				if(t->right != nullptr) s.push(t->right);
				alloc.destroy(t), alloc.deallocate(t, 1);
			}
		}
	}
	T& Access(const T &val) {
		if(Has(val)) return root->val;
	}
	T& Min() {
		if(root != nullptr) return Splay_min(), root->val;
	}
	T& Max() {
		if(root != nullptr) return Splay_max(), root->val;
	}
	bool Has(const T &val) {
		return root != nullptr && (Splay(val), root->val == val);
	}
	void Insert(const T &val) {
		if(root == nullptr) root = alloc.allocate(1), alloc.construct(root, val);
		else if(!Has(val)) {
			Node *New = alloc.allocate(1);
			alloc.construct(New, val);
			if(val < root->val) New->left = root->left, New->right = root, root->left = nullptr;
			else New->right = root->right, New->left = root, root->right = nullptr;
			root = New;
		}
	}
	void Delete(const T &val) {
		if(Has(val)) {
			Node *x = root;
			if(x->left == nullptr) root = root->right;
			else {
				root = root->left;
				Splay_max();
				root->right = x->right;
			}
			alloc.destroy(x), alloc.deallocate(x, 1);
		}
	}
};
int main() {
	using namespace std;
	rank_SplayTree<int> spt;
	srand(1234);
	for(int i = 0; i < 1e7; i++) spt.Insert(rand());
/*	srand(9854022);
	vector<int> v;
	for(int i = 0; i < n; i++) {
		int t = rand() % m;
		rspt.Insert(t);
		v.push_back(t);
	}
	sort(v.begin(), v.end());
	while(true) {
		for(int i = 0; i < 1; i++) {
			int t = (rand() + n) % n;
			for(int j = 1; j <= 3; j++) rspt.Has(v[t] * j);
		}
		int t = (rand() + n) % n;
		if(rspt.Select(t) != v[t])
			break;
	}
	return 0;*/
}

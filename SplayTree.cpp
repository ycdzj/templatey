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
		Node* ch[2];

		Node(const T &val): val(val), size(1), ch({nullptr, nullptr}) {}
	};
	std::allocator<Node> alloc;
	Node *root;

	inline int Size_of_node(Node *node) {
		return node == nullptr ? 0 : node->size;
	}
	void Splay(const T &val) {
		Node* p[2];
		Node **p_[2] = { &p[0], &p[1] };
		std::stack<Node*> s[2];
		while(!(root->val == val)) {
			int d = val < root->val ? 0 : 1;
			if(root->ch[d] == nullptr) break;
			if(val < root->ch[d]->val && root->ch[d]->ch[d] != nullptr) {
				//rotate
				Node *y = root->ch[d];
				root->ch[d] = y->ch[d ^ 1], y->ch[d ^ 1] = root;
				y->size = root->size, root->size -= y->ch[d]->size + 1;
				root = y;
			}
			//move
			*p_[d ^ 1] = root, p_[d ^ 1] = &root->ch[d];
			s[d ^ 1].push(root);
			root->size -= root->ch[d]->size;
			root = root->ch[d];
		}
		root->size = 1;
		for(int i = 0; i < 2; i++) {
			*p_[i] = root->ch[i], root->ch[i] = p[i];
			while(!s[i].empty()) s[i].top()->size += Size_of_node(s[i].top()->ch[1]), s[i].pop();
			root->size += Size_of_node(root->ch[i]);
		}
	}
	void Splay_kth(int k) {
		Node* p[2];
		Node **p_[2] = { &p[0], &p[1] };
		std::stack<Node*> s[2];
		int cur = Size_of_node(root->ch[0]);
		while(cur != k) {
			int d = k < cur ? 0 : 1;
			int d_ = k < cur ? -1 : 1;
			if(root->ch[d] == nullptr) break;
			int cur_nxt = cur + d_ * (1 + Size_of_node(root->ch[d]->ch[d ^ 1]));
			if(k * d_ > cur_nxt * d_ && root->ch[d]->ch[d] != nullptr) {
				//rotate
				Node *y = root->ch[d];
				cur += d_ * (1 + Size_of_node(y->ch[d ^ 1]));
				root->ch[d] = y->ch[d ^ 1], y->ch[d ^ 1] = root;
				y->size = root->size, root->size -= Size_of_node(y->ch[d]) + 1;
				root = y;
			}
			//move
			cur += d_ * (1 + Size_of_node(root->ch[d]->ch[d ^ 1]));
			*p_[d ^ 1] = root, p_[d ^ 1] = &root->ch[d];
			s[d ^ 1].push(root);
			root->size -= root->ch[d]->size;
			root = root->ch[d];
		}
		root->size = 1;
		for(int i = 0; i < 2; i++) {
			*p_[i] = root->ch[i], root->ch[i] = p[i];
			while(!s[i].empty()) s[i].top()->size += Size_of_node(s[i].top()->ch[1]), s[i].pop();
			root->size += Size_of_node(root->ch[i]);
		}
	}

public:
	rank_SplayTree() : root(nullptr) {}
	~rank_SplayTree() { Clear(); }
	void Clear() {
		if(root != nullptr) {
			std::stack<Node*> s;
			s.push(root);
			while(!s.empty()) {
				Node *t = s.top(); s.pop();
				if(t->ch[0] != nullptr) s.push(t->ch[0]);
				if(t->ch[1] != nullptr) s.push(t->ch[1]);
				alloc.destroy(t), alloc.deallocate(t, 1);
			}
		}
		root = nullptr;
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
			return Size_of_node(root->ch[0]) + (root->val < val ? 1 : 0);
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
				root->ch[0] = x->ch[0], x->ch[0] = nullptr, root->ch[1] = x;
			else
				root->ch[1] = x->ch[1], x->ch[1] = nullptr, root->ch[0] = x;
			x->size = Size_of_node(x->ch[0]) + Size_of_node(x->ch[1]) + 1;
			root->size = Size_of_node(root->ch[0]) + Size_of_node(root->ch[1]) + 1;
		}
	}
	void Delete(const T &val) {
		if(Has(val)) {
			Node *x = root;
			if(root->ch[0] == nullptr) root = root->ch[1];
			else {
				root = root->ch[0];
				Splay_kth(x->size);
				root->ch[1] = x->ch[1];
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
	int n = 1e7;
	for(int i = 0; i < 1e7; i++) spt.Insert(rand());
	for(int i = 0; i < 1e7; i++) spt.Select((rand() + n)%n);
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

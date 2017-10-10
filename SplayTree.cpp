#include <memory>
template<typename T>
class rank_SplayTree {
	struct Node {
		T val;
		int size;
		Node *left, *right;
	};
	std::allocator<Node> alloc;
	Node *root;
	int n_node;

	void Repair_size(Node *cur, Node *last, bool d) {
		if(cur == last) return;
		if(d) Repair_size(cur->left, last, d), cur->size += cur->left->size;
		else Repair_size(cur->right, last, d), cur->size += cur->right->size;

	}
	inline int Size_of_node(Node *node) {
		return node == nullptr ? 0 : node->size;
	}
	void Splay(const T &val) {
		Node *l, *r;
		Node **l_ = &l, **r_ = &r;
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
				root->size -= root->left->size;
				root = root->left;
			}
			else {
				if(root->right == nullptr) break;
				if(!(val < root->right->val) && root->right->right != nullptr) {
					//left rotate
					Node *y = root->right;
					root->right = y->left, y->left = root;
					y->size = root->size, root->size -= y->right->size + 1;
					root = y;
				}
				//move to right
				*l_ = root, l_ = &root->right;
				root->size -= root->right->size;
				root = root->right;
			}
		}
		*l_ = root->left, *r_ = root->right;
		root->left = l, root->right = r;
		Repair_size(l, *l_, false), Repair_size(r, *r_, true);
		root->size = (root->left == nullptr ? 0 : root->left->size) + (root->right == nullptr ? 0 : root->right->size) + 1;
	}
	void Splay_kth(int k) {// start from 0
		Node *l, *r;
		Node **l_ = &l, **r_ = &r;
		int cur = Size_of_node(root->left);
		while(cur != k) {
			if(k < cur) {
				if(root->left == nullptr) break;
				int cur_left = cur - (1 + Size_of_node(root->left->right));
				if(k < cur_left && root->left->left != nullptr) {
					//right rotate
					Node *y = root->left;
					root->left = y->right, y->right = root;
					y->size = root->size, root->size -= y->left->size + 1;
					root = y;
				}
				//move to left
				cur -= 1 + Size_of_node(root->left->right);
				*r_ = root, r_ = &root->left;
				root->size -= root->left->size;
				root = root->left;
			}
			else {
				if(root->right == nullptr) break;
				int cur_right = cur + 1 + Size_of_node(root->right->left);
				if(k > cur_right && root->right->right != nullptr) {
					//left rotate
					Node *y = root->right;
					root->right = y->left, y->left = root;
					y->size = root->size, root->size -= y->right->size + 1;
					root = y;
				}
				//move to right
				cur += 1 + Size_of_node(root->right->left);
				*l_ = root, l_ = &root->right;
				root->size -= root->right->size;
				root = root->right;
			}
		}
		*l_ = root->left, *r_ = root->right;
		root->left = l, root->right = r;
		Repair_size(l, *l_, false), Repair_size(r, *r_, true);
		root->size = (root->left == nullptr ? 0 : root->left->size) + (root->right == nullptr ? 0 : root->right->size) + 1;
	}

	void clear(Node *root) {
		if(root != nullptr) {
			clear(root->left), clear(root->right);
			alloc.deallocate(root, 1);
		}
	}
public:
	rank_SplayTree() : root(nullptr), n_node(0) {}
	bool Has(const T &val) {
		return root != nullptr && (Splay(val), root->val == val);
	}
	T& Access(const T &val) {
		if(root != nullptr) return Splay(val), root->val;
	}
	T& Select(int k) {
		if(root != nullptr) return Splay_kth(k), root->val;
	}
	int AtRank(const T &val) {
		if(root != nullptr) {
			Splay(val);
			return Size_of_node(root->left) + (!(val < root->val));
		}
	}

};

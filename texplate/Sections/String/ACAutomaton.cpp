struct Node {
	Node *next[26], *fail;
	int end;
};
struct ACA {
	Node node[MAXN];
	int cnt_node;
	Node* new_node() {
		memset(&node[cnt_node], 0, sizeof(node[cnt_node]));
		return &node[cnt_node++];
	}
	Node* root;
	void init() {
		cnt_node = 0;
		root = new_node();
	}
	void insert(char *str, int len) {
		Node* cur = root;
		for(int i = 0; i < len; i++) {
			if(cur->next[str[i] - 'a'] == 0) {
				cur->next[str[i] - 'a'] = new_node();
			}
			cur = cur->next[str[i] - 'a'];
		}
		cur->end++;
	}
	void build() {
		std::queue<Node*> que;
		root->fail = root;
		for(int i = 0; i < 26; i++) {
			if(root->next[i] == 0) root->next[i] = root;
			else {
				root->next[i]->fail = root;
				que.push(root->next[i]);
			}
		}
		while(!que.empty()) {
			Node *u = que.front(); que.pop();
			for(int i = 0; i < 26; i++) {
				if(u->next[i] == 0) u->next[i] = u->fail->next[i];
				else {
					u->next[i]->fail = u->fail->next[i];
					que.push(u->next[i]);
				}
			}
		}
	}
} ac;

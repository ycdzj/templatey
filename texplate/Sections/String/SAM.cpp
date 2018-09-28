struct Node {
	Node *go[26], *par;
	int val;
};
struct SAM {
	Node node[MAXN * 2];
	int cnt_node;
	Node* new_node(int val) {
		memset(&node[cnt_node], 0, sizeof(Node));
		node[cnt_node].val = val;
		return &node[cnt_node++];
	}

	Node *root, *last;
	void init() {
		cnt_node = 0;
		root = last = new_node(0);
	}
	void extend(int w) {
		Node *p = last;
		Node *np = new_node(last->val + 1);
		while(p != 0 && p->go[w] == 0) {
			p->go[w] = np;
			p = p->par;
		}
		if(p == 0) np->par = root;
		else {
			Node *q = p->go[w];
			if(q->val == p->val + 1) np->par = q;
			else {
				Node *nq = new_node(p->val + 1);
				memcpy(nq->go, q->go, sizeof(q->go));
				nq->par = q->par;
				q->par = nq;
				np->par = nq;
				while(p != 0 && p->go[w] == q) {
					p->go[w] = nq;
					p = p->par;
				}
			}
		}
		last = np;
	}
} sam;
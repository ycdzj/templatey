//后缀自动机
//指针版：
struct samnode{
    samnode *son[26] , *f;
    int l , sc;
}*root,*last,sam[maxn];
int cnt;
char a[maxn];
void init(){
    root = last = &sam[cnt=0];
}
void add(int x)
{
    samnode *p = &sam[++cnt] , *jp=last;
    p->l = jp->l+1;
    last = p;
    for( ; jp&&!jp->son[x] ; jp=jp->f) jp->son[x]=p;
    if(!jp) p->f = root;
    else{
        if(jp->l+1 == jp->son[x]->l) p->f = jp->son[x];
        else{
            samnode *r = &sam[++cnt] , *q = jp->son[x];
            *r = *q;
            r->l = jp->l+1;
            q->f = p->f = r;
            for( ; jp && jp->son[x]==q ; jp=jp->f) jp->son[x]=r;
        }
    }
}
//数组版：
struct samnode{
    int son[26] , f;
    int l , sc;
}sam[maxn];
int cnt,root,last;
void init(){
    root = last = cnt = 1;
}
void add(int x) {
    int cur = ++cnt;
    sam[cur].l = sam[last].l + 1;
    int p;
    for (p=last; p && !sam[p].son[x]; p=sam[p].f)
        sam[p].son[x] = cur;
    if (!p)
        sam[cur].f = root;
    else {
        int q = sam[p].son[x];
        if (sam[p].l + 1 == sam[q].l)sam[cur].f = q;
        else {
            int clone = ++cnt;
            sam[clone]=sam[q];
            sam[clone].l = sam[p].l + 1;
            sam[q].f = sam[cur].f = clone;
            for (; p && sam[p].son[x]==q; p=sam[p].f)
            sam[p].son[x] = clone;
        }
    }
    last = cur;
}
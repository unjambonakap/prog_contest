
const int MAX_VTX = 8000 +100;
const int MAX_EDGES = 100000 +100;
const int MAX_COMP = 100 +100;

struct Node {
    Node *left, *right, *parent;
    bool everted;
    void rotate() {
        Node *p = parent;
        this->parent = p->parent;
        if (p->parent) {
            if (p==p->parent->left) p->parent->left = this;
            else p->parent->right = this;
        }
        if (this == p->left) {
            p->left = this->right;
            if (p->left) p->left->parent = p;
            this->right = p;
        } else {
            p->right = this->left;
            if (p->right) p->right->parent = p;
            this->left = p;
        }
        p->parent = this;
    }
    void evert() { everted = !everted; }
};

void pushdown(Node* v)
{
    if (!v->everted)
        return;
    swap(v->left, v->right);
    if (v->left)
        v->left->evert();
    if (v->right)
        v->right->evert();
}

void splay(Node* v)
{
    while (v->parent) {
        pushdown(v);
        pushdown(v->parent);
        if (v->parent->parent) pushdown(v->parent->parent);
        if (v->parent->parent!=NULL && ((v==v->parent->left) ==
                    (v->parent==v->parent->parent->left)))
            v->parent->rotate();
        v->rotate();
    }
}

void join(Node* n1, Node* n2, Node* r)
{
    debug printf("join %d %d %d\n", n1, n2, r);
    if (n1) {
        splay(n1);
        pushdown(n1);
        if (n1->right) n1->evert();
    }
    if (n2) {
        splay(n2);
        pushdown(n2);
        if (n2->left) n2->evert();
    }
    r->parent = NULL;
    r->left = n1;
    if (n1)
        r->left->parent = r;
    r->right = n2;
    if (n2)
        r->right->parent = r;
}

void split(Node* r)
{
    debug printf("split %d\n", r);
    splay(r);
    pushdown(r);
    if (r->left) r->left->parent = NULL;
    if (r->right) r->right->parent = NULL;
    r->left = r->right = NULL;
}

map<pair<int,int>, int> edge_to_comp; // beware! both should be same here and below (u,v and v,u)
map<pair<int,int>, Node*> edge_to_splay;
int comp_to_edge[MAX_VTX][MAX_COMP][2];

int n_nodes;
Node nodes[MAX_EDGES];

void remove_ownership(int v, int u, int c)
{
    debug printf("remove-ownership %d %d %d\n", v, u, c);
    if (comp_to_edge[v][c][0] == u)
        comp_to_edge[v][c][0] = -1;
    if (comp_to_edge[v][c][1] == u)
        comp_to_edge[v][c][1] = -1;
    if (comp_to_edge[u][c][0] == v)
        comp_to_edge[u][c][0] = -1;
    if (comp_to_edge[u][c][1] == v)
        comp_to_edge[u][c][1] = -1;
}

void add_ownership(int v, int u, int c)
{
    debug printf("add-ownership %d %d %d\n", v, u, c);
    if (comp_to_edge[v][c][0] == -1)
        comp_to_edge[v][c][0] = u;
    else
        comp_to_edge[v][c][1] = u;
    if (comp_to_edge[u][c][0] == -1)
        comp_to_edge[u][c][0] = v;
    else
        comp_to_edge[u][c][1] = v;
    edge_to_comp[make_pair(u, v)] = c;
    edge_to_comp[make_pair(v, u)] = c;
}

int cnt_ownership(int v, int c)
{
    return (comp_to_edge[v][c][0] != -1) + (comp_to_edge[v][c][1] != -1);
}

int get_owned_neigh(int v, int c)
{
    int r;
    if (comp_to_edge[v][c][0] != -1)
        r = comp_to_edge[v][c][0];
    else
        r = comp_to_edge[v][c][1];
    debug printf("get_owned_neigh %d %d = %d\n", v, c, r);
    return r;
}

void sell(pair<int,int> e)
{
    split(edge_to_splay[e]);
    remove_ownership(e.first, e.second, edge_to_comp[e]);
}

bool try_buy(pair<int,int> e, int c)
{
    if (edge_to_comp.count(e) == 0) {
        printf("No such cable.\n");
        return false;
    }
    if (edge_to_comp[e] == c) {
        printf("Already owned.\n");
        return false;
    }
    if (cnt_ownership(e.first, c) == 2 || cnt_ownership(e.second, c) == 2) {
        printf("Forbidden: monopoly.\n");
        return false;
    }
    if (cnt_ownership(e.first, c) == 0 || cnt_ownership(e.second, c) == 0) {
        printf("Sold.\n");
        return true;
    }
    pair<int,int> e1 = make_pair(e.first, get_owned_neigh(e.first, c));
    pair<int,int> e2 = make_pair(e.second, get_owned_neigh(e.second, c));
    Node *n1 = edge_to_splay[e1], *n2 = edge_to_splay[e2];
    debug printf("test %d %d\n", n1, n2);
    debug printf("test-n1 %d %d\n", n1->left, n1->right);
    debug printf("test-n2 %d %d\n", n2->left, n2->right);
    splay(n1);
    splay(n2);
    if (n1->parent != NULL) {
        printf("Forbidden: redundant.\n");
        return false;
    } else {
        printf("Sold.\n");
        return true;
    }
}

pair<int,int> prev(pair<int,int> p)
{
    return make_pair(p.second, p.first);
}

void do_buy(pair<int,int> e, int c)
{
    Node *n1 = NULL, *n2 = NULL;
    if (cnt_ownership(e.first, c) == 1) {
        pair<int,int> e1 = make_pair(e.first, get_owned_neigh(e.first, c));
        n1 = edge_to_splay[e1];
    }
    if (cnt_ownership(e.second, c) == 1) {
        pair<int,int> e2 = make_pair(e.second, get_owned_neigh(e.second, c));
        n2 = edge_to_splay[e2];
    }
    Node *n = edge_to_splay[e];
    if (!n) {
        n = &nodes[n_nodes++];
        debug printf("alloc %d for %d-%d\n", n, e.first, e.second);
        n->left = n->right = n->parent = NULL;
        n->everted = false;
        edge_to_splay[e] = n;
        edge_to_splay[prev(e)] = n;
    }
    join(n1, n2, n);
    add_ownership(e.first, e.second, c);
}

bool scase()
{
    int N, M, C, T;
    scanf("%d%d%d%d", &N, &M, &C, &T);
    if (N == 0) return false;
    for(int i=0;i<N;i++)
        for(int j=0;j<C;j++)
            comp_to_edge[i][j][0] = comp_to_edge[i][j][1] = -1;
    edge_to_comp.clear();
    edge_to_splay.clear();
    n_nodes = 0;
    while (M--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        u--;v--;c--;
        do_buy(make_pair(u, v), c);
    }
    while (T--) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        u--;v--;c--;
        if (try_buy(make_pair(u, v), c)) {
            sell(make_pair(u, v));
            do_buy(make_pair(u, v), c);
        }
    }
    printf("\n");
    return true;
}

int main()
{
    while(scase()) {}
    return 0;
}



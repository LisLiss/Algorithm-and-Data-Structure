#include <bits/stdc++.h>

using namespace std;
typedef struct node{
    node* l=nullptr;
    node* r=nullptr;
    node* p=nullptr;
    bool rev=false;
    int x;
};
typedef node* pnode;
bool isRoot(pnode v){
    if ((v->p==nullptr) || (v->p->l!=v && v->p->r!=v)) return true;
    return false;
}
void pushing(pnode v){
    if (false==(v->rev)) return;
    v->rev=false;
    pnode help=v->l; v->l=v->r; v->r=help;
    if (v->l!=nullptr) v->l->rev=!(v->l->rev);
    if (v->r!=nullptr) v->r->rev=!(v->r->rev);
}
void connect(pnode v, pnode u, int isLeft){
    if (v!=nullptr) v->p=u;
    if (isLeft!=-1){
        if (isLeft==1) u->l=v;
        else u->r=v;
    }
}
void turn(pnode v) {
        pnode parent = v->p;
        pnode grandpa = parent->p;
        bool isRootParent = isRoot(parent);
        bool isLeftChild = (v == parent->l);

        connect((isLeftChild ? v->r : v->l), parent, isLeftChild);
        connect(parent, v, !isLeftChild);
        connect(v, grandpa, !isRootParent ? parent == grandpa->l : -1);
}
void splay(pnode v){
    while (!isRoot(v)){
        if (!isRoot(v->p)) pushing(v->p->p);
        pushing(v->p);
        pushing(v);
        if (!isRoot(v->p)){
            if ((v==v->p->l)==(v->p==v->p->p->l)) turn(v->p);
            else turn(v);
        }
        turn(v);
    }
    pushing(v);
}
pnode exposing(pnode v){
    pnode help=nullptr;
    for (pnode i=v; i!=nullptr; i=i->p){
        splay(i);
        i->l=help;
        help=i;
    }
    splay(v);
    return help;
}
void makeRev(pnode v){
    exposing(v);
    v->rev=!(v->rev);
}
bool connected(pnode a, pnode b){
    if (a==b) return true;
    exposing(a);
    exposing(b);
    if (a->p==nullptr) return false;
    return true;
}
void linking(pnode a, pnode b){
    makeRev(a);
    a->p=b;
}
void cuting(pnode a, pnode b){
    makeRev(a);
    exposing(b);
    b->r->p=nullptr;
    b->r=nullptr;
}

void printing(pnode v){
    if (v==nullptr) return;
    cout<<v->x<<" ";
    printing(v->l);
    printing(v->r);
}

int main(){
    int n, m, x, y;
    cin>>n>>m;
    vector <pnode> mas(n+1);
    for (int i=0; i<n+1; i++) {
        mas[i]=new node;
        mas[i]->x=i;
    }
    string s;
    for (int i=0; i<m; i++){
        cin>>s;
        cin>>x>>y;
        if (s=="link") linking(mas[x], mas[y]);
        if (s=="connected") cout<<connected(mas[x], mas[y])<<endl;
        if (s=="cut") cuting(mas[x], mas[y]);
    }
    return 0;
}

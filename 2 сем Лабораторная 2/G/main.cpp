#include <bits/stdc++.h>

using namespace std;
#define ll long long
typedef struct node{
    node* l=nullptr;
    node* r=nullptr;
    ll x, y;
    ll c=1;
};
typedef node* pnode;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 1000000);

ll getC(pnode v){
    if (v==nullptr) return 0;
    return v->c;
}
void updateC(pnode v){
    if (v!=nullptr) v->c=getC(v->l)+getC(v->r)+1;
}
pair<pnode, pnode> split(pnode v, ll x){
    if (v==nullptr) return make_pair(nullptr, nullptr);
    ll l=getC(v->l);
    if (l<x){
        pair<pnode, pnode> help = split(v->r, x-l-1);
        v->r=help.first;
        updateC(v);
        return make_pair(v, help.second);
    } else{
        pair<pnode, pnode> help = split(v->l, x);
        v->l=help.second;
        updateC(v);
        return make_pair(help.first, v);
    }
}
pnode merging(pnode l, pnode r){
    if (l==nullptr) return r;
    if (r==nullptr) return l;
    if (r->y>l->y){
        r->l=merging(l, r->l);
        updateC(r);
        return r;
    } else{
        l->r=merging(l->r, r);
        updateC(l);
        return l;
    }
}
pnode inserting(pnode v, ll x){
    pair <pnode, pnode> splited = split (v, x);
    pnode help = new node;
    help->x=x;
    help->y=dis(gen);
    help->c=x;
    help = merging(splited.first, help);
    return merging (help, splited.second);
}

pnode ans(pnode v, ll l, ll r){
    pair <pnode, pnode> help1 = split(v, l-1);
    r-=l;
    pair<pnode, pnode> help2 = split(help1.second, r+1);
    pnode v2=merging(help2.first, help1.first);
    return merging(v2, help2.second);
}

void print(pnode v){
    if (v==nullptr) return;
    print(v->l);
    cout<<v->x<<" ";
    print(v->r);
}

int main(){
    ll n, m;
    cin>>n>>m;
    pnode root=nullptr;
    for (ll i=0; i<n; i++){
        root=inserting(root, i+1);
    }
    ll l, r;
    for (ll i=0; i<m; i++){
        cin>>l>>r;
        root=ans(root, l, r);
    }
    print(root);
    return 0;
}

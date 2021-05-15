#include <bits/stdc++.h>

using namespace std;
#define ll long long
typedef struct node{
    node* l=nullptr;
    node* r=nullptr;
    ll x, y;
    ll c=1;
    ll s;
};
typedef node* pnode;
ll length=0;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 5000000);

ll getC(pnode v){
    if (v==nullptr) return 0;
    return v->c;
}
void updateC(pnode v){
    if (v!=nullptr) v->c=getC(v->l)+getC(v->r)+1;
}
ll getS(pnode v){
    if (v==nullptr) return 0;
    return v->s;
}
void updateS(pnode v){
    if (v!=nullptr) v->s=getS(v->l)+getS(v->r)+(v->x==0?1:0);
}

pair<pnode, pnode> split(pnode v, ll x){
    if (v==nullptr) return make_pair(nullptr, nullptr);
    ll l=getC(v->l);
    if (l<x){
        pair<pnode, pnode> help = split(v->r, x-l-1);
        v->r=help.first;
        updateC(v);
        updateS(v);
        return make_pair(v, help.second);
    } else{
        pair<pnode, pnode> help = split(v->l, x);
        v->l=help.second;
        updateC(v);
        updateS(v);
        return make_pair(help.first, v);
    }
}
pnode merging(pnode l, pnode r){
    if (l==nullptr) return r;
    if (r==nullptr) return l;
    if (r->y>l->y){
        r->l=merging(l, r->l);
        updateC(r);
        updateS(r);
        return r;
    } else{
        l->r=merging(l->r, r);
        updateC(l);
        updateS(l);
        return l;
    }
}
pnode inserting(pnode v, ll x){
    pair <pnode, pnode> splited = split (v, x);
    pnode help = new node;
    help->x=0;
    help->y=dis(gen);
    help->s=1;
    help = merging(splited.first, help);
    return merging (help, splited.second);
}
ll maxl=0;
void print(pnode v){
    if (v==nullptr) return;
    print(v->l);
    if (maxl>=length) return;
    cout<<v->x<<" ";
    maxl++;
    print(v->r);
}

ll findLeftInd(pnode v){
    if (v==nullptr) return 0;
    if (v->l==nullptr || v->l->s==0) {
        if (v->x==0) return getC(v->l);
        return getC(v->l)+1+findLeftInd(v->r);
    } else{
        return findLeftInd(v->l);
    }
}

pnode ans(pnode v, ll l, ll x){
    pair <pnode, pnode> help1 = split(v, l-1);
    pair<pnode, pnode> help2 = split(help1.second, 1);
    if (help2.first->x==0) {
        help2.first->x=x;
        //help2.first->s--;
        length=max(length, l);
        pnode v2=merging(help1.first, help2.first);
        return merging(v2, help2.second);
    }
    ll left=findLeftInd(help2.second);
    length=max(length, left+l+1);
    pair<pnode, pnode> help3 = split(help2.second, left);
    pair<pnode, pnode> help4 = split(help3.second, 1);
    pnode helpV=new node;
    helpV->x=x;
    helpV->y=dis(gen);
    helpV->s=0;
    pnode v3=merging(help1.first, helpV);
    v3=merging(v3, help2.first);
    v3=merging(v3, help3.first);
    return merging(v3, help4.second);
}
int main(){
    ll n, m;
    cin>>n>>m;
    pnode root=nullptr;
    for (ll i=0; i<n+m+1; i++){
        root=inserting(root, i+1);
    }
    ll l;
    for (ll i=0; i<n; i++){
        cin>>l;
        root=ans(root, l, i+1);
    }
    cout<<length<<endl;
    print(root);
    return 0;
}

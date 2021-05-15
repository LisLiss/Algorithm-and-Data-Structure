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

ll getC(pnode v){
    if (v==nullptr) return 0;
    return v->c;
}
void updateC(pnode v){
    if (v!=nullptr) v->c=getC(v->l)+getC(v->r)+1;
}
pair<pnode, pnode> split(pnode v, ll x){
    if (v==nullptr) return make_pair(nullptr, nullptr);
    if (v->x<x){
        pair<pnode, pnode> help = split(v->r, x);
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
pnode inserting(pnode v, ll x, ll y){
    if (v==nullptr){
        pnode help= new node;
        help->x=x;
        help->y=y;
        return help;
    }
    if (y>v->y){
        pair<pnode, pnode> help = split(v, x);
        pnode h= new node;
        h->x=x;
        h->y=y;
        h->l=help.first;
        h->r=help.second;
        updateC(h);
        return h;
    } else{
        if (x<v->x){
            v->l=inserting(v->l, x, y);
        } else{
            v->r=inserting(v->r, x, y);
        }
        updateC(v);
        return v;
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

pnode removing(pnode v, ll x){
    if (v->x==x) return merging(v->l, v->r);
    if (x<v->x) v->l=removing(v->l, x);
    else v->r=removing(v->r, x);
    updateC(v);
    return v;
}

ll getK(pnode v, ll k){
    if (v==nullptr) return -1;
    if (getC(v->r)==k-1) return v->x;
    if (getC(v->r)>=k) return getK(v->r, k);
    return getK(v->l, k-getC(v->r)-1);
}
vector <ll> massiv;
void toArray(pnode v){
    if (v==nullptr) return;
    toArray(v->l);
    massiv.push_back(getC(v));
    toArray(v->r);
}

int main(){
    ll n;
    cin>>n;
    pnode root=nullptr;
    ll t, x, y;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000000);
    for (ll i=0; i<n; i++){
        cin>>t>>x;
        if (t==1){
            y=dis(gen);
            root=inserting(root, x, y);
        }
        if (t==0){
            cout<<getK(root, x)<<endl;
        }
        if (t==-1){
            root=removing(root, x);
        }
    }
    return 0;
}

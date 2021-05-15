#include <bits/stdc++.h>

using namespace std;
 #define ll long long
 struct pn{
    ll x, delta, type;
    //type 1 - set
    //type 2 - add
 };
 vector <pn> tree;
 vector <ll> a;
 void rec(ll l, ll r, ll v){
    tree[v].delta=0;
    tree[v].type=0;
    if (r-l==1){
        tree[v].x=a[l];
    } else{
        ll m=(l+r)/2;
        rec(l,m,2*v+1);
        rec(m,r,2*v+2);
        tree[v].x=min(tree[2*v+1].x,tree[2*v+2].x);
    }
}
void push(ll v){
    if (tree[v].type==0) return;
    if (tree[v].type==1){
        tree[2*v+1].type=tree[v].type;
        tree[2*v+1].delta=tree[v].delta;
        tree[2*v+2].type=tree[v].type;;
        tree[2*v+2].delta=tree[v].delta;
    } else{
        if (tree[2*v+1].type==1){
            tree[2*v+1].type=1;
        } else{
            tree[2*v+1].type=tree[v].type;
        }
        tree[2*v+1].delta+=tree[v].delta;
        if (tree[2*v+2].type==1){
            tree[2*v+2].type=1;
        } else{
            tree[2*v+2].type=tree[v].type;
        }
        tree[2*v+2].delta+=tree[v].delta;
    }
    tree[v].type=0;
    tree[v].delta=0;
}

ll getVal(ll v){
    if (tree[v].type==0) return tree[v].x;
    if (tree[v].type==1){
        return tree[v].delta;
    } else{
        return tree[v].x+tree[v].delta;
    }
}
void update(ll v, ll l, ll r, ll nl, ll nr, ll type, ll delta){
    if (r<=nl || l>=nr) return;
    if ((nl>=l) && (nr<=r)){
        if (type == 1){
            tree[v].type=1;
            tree[v].delta=delta;
        } else{
            if (tree[v].type!=1){
                tree[v].type=2;
            }
            tree[v].delta+=delta;
        }
        return;
    }
    push(v);
    ll m=(nl+nr)/2;
    update(2*v+1, l, r, nl, m, type, delta);
    update(2*v+2, l, r, m, nr, type, delta);
    tree[v].x=min(getVal(2*v+1), getVal(2*v+2));
}

ll minans(ll v, ll nl, ll nr, ll l, ll r){
    if (r<=nl || l>=nr) return LONG_LONG_MAX;
    if ((nl>=l) && (nr<=r)) return getVal(v);
    push(v);
    ll m=(nl+nr)/2;
    ll ans= min(minans(2*v+1,nl,m,l,r), minans(2*v+2,m,nr,l,r));
    tree[v].x=min(getVal(2*v+1), getVal(2*v+2));
    return ans;
}

int main()
{
    ll n;
    cin>>n;
    a.resize(n);
    tree.resize(4*n);
    for (int i=0; i<n; i++){
        cin>>a[i];
    }
    rec(0, n, 0);
    string com;
    ll x, y, z;
    while(cin>>com){
        cin>>x>>y;
        if(com=="min"){
            cout<<minans(0, 0, n, x-1, y)<<endl;
        } else{
            cin>>z;
            if (com=="set"){
                update(0, x-1, y, 0, n, 1, z);
            } else{
                update(0, x-1, y, 0, n, 2, z);
            }
        }
    }
    return 0;
}

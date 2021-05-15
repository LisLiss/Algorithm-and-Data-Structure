#include <bits/stdc++.h>

using namespace std;
#define ll long long

 struct pn{
    ll minn, ind, c;
 };
 vector <pn> tree;
 vector <ll> a;
 ll inf = LONG_LONG_MAX;

 void rec(ll l, ll r, ll v){
    tree[v].c=0;
    if (r-l==1){
        tree[v].minn=a[l];
        tree[v].ind=l;
    } else{
        ll m=(l+r)/2;
        rec(l,m,2*v+1);
        rec(m,r,2*v+2);
        tree[v].minn=min(tree[2*v+1].minn,tree[2*v+2].minn);
        if (tree[v].minn==tree[2*v+1].minn) tree[v].ind=tree[2*v+1].ind;
        else tree[v].ind=tree[2*v+2].ind;
    }
}

void push(ll v){
    if (tree[v].c==0) return;
    if (tree[v].minn<tree[v].c){
        tree[v].minn=tree[v].c;
        tree[2*v+1].c=max(tree[v].c, tree[2*v+1].c);
        tree[2*v+2].c=max(tree[v].c, tree[2*v+2].c);
    }
    tree[v].c=0;
}

ll getVal(ll v){
    if (tree[v].c==0) return tree[v].minn;
    if (tree[v].minn>=tree[v].c) return tree[v].minn;
    else return tree[v].c;
}
ll getInd(ll v){
    return tree[v].ind;
}

void update(ll v, ll l, ll r, ll nl, ll nr,ll c){
    if (r<=nl || l>=nr) return;
    if ((nl>=l) && (nr<=r)){
        tree[v].c=max(tree[v].c,c);
        return;
    }
    push(v);
    ll m=(nl+nr)/2;
    update(2*v+1, l, r, nl, m, c);
    update(2*v+2, l, r, m, nr, c);
    if (getVal(2*v+1)<=getVal(2*v+2)){
        tree[v].minn=getVal(2*v+1);
        tree[v].ind=tree[2*v+1].ind;
    } else{
        tree[v].minn=getVal(2*v+2);
        tree[v].ind=tree[2*v+2].ind;
    }
}

pair<ll, ll> minans(ll v, ll nl, ll nr, ll l, ll r){
    if (r<=nl || l>=nr) return make_pair(inf, inf);
    if ((nl>=l) && (nr<=r)) return make_pair(getVal(v),getInd(v));
    push(v);
    ll m=(nl+nr)/2;
    pair<ll, ll> min1,min2;
    min1=minans(2*v+1,nl,m,l,r);
    min2=minans(2*v+2,m,nr,l,r);
    if (getVal(2*v+1)<=getVal(2*v+2)){
        tree[v].minn=getVal(2*v+1);
        tree[v].ind=tree[2*v+1].ind;
    } else{
        tree[v].minn=getVal(2*v+2);
        tree[v].ind=tree[2*v+2].ind;
    }
    if (min1.first==min2.first){
        if (min1.second<l) return min2;
        if (min2.second>=r) return min1;
        return min1;
    }
    if (min1.first<min2.first){
        return min1;
    } else return min2;
}


int main()
{
    ll n,m;
    cin>>n>>m;
    a.resize(n);
    tree.resize(4*n);
    for (int i=0; i<n; i++){
        a[i]=0;
    }
    rec(0, n, 0);
    string com;
    ll x,y,c;
    pair<ll,ll> ans;
    for (ll i=0; i<m; i++){
        //for (ll j=0; j<4*n; j++) cout<<tree[j].minn<<"."<<tree[j].ind<<"."<<tree[j].c<<" ";
        //cout<<endl;
        cin>>com;
        cin>>x>>y;
        if(com=="attack"){
            ans=minans(0, 0, n, x-1, y);
            cout<<ans.first<<" "<<ans.second+1<<endl;
        } else{
            cin>>c;
            update(0, x-1, y, 0, n, c);
        }
    }
    return 0;
}

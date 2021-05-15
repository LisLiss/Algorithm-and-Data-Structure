#include <bits/stdc++.h>

using namespace std;
 #define ll long long
 vector <ll> tree, a;
 ll inf = 200000;

 void rec(ll l, ll r, ll v){
    if (r-l==1){
        tree[v]=a[l];
    } else{
        ll m=(l+r)/2;
        rec(l,m,2*v+1);
        rec(m,r,2*v+2);
        tree[v]=min(tree[2*v+1],tree[2*v+2]);
    }
 }

 ll minn(ll nl, ll nr, ll l, ll r, ll v){
    if (r<=nl || l>=nr) return inf;
    if ((nl>=l) && (nr<=r)) return tree[v];
    ll m=(nl+nr)/2;
    return min(minn(nl, m,l,r,2*v+1),minn(m,nr,l,r,2*v+2));
 }
 void setx(ll i, ll x, ll v, ll l, ll r){
    if (r-l==1) tree[v]=x;
    else{
        ll m=(l+r)/2;
        if (i<m){
            setx(i,x,2*v+1,l,m);
        } else{
            setx(i,x,2*v+2,m,r);
        }
        tree[v]=min(tree[2*v+1],tree[2*v+2]);
    }
 }

int main()
{
    ifstream f1("parking.in");
    ofstream f2("parking.out");
    ll n;
    f1>>n;
    a.resize(n);
    tree.resize(4*n);
    for (int i=0; i<n; i++){
        a[i]=i;
    }
    rec(0, n, 0);
    ll m, ans;
    f1>>m;
    string com;
    ll x;
    for (ll i=0; i<m; i++){
        f1>>com;
        f1>>x;
        x--;
        if(com=="enter"){
            ans=minn(0,n,x,n,0);
            if (ans==inf) {
                ans=minn(0,n,0,n,0);
            }
            f2<<ans+1<<endl;
            setx(ans, inf, 0, 0, n);
        } else{
            setx(x, x, 0, 0, n);
        }
    }
    return 0;
}

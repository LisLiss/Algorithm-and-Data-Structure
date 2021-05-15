#include <bits/stdc++.h>

using namespace std;
 #define ll long long
 vector <ll> tree, a;
 void rec(ll l, ll r, ll v){
    if (r-l==1){
        tree[v]=a[l];
    } else{
        ll m=(l+r)/2;
        rec(l,m,2*v+1);
        rec(m,r,2*v+2);
        tree[v]=tree[2*v+1]+tree[2*v+2];
    }
 }

 ll sum(ll nl, ll nr, ll l, ll r, ll v){
    if (r<=nl || l>=nr) return 0;
    if ((nl>=l) && (nr<=r)) return tree[v];
    ll m=(nl+nr)/2;
    return sum(nl, m,l,r,2*v+1)+sum(m,nr,l,r,2*v+2);
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
        tree[v]=tree[2*v+1]+tree[2*v+2];
    }
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
    ll x, y;
    while(cin>>com){
        cin>>x>>y;
        if(com=="sum"){
            cout<<sum(0,n,x-1,y,0)<<endl;
        } else{
            setx(x-1, y, 0, 0, n);
        }
    }
    return 0;
}

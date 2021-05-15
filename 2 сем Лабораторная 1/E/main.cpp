#include <bits/stdc++.h>

using namespace std;
#define ll long long
 struct pp{
    ll a11, a12, a21, a22;
 };
 pp nx;
 vector <pp> tree, a;
 ll rr;
 pp mul(pp x, pp y){
    pp ans;
    ans.a11=(x.a11*y.a11%rr+x.a12*y.a21%rr)%rr;
    ans.a12=(x.a11*y.a12%rr+x.a12*y.a22%rr)%rr;
    ans.a21=(x.a21*y.a11%rr+x.a22*y.a21%rr)%rr;
    ans.a22=(x.a21*y.a12%rr+x.a22*y.a22%rr)%rr;
    return ans;
 }

 void rec(ll l, ll r, ll v){
    if (r-l==1){
        tree[v]=a[l];
    } else{
        ll m=(l+r)/2;
        rec(l,m,2*v+1);
        rec(m,r,2*v+2);
        tree[v]=mul(tree[2*v+1],tree[2*v+2]);
    }
 }

 pp sum(ll nl, ll nr, ll l, ll r, ll v){
    if (r<=nl || l>=nr) return nx;
    if ((nl>=l) && (nr<=r)) return tree[v];
    ll m=(nl+nr)/2;
    return mul(sum(nl, m,l,r,2*v+1),sum(m,nr,l,r,2*v+2));
 }

 int main(){
     ifstream f1("crypto.in");
     ofstream f2("crypto.out");

     nx.a11=1;
     nx.a12=0;
     nx.a21=0;
     nx.a22=1;
    ll n,m;
    pp ans;
    f1>>rr>>n>>m;;
    a.resize(n);
    tree.resize(4*n);
    for (ll i=0; i<n; i++){
        f1>>a[i].a11>>a[i].a12>>a[i].a21>>a[i].a22;
    }
    rec(0, n, 0);
    ll x, y;
    for(ll i=0; i<m; i++){
        f1>>x>>y;
        ans = sum(0, n, x-1, y, 0);
        f2<<ans.a11<<" "<<ans.a12<<" "<<"\n"<<ans.a21<<" "<<ans.a22<<"\n"<<"\n";
    }
    f1.close();
    f2.close();
    return 0;
 }

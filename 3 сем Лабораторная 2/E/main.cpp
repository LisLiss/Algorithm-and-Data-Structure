#include <bits/stdc++.h>

using namespace std;

#define ll long long
struct e {
    ll x, y, w;
};
vector <bool> was;
vector <e> edges;

void dfs(ll v){
    if (was[v]) return;
    was[v]=true;
    for (e i:edges){
        if (i.x==v) dfs(i.y);
    }
}
int main()
{
    ll n, m, s, inf=1e20;
    cin>>n>>m>>s;
    s--;
    was.resize(n, false);
    for (ll i=0; i<m; i++){
        ll x, y, w;
        cin>>x>>y>>w; x--; y--;
        e help; help.x=x; help.y=y; help.w=w;
        edges.push_back(help);
    }
    vector <ll> d(n, inf), d2(n);
    d[s]=0;
    for (ll i=0; i<n-1; i++){
        for (e j:edges){
            if (d[j.x]<inf) d[j.y]=min(d[j.y], d[j.x]+j.w);
           // if (d[j.y]<-inf) d[j.y]=-inf;
        }
    }
    for (int i=0; i<n; i++) d2[i]=d[i];
    for (e j:edges){
        if (d2[j.x]<inf) d2[j.y]=min(d2[j.y], d2[j.x]+j.w);
        //if (d2[j.y]<-inf) d2[j.y]=-inf;
    }
    for (ll i=0; i<n; i++){
        if (d[i]!=d2[i]) dfs(i);
    }
    for (ll i=0; i<n; i++){
        if (was[i]) cout<<"-";
         else if (d2[i]>=inf) cout<<"*";
        else cout<<d2[i];
        cout<<endl;
    }
    return 0;
}

#include <bits/stdc++.h>

using namespace std;
#define ll long long

int n,m;
vector <vector <pair <ll, ll> > > g;
ll dei(int v, int b){
    set <pair <ll, ll> > mini;
    mini.insert(make_pair(0,v));
    vector <bool> used(n, false);
    vector <ll> d(n, 1e18);
    d[v]=0;
    for (int i=0; i<n; i++){
        if (mini.size()==0) break;
        ll now = (*mini.begin()).second;
        mini.erase(mini.begin());
        used[now]=true;
        for (int j=0; j<g[now].size(); j++){
            if (d[now]+g[now][j].second<d[g[now][j].first]){
                mini.erase(make_pair(d[g[now][j].first], g[now][j].first));
                mini.insert(make_pair(d[now]+g[now][j].second, g[now][j].first));
                d[g[now][j].first] = d[now]+g[now][j].second;
            }
        }
    }
    return d[b];
}
int main(){
    cin>>n>>m;
    g.resize(n);
    for (int i=0; i<m; i++){
        ll x, y, w;
        cin >>x>>y>>w;
        x--; y--;
        g[x].push_back(make_pair(y, w));
        g[y].push_back(make_pair(x, w));
    }
    ll a, b, c;
    cin>>a>>b>>c;
    a--; b--; c--;
    ll ab=dei(a, b);
    ll bc=dei(b, c);
    ll ac=dei(a, c);
    //abc acb bac
    if (ab>=1e18 || bc>=1e18 || ac>=1e18){
        cout<<"-1";
        return 0;
    }
    ll ans = min ( min (ab+bc, ac+bc), ab+ac);
    cout<<ans;
    return 0;
}

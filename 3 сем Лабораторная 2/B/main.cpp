    #include <bits/stdc++.h>

    using namespace std;
    #define ll long long
    int main(){
        int n,m;
        cin>>n>>m;
        vector <vector <pair <ll, ll> > > g(n);
        vector <ll> d(n, 1e10);
        vector <bool> used(n, false);
        d[0]=0;
        for (int i=0; i<m; i++){
            ll x, y, w;
            cin >>x>>y>>w;
            x--; y--;
            g[x].push_back(make_pair(y, w));
            g[y].push_back(make_pair(x, w));
        }
        set <pair <ll, ll> > mini;
        mini.insert(make_pair(0,0));
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
        for (int i=0; i<n; i++) cout<<d[i]<<" ";
        return 0;
    }

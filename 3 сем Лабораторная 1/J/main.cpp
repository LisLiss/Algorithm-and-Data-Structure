#include <bits/stdc++.h>

using namespace std;
vector <int> p;
vector <pair < pair < int, int> , int > > matrix;
int n, m;
long long ans;
int get(int v){
    return (v == p[v]) ? v : (p[v] = get (p[v]));
    //if (v == p[v]) return v;
    //p[v]=get(p[v]);
    //return p[v];
}

int unite (int x, int y){
    x = get(x);
    y = get(y);
    if (x!=y) p[x]=y;
}

void kruskal(){
    for (int i=0; i<m; i++){
        int x = matrix[i].first.first;
        int y = matrix[i].first.second;
        int w = matrix[i].second;
        if (get(x)!=get(y)){
            ans+=w;
            unite(x, y);
        }
    }
}

bool cmp(pair < pair < int, int> , int > x, pair < pair < int, int> , int > y){
    return x.second < y.second;
}
int main(){
    cin>>n>>m;
    p.resize(n);
    for (int i=0; i<n; i++) p[i]=i;
    for (int i=0; i<m; i++){
        int x, y, w;
        cin>>x>>y>>w;
        x--; y--;
        matrix.push_back(make_pair(make_pair(x, y), w));
    }
    ans=0;
    sort (matrix.begin(), matrix.end(), cmp);
    kruskal();
    cout<<ans;
    return 0;
}

#include <bits/stdc++.h>

using namespace std;
int n, m;
vector <vector <pair <int, int> > > matrix;
vector <bool> used;
vector <int> tin, tup, bridges;
int t;

void dfs(int v, int p){
    used[v]=true;
    tin[v]=t;
    tup[v]=t;
    t++;
    for (int i=0; i<matrix[v].size(); i++){
        if (matrix[v][i].first==p) continue;
        if (used[matrix[v][i].first]) tup[v]=min(tup[v], tin[matrix[v][i].first]);
        else{
            dfs(matrix[v][i].first, v);
            tup[v]=min(tup[v], tup[matrix[v][i].first]);
            if (tup[matrix[v][i].first] > tin[v]) bridges.push_back(matrix[v][i].second);
        }
    }
}
void makeans(){
    for (int i=0; i<n; i++)
        if (!used[i]) dfs(i, -1);
}

int main(){
    cin>>n>>m;
    matrix.resize(n);
    tin.resize(n);
    tup.resize(n);
    used.resize(n, false);
    for (int i=0; i<m; i++){
        int x, y;
        cin>>x>>y;
        x--; y--;
        matrix[x].push_back(make_pair(y, i));
        matrix[y].push_back(make_pair(x, i));
    }
    t=0;
    makeans();
    sort(bridges.begin(), bridges.end());
    cout<<bridges.size()<<endl;
    for (int i=0; i<bridges.size(); i++) cout<<bridges[i]+1<<endl;
    return 0;
}

#include <bits/stdc++.h>

using namespace std;

int n, m;
vector <vector <int> > matrix, trmatrix;
vector <bool> used;
vector <int> comp, topsort;
int nowcomp;
vector <pair <int, int> > edges;

void dfs(int v){
    used[v]=true;
    for (int i=0; i<matrix[v].size(); i++){
        if (!used[matrix[v][i]]) dfs(matrix[v][i]);
    }
    topsort.push_back(v);
}

void trdfs(int v){
    used[v]=true;
    comp[v]=nowcomp;
    for (int i=0; i<trmatrix[v].size(); i++){
        if (!used[trmatrix[v][i]]) trdfs(trmatrix[v][i]);
    }
}

void makedfs(){
    for (int i=0; i<n; i++){
        if (!used[i]) dfs(i);
    }
}
void maketrdfs(){
    for (int i=0; i<n; i++){
        if (!used[topsort[n-i-1]]) {
            trdfs(topsort[n-i-1]);
            nowcomp++;
        }
    }
}

void makeans(){
    set <pair <int, int> > ans;
    for (int i=0; i<m; i++){
        if (comp[edges[i].first]!=comp[edges[i].second]) ans.insert(make_pair(comp[edges[i].first], comp[edges[i].second]));
    }
    cout<<ans.size();
}
int main(){
    cin>>n>>m;
    matrix.resize(n);
    trmatrix.resize(n);
    used.resize(n, false);
    comp.resize(n, 0);

    for (int i=0; i<m; i++){
        int x, y;
        cin>>x>>y;
        x--; y--;
        edges.push_back(make_pair(x, y));
        matrix[x].push_back(y);
        trmatrix[y].push_back(x);
    }
    makedfs();
    used.clear();
    used.resize(n, false);
    nowcomp=1;
    maketrdfs();
    makeans();
    return 0;
}

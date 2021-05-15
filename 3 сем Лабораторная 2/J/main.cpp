#include <bits/stdc++.h>

using namespace std;
vector <int> grandy;
vector <vector <int> > matrix;
vector <bool> was;
int n, m;

int mex (set<int> gr){
    for (int i=0; ; i++){
        if (!gr.count(i)) return i;
    }
}

void dfs(int v){
    if (was[v]) return;
    was[v]=true;
    set<int> help;
    for (int i : matrix[v]){
        dfs(i);
        help.insert(grandy[i]);
    }
    grandy[v]=mex(help);
}

int main(){
    cin>>n>>m;
    matrix.resize(n);
    was.resize(n, false);
    grandy.resize(n, -1);
    for (int i=0; i<m; i++){
        int x, y;
        cin>>x>>y; x--; y--;
        matrix[x].push_back(y);
    }
    for (int i=0; i<n; i++){
        if (!was[i]) dfs(i);
    }
    for (int i=0; i<n; i++){
        cout<<grandy[i]<<endl;
    }
    return 0;
}

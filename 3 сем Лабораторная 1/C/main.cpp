#include <bits/stdc++.h>

using namespace std;
int n, m;
vector <vector <int> > matrix;
vector <bool> used, ans;
vector <int> tin, tup;
int t;

void dfs(int v, int p){
    used[v]=true;
    tin[v]=t;
    tup[v]=t;
    t++;
    int child=0;
    for (int i=0; i<matrix[v].size(); i++){
        if (matrix[v][i]==p) continue;
        if (used[matrix[v][i]]) tup[v]=min(tup[v], tin[matrix[v][i]]);
        else{
            child++;
            dfs(matrix[v][i], v);
            tup[v]=min(tup[v], tup[matrix[v][i]]);
            if (p!=-1 && tup[matrix[v][i]] >= tin[v]) ans[v]=true;
        }
    }
    if (p==-1 && child>1) ans[v]=true;
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
    ans.resize(n, false);
    for (int i=0; i<m; i++){
        int x, y;
        cin>>x>>y;
        x--; y--;
        matrix[x].push_back(y);
        matrix[y].push_back(x);
    }
    t=0;
    makeans();
    int k=0;
    for (int i=0; i<n; i++) if (ans[i]) k++;;
    cout<<k<<endl;
    for (int i=0; i<n; i++) if (ans[i]) cout<<i+1<<" ";
    return 0;
}

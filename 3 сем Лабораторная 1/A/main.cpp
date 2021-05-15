#include <bits/stdc++.h>

using namespace std;
int n, m;
vector <vector <int> > matrix;
vector <int> used;
vector <int> ans;
bool cycle = false;
//0-white 1-gray 2-black
void dfs(int v) {
    used[v]=1;
    for (int i=0; i<matrix[v].size(); i++){
        if (used[matrix[v][i]]==0) dfs(matrix[v][i]);
        if (used[matrix[v][i]]==1) cycle=true;
    }
    ans.push_back(v);
    used[v]=2;
}
void topsort(){
    for (int i=0; i<n; i++){
        if (used[i]==0) dfs(i);
    }
}

int main(){
    cin>>n>>m;

    matrix.resize(n);
    used.resize(n, 0);

    for (int i=0; i<m; i++){
        int x, y;
        cin>>x>>y;
        x--; y--;
        matrix[x].push_back(y);
    }
    topsort();
    if (cycle) {
        cout <<"-1";
        return 0;
    }
    for (int i=n-1; i>-1; i--) cout<<ans[i]+1<<" ";
    return 0;
}

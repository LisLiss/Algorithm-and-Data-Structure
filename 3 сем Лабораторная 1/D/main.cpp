#include <bits/stdc++.h>

using namespace std;
int n, m;
vector <vector <pair <int, int> > > matrix;
vector <bool> used, bridges;
vector <int> tin, tup, ans;
int t, maxans;

void dfs(int v, int p){
    used[v]=true;
    tin[v]=t;
    tup[v]=t;
    t++;
    for (int i=0; i<matrix[v].size(); i++){
        if (matrix[v][i].second==p) continue;
        if (used[matrix[v][i].first]) tup[v]=min(tup[v], tin[matrix[v][i].first]);
        else{
            dfs(matrix[v][i].first, matrix[v][i].second);
            tup[v]=min(tup[v], tup[matrix[v][i].first]);
            if (tup[matrix[v][i].first] > tin[v]) bridges[matrix[v][i].second]=true;
        }
    }
}
void makedfs(){
    for (int i=0; i<n; i++)
        if (!used[i]) dfs(i, -1);
}

void makecolor(int v, int color){
    ans[v]=color;
    for (int i=0; i<matrix[v].size(); i++){
        if (ans[matrix[v][i].first]==0){
            if (bridges[matrix[v][i].second]){
                    maxans++;
                    makecolor(matrix[v][i].first, maxans);
            }
            else{
                makecolor(matrix[v][i].first, color);
            }
        }
    }
}

void makeans(){
    for (int i=0; i<n; i++){
        if (ans[i]==0){
            maxans++;
            makecolor(i, maxans);
        }
    }
}

int main(){
    cin>>n>>m;
    matrix.resize(n);
    tin.resize(n);
    tup.resize(n);
    used.resize(n, false);
    bridges.resize(m, false);
    ans.resize(n, 0);
    for (int i=0; i<m; i++){
        int x, y;
        cin>>x>>y;
        x--; y--;
        matrix[x].push_back(make_pair(y, i));
        matrix[y].push_back(make_pair(x, i));
    }
    t=0;
    makedfs();
    maxans=0;
    makeans();
    cout<<maxans<<endl;
    for (int i=0; i<n; i++) cout<<ans[i]<<" ";
    return 0;
}

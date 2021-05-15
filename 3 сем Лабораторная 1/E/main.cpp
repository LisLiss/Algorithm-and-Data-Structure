#include <bits/stdc++.h>

using namespace std;
int n, m;
vector <vector <pair <int, int> > > matrix;
vector <bool> used, vis;
vector <int> tin, tup, ans;
int t, maxans;

void dfs(int v, int p){
    used[v]=true;
    tin[v]=t;
    tup[v]=t;
    t++;
    int child=0;
    for (int i=0; i<matrix[v].size(); i++){
        if (matrix[v][i].first==p) continue;
        if (used[matrix[v][i].first]) tup[v]=min(tup[v], tin[matrix[v][i].first]);
        else{
            child++;
            dfs(matrix[v][i].first, v);
            tup[v]=min(tup[v], tup[matrix[v][i].first]);
            //if (p!=-1 && tup[matrix[v][i]] >= tin[v]) ans[v]=true;
        }
    }
    //if (p==-1 && child>1) ans[v]=true;
}
void makedfs(){
    for (int i=0; i<n; i++)
        if (!used[i]) dfs(i, -1);
}

void makecolor(int v, int color, int p){
    vis[v]=true;
    for (int i=0; i<matrix[v].size(); i++){
        if (matrix[v][i].first==p) continue;
        if (!vis[matrix[v][i].first]){
            if (tup[matrix[v][i].first]>= tin [v]){
                maxans++;
                //cout<<maxans<<endl;
                ans[matrix[v][i].second]=maxans;
                makecolor(matrix[v][i].first, maxans, v);
            }
            else {
                ans[matrix[v][i].second]=color;
                makecolor(matrix[v][i].first, color, v);
            }
        }
        else{
            if (tin[v] > tin[matrix[v][i].first]){
                ans[matrix[v][i].second]=color;
            }
        }
    }
}

void makeans(){
    for (int i=0; i<n; i++){
        if (vis[i]==false){
            makecolor(i, maxans, -1);
           // maxans++;
        }
    }
}

int main(){
    cin>>n>>m;
    matrix.resize(n);
    tin.resize(n);
    tup.resize(n);
    used.resize(n, false);
    vis.resize(n, false);
    ans.resize(m, 0);
    vector <pair <int, int> > edge;
    for (int i=0; i<m; i++){
        int x, y;
        cin>>x>>y;
        x--; y--;
        edge.push_back(make_pair(x, y));
        matrix[x].push_back(make_pair(y, i));
        matrix[y].push_back(make_pair(x, i));
    }
    t=0;
    makedfs();
    maxans=0;
    makeans();
    for (int i=0; i<m; i++) {
        if (ans[i]==0){
            for (int j=0; j<matrix[edge[i].first].size(); j++) {
                if (edge[i].second == matrix[edge[i].first][j].first && ans[matrix[edge[i].first][j].second]!=0){
                    ans[i]=ans[matrix[edge[i].first][j].second];
                }
            }
        }
    }
    cout<<maxans<<endl;
    for (int i=0; i<m; i++) cout<<ans[i]<<" ";
    return 0;
}

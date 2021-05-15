#include <bits/stdc++.h>

using namespace std;
vector <int> sizeTree, ansC;
vector <vector <int> > matrix;

int dfs(int v, int x){
    int ans=1;
    for (int i=0; i<matrix[v].size(); i++){
        if (matrix[v][i]!=x) ans+=dfs(matrix[v][i], v);
    }
    sizeTree[v]=ans;
    return ans;
}

int centroid(int v){
    dfs(v, v);
    int sizeV=sizeTree[v];
    int x=v;
    while (true){
        bool f =true;
        for (int i=0; i<matrix[v].size(); i++){
            if (matrix[v][i]!=x){
                if (sizeTree[matrix[v][i]]>sizeV/2){
                    x=v; v=matrix[v][i];
                    f=false; break;
                }
            }
        }
        if (f) break;
    }
    return v;
}

void makeAnswer(int v, int x){
    int y=centroid(v);
    ansC[y]=x;
    queue<int> q;
    for (int i=0; i<matrix[y].size(); i++) q.push(matrix[y][i]);
    matrix[y].clear();
    while (!q.empty()){
        int i=q.front(); q.pop();
        for (int j=0; j<matrix[i].size(); j++){
            if (matrix[i][j]==y) {matrix[i].erase(matrix[i].begin()+j); break;}
        }
        makeAnswer(i, y);
    }
}

int main(){
    int n, x, y;
    cin>>n;
    sizeTree.resize(n);
    ansC.resize(n);
    matrix.resize(n);
    for (int i=0; i<n-1; i++){
        cin>>x>>y;
        x--; y--;
        matrix[x].push_back(y);
        matrix[y].push_back(x);
    }
    makeAnswer(0, -1);
    for (int i=0; i<n; i++){
        cout<<ansC[i]+1<<" ";
    }
    return 0;
}

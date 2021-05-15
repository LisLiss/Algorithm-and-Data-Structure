#include <bits/stdc++.h>

using namespace std;

int n, r;
vector <vector <int> > matrix;
vector <int> pmatrix, grandi, help;
vector <pair <int, int> > edge;

inline void dfs(int v, int p){
    pmatrix[v]=p;
    for (int i=0; i<matrix[v].size(); i++){
        if (matrix[v][i]==p) continue;
        dfs(matrix[v][i], v);
        grandi[v] ^= (grandi[matrix[v][i]]+1);
    }
}

int main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    scanf("%d", &n); scanf("%d", &r);
    r--;
    matrix.resize(n);
    pmatrix.resize(n);
    grandi.resize(n, 0);

    for (int i=0; i<n-1; i++){
        int x, y;
        scanf("%d", &x); scanf("%d", &y);
        x--; y--;
        matrix[x].push_back(y);
        matrix[y].push_back(x);
        edge.push_back(make_pair(x, y));
        help.push_back(i);
    }
    dfs(r, -1);
    if (grandi[r]==0){
        printf("2");
        return 0;
    }
    //random_device rd;
    //mt19937 g(rd());
    random_shuffle(help.begin(), help.end());
    printf("1\n");
    for (int i=0; i<n-1; i++){
        int p = edge[help[i]].first;
        int v = edge[help[i]].second;
        if (v==pmatrix[p]) swap(p, v);
        int ans=grandi[p] ^ (grandi[v]+1);
        while (p!=-1){
            v=p;
            p=pmatrix[p];
            if (p==-1) break;
            ans = grandi[p] ^ (grandi[v] + 1) ^ (ans + 1);
        }
        if (ans==0) {
            help[i]++;
            printf("%d", help[i]);
            return 0;
        }
    }
    return 0;
}

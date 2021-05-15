#include <bits/stdc++.h>

using namespace std;

struct edge{
    long long  f, t;
    long long w;
};

vector <edge> matrix;
vector <bool> used;
long long  nn;

void dfs(long long  x){
    used[x]=true;
    for (long long  i=0; i<matrix.size(); i++){
        if (matrix[i].f==x && !used[matrix[i].t]) dfs(matrix[i].t);
    }
}

long long mst(vector <edge> edges, long long  n, long long  root){
    long long ans=0;
    vector<bool> cycle(n, false);
    vector <long long > cmp(n, 0);
    vector <edge> dopmatrix;
    edge help; help.f=-1; help.t=-1; help.w=LLONG_MAX;
    vector <edge> minW(n, help);
    used.clear(); used.resize(n, false);
    for (edge i : edges){
        if (minW[i.t].w>i.w){
            minW[i.t]=i;
        }
    }
    help.t=root; help.w=0;
    minW[root]=help;
    long long  numComp=0;
    for (long long  i=0; i<n; i++){
        if (used[i]) continue;
        vector <long long > path;
        long long  j=i;
        while (j!=-1){
            if (used[j]) break;
            used[j]=true;
            path.push_back(j);
            j=minW[j].f;
        }
        bool f=false;
        for (long long  k : path){
            cmp[k]=numComp;
            if (k==j){
                f=true;
                cycle[numComp]=true;
            }
            if (!f) numComp++;
        }
        if (f) numComp++;
    }
    if (n!=numComp){
        for (long long  i=0; i<n; i++){
            if (cycle[cmp[minW[i].t]]) ans+=minW[i].w;
        }
        for (edge i: edges){
            if (cmp[i.f]==cmp[i.t]) continue;
            if (!cycle[cmp[i.t]]){
                edge help1; help1.f=cmp[i.f]; help1.t=cmp[i.t]; help1.w=i.w;
                dopmatrix.push_back(help1);
            } else{
                edge help1; help1.f=cmp[i.f]; help1.t=cmp[i.t]; help1.w=i.w-minW[i.t].w;
                dopmatrix.push_back(help1);
            }
        }
        return ans + mst(dopmatrix, numComp, cmp[root]);
    }
    for (long long  i=0; i<n; i++){
        ans+=minW[i].w;
    }
    return ans;
}

void make(){
    long long m, x, y;
    long long z;
    cin>>nn>>m;
    used.resize(nn, false);
    for (long long  i=0; i<m; i++){
        cin>>x>>y>>z;
        x--; y--;
        if (x!=y){
            bool wasxy=false;
            for (edge j: matrix){
                if (j.f==x && j.t==y) {j.w=min(j.w, z); wasxy=true;}
            }
            if (!wasxy){
                edge help; help.f=x; help.t=y; help.w=z;
                matrix.push_back(help);
            }
        }
    }
}
int  main()
{
    make();
    dfs(0);
    for (long long  i=0; i<nn; i++){
        if (!used[i]){
            cout<<"NO";
            return 0;
        }
    }
    cout<<"YES"<<endl<<mst(matrix, nn, 0);
    return 0;
}

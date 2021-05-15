#include <bits/stdc++.h>

using namespace std;


struct edge {
    long long f, t;
    long long cap, flow;
    bool r;
};

long long n, s, t, m, inf;
vector <long long> d, ptr, q;
vector <vector <long long> > matrix;
vector <edge> edges;
vector <vector <char> > table;

void add(long long f, long long t, long long cap, long long capt){
    matrix[f].push_back(edges.size());
    matrix[t].push_back(edges.size()+1);
    edge a; a.f=f; a.t=t; a.cap=cap; a.flow=0;a.r=true;
    edge b; b.f=t; b.t=f; b.cap=capt; b.flow=0;b.r=false;
    edges.push_back(a);
    edges.push_back(b);
}


bool bfs(){
    long long qh=0;
    long long qt=1;
    q[0]=s;
    d.resize(0);
    d.resize(t+1, inf);
    d[s]=0;
    while (qh<qt){
        long long v=q[qh];
        qh++;
        for (long long i=0; i<matrix[v].size(); i++){
            if (d[edges[matrix[v][i]].t]==inf){
                if (edges[matrix[v][i]].flow<edges[matrix[v][i]].cap){
                    q[qt]=edges[matrix[v][i]].t;
                    qt++;
                    d[edges[matrix[v][i]].t]=d[v]+1;
                }
            }
        }
    }
    return d[t]!=inf;
}

long long dfs(long long v, long long flow){
    if (flow==0) return 0;
    if (v==t) return flow;
    while (ptr[v]<matrix[v].size()){
        if (d[edges[matrix[v][ptr[v]]].t]==d[v]+1){
            long long help=dfs(edges[matrix[v][ptr[v]]].t, min(edges[matrix[v][ptr[v]]].cap-edges[matrix[v][ptr[v]]].flow, flow));
            if (help!=0){
                edges[matrix[v][ptr[v]]].flow+=help;
                edges[matrix[v][ptr[v]]^1].flow-=help;
                /*if (edges[matrix[v][ptr[v]]].r){
                    edges[matrix[v][ptr[v]]+1].flow-=help;
                } else{
                    edges[matrix[v][ptr[v]]-1].flow-=help;
                }*/
                return help;
            }
        }
        ptr[v]++;
    }
    return 0;
}

long long dinic(){
    long long ans=0;
    while (true){
        if (bfs()==false) break;
        ptr.resize(0);
        ptr.resize(1+t, 0);
        while (true){
            long long help=dfs(s, inf);
            ans+=help;
            if (help==0) break;

        }
    }
    return ans;
}

int main(){
    inf=1e9;
    cin>>n>>m;
    matrix.resize(n*m*2+2);
    table.resize(n, vector<char> (m));
    q.resize(1e6);
    s=0; t=n*m*2+1;
     for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            char c;
            cin>>c;
            table[i][j]=c;
        }
    }
    /*
    A 0
    B 1
    - 2
    . 3
    # 4
    */
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            char c=table[i][j];
            if (c!='#'){
                int help = (i*m+j+1)*2;
                if (c=='.'){
                    add(help-1, help, 1, 0);
                } else{
                    if (c=='A'){
                        add(0, help-1, inf, 0);
                    } else {
                        if (c=='B'){
                            add(help, 2*n*m+1, inf, 0);
                        }
                    }
                    add(help-1, help, inf, 0);
                }
                if (i>0 && table[i-1][j]!='#'){
                    add(help, help-2*m-1, inf, 0);
                }
                if (j>0 && table[i][j-1]!='#'){
                    add(help, help-3, inf, 0);
                }
                if (i<n-1 && table[i+1][j]!='#'){
                    add(help, help + 2*m -1, inf, 0);
                }
                if (j<m-1 && table[i][j+1]!='#'){
                    add(help, help+1, inf, 0);
                }
            }
        }
    }
    long long ans=dinic();
    if (ans>n){
        cout<<"-1";
        return 0;
    }
    for (int i=0; i<matrix.size(); i++){
        if (d[i]!=inf){
            bool flag=false;
            for (int j=0; j<matrix[i].size(); j++){
                if (d[edges[matrix[i][j]].t]==inf){
                    if (edges[matrix[i][j]].flow==edges[matrix[i][j]].cap){
                        flag=edges[matrix[i][j]].cap;
                        if (flag) break;
                    }
                }
            }
            if (flag && table[(i-1)/2/m][((i-1)/2)%m]=='.'){
                table[(i-1)/2/m][((i-1)/2)%m]='+';
            }
        }
    }
    cout<<ans<<endl;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cout<<table[i][j];
        }
        cout<<endl;
    }
    return 0;
}

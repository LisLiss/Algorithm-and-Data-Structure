#include <bits/stdc++.h>

using namespace std;


struct edge {
    int f, t;
    int cap, flow;
    bool r;
};

int n, s, t;
vector <int> d, ptr, q;
vector <vector <int> > matrix;
vector <edge> edges;

void add(int f, int t, int cap){
    matrix[f].push_back(edges.size());
    matrix[t].push_back(edges.size()+1);
    edge a; a.f=f; a.t=t; a.cap=cap; a.flow=0;a.r=true;
    edge b; b.f=t; b.t=f; b.cap=cap; b.flow=0;b.r=false;
    edges.push_back(a);
    edges.push_back(b);
}

bool bfs(){
    int qh=0;
    int qt=1;
    q[0]=s;
    d.resize(0);
    d.resize(n, -1);
    d[s]=0;
    while (qh<qt && d[t]==-1){
        int v=q[qh];
        qh++;
        for (int i=0; i<matrix[v].size(); i++){
            if (d[edges[matrix[v][i]].t]==-1){
                if (edges[matrix[v][i]].flow<edges[matrix[v][i]].cap){
                    q[qt]=edges[matrix[v][i]].t;
                    qt++;
                    d[edges[matrix[v][i]].t]=d[v]+1;
                }
            }
        }
    }
    return d[t]!=-1;
}

int dfs(int v, int flow){
    if (flow==0) return 0;
    if (v==t) return flow;
    while (ptr[v]<matrix[v].size()){
        if (d[edges[matrix[v][ptr[v]]].t]==d[v]+1){
            int help=dfs(edges[matrix[v][ptr[v]]].t, min(edges[matrix[v][ptr[v]]].cap-edges[matrix[v][ptr[v]]].flow, flow));
            if (help!=0){
                edges[matrix[v][ptr[v]]].flow+=help;
                if (edges[matrix[v][ptr[v]]].r){
                    edges[matrix[v][ptr[v]]+1].flow-=help;
                } else{
                    edges[matrix[v][ptr[v]]-1].flow-=help;
                }
                return help;
            }
        }
        ptr[v]++;
    }
    return 0;
}

int dinic(){
    int ans=0;
    while (true){
        if (bfs()==false) break;
        ptr.resize(0);
        ptr.resize(n, 0);
        while (true){
            int help=dfs(s, 1e9);
            ans+=help;
            if (help==0) break;

        }
    }
    return ans;
}

vector <bool> was;
void dfs2(int v){
    if (was[v]==false){
        was[v]=true;
        for (int i=0; i<matrix[v].size(); i++){
            if (edges[matrix[v][i]].flow<edges[matrix[v][i]].cap){
                dfs2(edges[matrix[v][i]].t);
            }
        }
    }
}

int main(){
    cin>>n;
    s=0; t=n-1;
    matrix.resize(n);
    q.resize(1e5);
    int m;
    cin>>m;
    for (int i=0; i<m; i++){
        int f, t, cap;
        cin>>f>>t>>cap;
        f--; t--;
        add(f, t, cap);
    }
    int ans=dinic();
    vector <int> ansEdge;
    was.resize(n, false);
    dfs2(0);
    for (int i=0; i<2*m; i+=2){
        int from=edges[i].f;
        int to=edges[i].t;
        if (was[from]!=was[to]){
            ansEdge.push_back(i/2);
        }
    }
    cout<<ansEdge.size()<<" "<<ans<<endl;
    for (int i=0; i<ansEdge.size(); i++){
        cout<<ansEdge[i]+1<<" ";
    }
    return 0;
}

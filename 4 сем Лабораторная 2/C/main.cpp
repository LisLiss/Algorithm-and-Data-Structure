#include <bits/stdc++.h>

using namespace std;


struct edge {
    long long f, t;
    long long cap, flow;
    bool r;
};

long long n, s, t;
vector <long long> d, ptr, q;
vector <vector <long long> > matrix;
vector <edge> edges;

void add(long long f, long long t, long long cap){
    matrix[f].push_back(edges.size());
    matrix[t].push_back(edges.size()+1);
    edge a; a.f=f; a.t=t; a.cap=cap; a.flow=0;a.r=true;
    edge b; b.f=t; b.t=f; b.cap=0; b.flow=0;b.r=false;
    edges.push_back(a);
    edges.push_back(b);
}

bool bfs(){
    long long qh=0;
    long long qt=1;
    q[0]=s;
    d.resize(0);
    d.resize(n, -1);
    d[s]=0;
    while (qh<qt && d[t]==-1){
        long long v=q[qh];
        qh++;
        for (long long i=0; i<matrix[v].size(); i++){
            if (d[edges[matrix[v][i]].t]==-1){
                if (edges[matrix[v][i]].flow<edges[matrix[v][i]].cap){
                    q[qt]=edges[matrix[v][i]].t;
                    qt++;
                    d[edges[matrix[v][i]].t]=d[v]+1;
                }
            }
        }
    }
    //cout<<d[t]<<endl;
    return d[t]!=-1;
}

long long dfs(long long v, long long flow){
    if (flow==0) return 0;
    if (v==t) return flow;
    while (ptr[v]<matrix[v].size()){
        if (d[edges[matrix[v][ptr[v]]].t]==d[v]+1){
            long long help=dfs(edges[matrix[v][ptr[v]]].t, min(edges[matrix[v][ptr[v]]].cap-edges[matrix[v][ptr[v]]].flow, flow));
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

long long dinic(){
    long long ans=0;
    while (true){
        if (bfs()==false) break;
        ptr.resize(0);
        ptr.resize(n, 0);
        while (true){
            long long help=dfs(s, 1e9);
            ans+=help;
            if (help==0) break;

        }
    }
    return ans;
}

vector <bool> was, wasE;
vector<long long> ans1, ans2;
bool dfs(long long v){
    if (v==t) {
        ans1.push_back(v);
        return true;
    }
    was[v]=true;
        for (long long i=0; i<matrix[v].size(); i++){
            if (edges[matrix[v][i]].flow==1 && wasE[matrix[v][i]]==false && was[edges[matrix[v][i]].t]==false){
                if (dfs(edges[matrix[v][i]].t)==true){
                    ans1.push_back(v);
                    wasE[matrix[v][i]]=true;
                    return true;
                }
            }
        }
    return false;
}

bool dfs2(long long v){
    if (v==t) {
        ans2.push_back(v);
        return true;
    }
    was[v]=true;
        for (long long i=0; i<matrix[v].size(); i++){
            if (edges[matrix[v][i]].flow==1 && wasE[matrix[v][i]]==false && was[edges[matrix[v][i]].t]==false){
                if (dfs2(edges[matrix[v][i]].t)==true){
                    ans2.push_back(v);
                    wasE[matrix[v][i]]=true;
                    return true;
                }
            }
        }
    return false;
}

int main(){
    long long m;
    cin>>n>>m>>s>>t;
    s--; t--;
    matrix.resize(n);
    q.resize(1e6);
    for (long long i=0; i<m; i++){
        long long f, t;
        cin>>f>>t;
        f--; t--;
        add(f, t, 1);
    }
    //cout<<"uih";
    long long ans=dinic();
    if (ans>=2) cout<<"YES"<<endl;
    else {
        cout<<"NO";
        return 0;
    }
    was.resize(n, false);
    wasE.resize(2*m, false);
    dfs(s);
    was.resize(0);
    was.resize(n, false);
    dfs2(s);
    for (long long i=0; i<ans1.size(); i++) cout<<ans1[ans1.size()-i-1]+1<<" ";
    cout<<endl;
    for (long long i=0; i<ans2.size(); i++) cout<<ans2[ans2.size()-i-1]+1<<" ";

    return 0;
}

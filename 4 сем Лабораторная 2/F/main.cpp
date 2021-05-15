#include <bits/stdc++.h>

using namespace std;


struct edge {
    long long f, t;
    long long cap, flow;
    bool r;
};

long long n, s, t, numv;
vector <long long> d, ptr, q;
vector <vector <long long> > matrix;
vector <edge> edges;

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
    d.resize(numv, -1);
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
        ptr.resize(numv, 0);
        while (true){
            long long help=dfs(s, 1e9);
            ans+=help;
            if (help==0) break;

        }
    }
    return ans;
}

int main(){

    cin>>n;
    s=n; t=n+1; numv=n+2;
    matrix.resize(1e5);
    q.resize(1e6);
    vector <int> points(n, 0);
    vector <vector <char> > table(n, vector <char> (n));
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            char c;
            cin>>c;
            table[i][j]=c;
            if (i>j) continue;
            if (c=='#') continue;
            if (c=='W'){
                points[i]-=3;
            }
            if (c=='w'){
                points[i]-=2;
                points[j]-=1;
            }
            if (c=='L'){
                points[j]-=3;
            }
            if (c=='l'){
                points[j]-=2;
                points[i]-=1;
            }
            if (c=='.'){
                add(i, numv, 3, 3);
                add(j, numv, 3, 3);
                numv++;
            }
        }
    }
    for (int i=0; i<n; i++){
        int k;
        cin>>k;
        points[i]+=k;
    }
    for (int i=n+2; i<numv; i++){
        add(s, i, 3, 0);
    }
    for (int i=0; i<n; i++){
        add(i, t, points[i], 0);
    }
    long long ans=dinic();
    for (int i=n+2; i<numv; i++){
        edge first=edges[matrix[i][0]];
        edge second=edges[matrix[i][1]];
        if (first.flow==3){
            table[first.t][second.t]='W';
            table[second.t][first.t]='L';
        }
        if (first.flow==2){
            table[first.t][second.t]='w';
            table[second.t][first.t]='l';
        }
        if (first.flow==1){
            table[first.t][second.t]='l';
            table[second.t][first.t]='w';
        }
        if (first.flow==0){
            table[first.t][second.t]='L';
            table[second.t][first.t]='W';
        }
    }
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            cout<<table[i][j];
        }
        cout<<endl;
    }
    return 0;
}

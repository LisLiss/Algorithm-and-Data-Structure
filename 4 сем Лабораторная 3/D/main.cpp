#include <bits/stdc++.h>

using namespace std;


struct edge {
    long long f, t, cap, price, flow, s;
   // bool r;
};
const long long inf =1e10;
long long n,m,k,st,tt;
vector <vector <long long> > matrix;
vector<long long> p,d,ind;
vector <edge> edges;

void add(long long f, long long t, long long cap, long long price){
    edge a; a.f=f; a.t=t; a.cap=cap; a.flow=0; a.price=price; a.s=edges.size()+1;
    edge b; b.f=t; b.t=f; b.cap=0; b.flow=0; b.price=-price; b.s=edges.size();
    edges.push_back(a);
    edges.push_back(b);
    matrix[edges[edges.size() - 1].f].push_back(edges.size() - 1);
    matrix[edges[edges.size() - 2].f].push_back(edges.size() - 2);
}

void res(){
    ind.resize(0);
    ind.resize(2*n+2,0);
    d.resize(0);
    d.resize(2*n+2, inf);
    p.resize(0);
    p.resize(2*n+2, inf);
}
priority_queue<pair<long long, long long> > q;
long long dinic(){
    long long flow=0, cost=0;
    while (true){
        res();
        q.push(make_pair(0, st));
        d[st]=0;
        while (!q.empty()){
            long long v=q.top().second;
            q.pop();
            while (!q.empty()){
                if (q.top().first==-d[q.top().second]) break;
                q.pop();
            }
            for (long long i=0; i<matrix[v].size(); i++){
                if (d[v]<inf && edges[matrix[v][i]].flow<edges[matrix[v][i]].cap){
                    if (d[v]+edges[matrix[v][i]].price < d[edges[matrix[v][i]].t]){
                        d[edges[matrix[v][i]].t]=d[v]+edges[matrix[v][i]].price;
                        p[edges[matrix[v][i]].t]=matrix[v][i];
                        q.push(make_pair(-d[edges[matrix[v][i]].t], edges[matrix[v][i]].t));
                    }
                }
            }
        }
        if (d[tt]==inf) break;
        long long help=k;
        long long i=tt;
        while (p[i] != inf) {
            help = min(help, edges[p[i]].cap-edges[p[i]].flow);
            i = edges[p[i]].f;
        }
        i=tt;
        while (p[i] != inf) {
            edges[p[i]].flow += help;
            long long rev = edges[p[i]].s;
            edges[rev].flow -= help;
            cost += help * edges[p[i]].price;
            i = edges[p[i]].f;
        }
    }
    return cost;
}
int main(){
    cin>>n>>m;
    k=inf;
    st=0; tt=2*n+1;
    matrix.resize(2*n+2);
    int helpind=1;
    for (int i=0; i<n; i++){
        int x;
        cin>>x;
        add(helpind, helpind+1, n, x);
        add(0, helpind, 1, 0);
        add(helpind+1, tt, 1, 0);
        add(helpind+1, helpind, n, 0);
        helpind+=2;
    }
    for (long long i=0; i<m; i++){
        long long f, tt, price;
        cin>>f>>tt>>price;
        f=f*2-1; tt*=2;
        add(f, tt, n, price);
    }
    long long ans=dinic();
    cout<<ans;
    return 0;
}

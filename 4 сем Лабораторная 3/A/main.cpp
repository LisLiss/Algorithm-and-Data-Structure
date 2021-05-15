#include <bits/stdc++.h>

using namespace std;


struct edge {
    long long f, t, cap, price, flow, s;
   // bool r;
};

long long n,m,k;//,s,t;
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
    ind.resize(n,0);
    d.resize(0);
    d.resize(n, 1e10);
    p.resize(0);
    p.resize(n, 1e10);
}
deque<long long> q;
long long dinic(){
    long long flow=0, cost=0;
    while (true){
        res();
        q.push_back(0);
        d[0]=0;
        while (!q.empty()){
            long long v=q.front();
            q.pop_front();
            ind[v]=1;
            for (long long i=0; i<matrix[v].size(); i++){
                if (d[v]<1e10 && edges[matrix[v][i]].flow<edges[matrix[v][i]].cap){
                    if (d[v]+edges[matrix[v][i]].price < d[edges[matrix[v][i]].t]){
                        d[edges[matrix[v][i]].t]=d[v]+edges[matrix[v][i]].price;
                        p[edges[matrix[v][i]].t]=matrix[v][i];
                        if (ind[edges[matrix[v][i]].t]==0){
                            q.push_back(edges[matrix[v][i]].t);
                        } else{
                            if (ind[edges[matrix[v][i]].t]==1){
                                q.push_front(edges[matrix[v][i]].t);
                            }
                        }
                        ind[edges[matrix[v][i]].t]=1;
                    }
                }
            }
        }
        if (d[n-1]==1e10) break;
        long long help=k;
        long long i=n-1;
        while (p[i] != 1e10) {
            help = min(help, edges[p[i]].cap-edges[p[i]].flow);
            i = edges[p[i]].f;
        }
        i=n-1;
        while (p[i] != 1e10) {
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
    k=1e10;
    matrix.resize(n);
    for (long long i=0; i<m; i++){
        long long f, tt, cap, price;
        cin>>f>>tt>>cap>>price;
        f--; tt--;
        add(f, tt, cap, price);
    }
    long long ans=dinic();
    cout<<ans;
    return 0;
}

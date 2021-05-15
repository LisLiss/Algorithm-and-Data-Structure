#include <bits/stdc++.h>

using namespace std;


struct edge {
    int f, t, cap, price, flow, s;
   // bool r;
};
const int inf =1e19;
int n,m,k,st,tt;
vector <vector <int> > matrix;
vector<int> p,d,ind;
vector <edge> edges;

void add(int f, int t, int cap, int price){
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
set<pair<int, int> > q;
int dinic(){
    int flow=0, cost=0;
    while (true){
        res();
        q.insert(make_pair(0, st));
        d[st]=0;
        while (!q.empty()){
            int v=(*q.begin()).second;
            q.erase(q.begin());
            /*while (!q.empty()){
                if (q.top().first==-d[q.top().second]) break;
                q.pop();
            }*/
            for (int i=0; i<matrix[v].size(); i++){
                if (d[v]<inf && edges[matrix[v][i]].flow<edges[matrix[v][i]].cap){
                    if (d[v]+edges[matrix[v][i]].price < d[edges[matrix[v][i]].t]){
                        q.erase(make_pair(d[edges[matrix[v][i]].t], edges[matrix[v][i]].t));
                        d[edges[matrix[v][i]].t]=d[v]+edges[matrix[v][i]].price;
                        p[edges[matrix[v][i]].t]=matrix[v][i];
                        q.insert(make_pair(d[edges[matrix[v][i]].t], edges[matrix[v][i]].t));
                    }
                }
            }
        }
        if (d[tt]==inf) break;
        int help=k;
        int i=tt;
        while (p[i] != inf) {
            help = min(help, edges[p[i]].cap-edges[p[i]].flow);
            i = edges[p[i]].f;
        }
        i=tt;
        while (p[i] != inf) {
            edges[p[i]].flow += help;
            int rev = edges[p[i]].s;
            edges[rev].flow -= help;
            cost += help * edges[p[i]].price;
            i = edges[p[i]].f;
        }
    }
    return cost;
}
int main(){
    cin>>n;
    k=inf;
    st=0; tt=2*n+1;
    matrix.resize(2*n+2);
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            int x;
            cin>>x;
            add(i+1, j+n+1, 1, x);
        }
    }
    for (int i=1; i<n+1; i++){
        add(st, i, 1, 0);
        add(i+n, tt, 1, 0);
    }
    int ans=dinic();
    cout<<ans<<endl;
    for (int i=1; i<n+1; i++){
        for (int j=0; j<matrix[i].size(); j++){
            if (edges[matrix[i][j]].flow==1){
                cout<<i<<" "<<edges[matrix[i][j]].t-n<<endl;
                break;
            }
        }
    }
    return 0;
}

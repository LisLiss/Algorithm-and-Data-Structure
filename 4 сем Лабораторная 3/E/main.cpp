#include <bits/stdc++.h>

using namespace std;


struct edge {
    int f, t, cap, price, flow, s, num;
   // bool r;
};
const int inf =1e19;
int n,m,k,st,tt;
vector <vector <int> > matrix;
vector<int> p,d,ind;
vector <edge> edges;

void add(int f, int t, int cap, int price, int num){
    edge a; a.f=f; a.t=t; a.cap=cap; a.flow=0; a.price=price; a.s=edges.size()+1;
    edge b; b.f=t; b.t=f; b.cap=0; b.flow=0; b.price=-price; b.s=edges.size();
    a.num=num; b.num=num;
    edges.push_back(a);
    edges.push_back(b);
    matrix[t].push_back(edges.size() - 1);
    matrix[f].push_back(edges.size() - 2);
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

pair<int, int> dinic(){
    int flow=0, cost=0;
    while (flow<k){
        res();
        q.insert(make_pair(0, st));
        d[st]=0;
        while (!q.empty()){
            int v=(*q.begin()).second;
            q.erase(q.begin());
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
        int help=k-flow;
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
        flow+=help;
    }
    return make_pair(flow, cost);
}
vector <int> ans;
vector <bool> was, wasv;
bool dfs(int v, edge now){
    if (v==tt){
        //ans.push_back(now.num);
        return true;
    }
    for (int i=0; i<matrix[v].size(); i++){
        if (was[edges[matrix[v][i]].num]==false && edges[matrix[v][i]].flow>0 && edges[matrix[v][i]].flow==edges[matrix[v][i]].cap){
            if (wasv[edges[matrix[v][i]].t]==false){
                if (dfs(edges[matrix[v][i]].t, edges[matrix[v][i]])){
                    ans.push_back(edges[matrix[v][i]].num);
                    was[edges[matrix[v][i]].num]=true;
                    return true;
                }
            }
        }
    }
    return false;
}

int main(){
    cin>>n>>m>>k;
    st=0; tt=n-1;
    matrix.resize(n);
    for (int i=0; i<m; i++){
        int ff, tt, price;
        cin>>ff>>tt>>price;
        ff--; tt--;
        add(ff, tt, 1, price, i);
        add(tt, ff, 1, price, i);
    }

    pair<int, int> anss=dinic();
    if (anss.first<k){
        cout<<"-1";
        return 0;
    }
    //anss.second=13;
    cout<<fixed<<setprecision(5);
    cout<<((double) anss.second)/k<<endl;
    was.resize(m, false);
    for (int i=0; i<k; i++){
        ans.resize(0);
        wasv.resize(0);
        wasv.resize(n, false);
        edge a;
        dfs(0, a);
        cout<<ans.size()<<" ";
        for (int i=ans.size()-1; i>-1; i--){
            cout<<ans[i]+1<<" ";
        }
        cout<<endl;
    }

    return 0;
}

#include <bits/stdc++.h>

using namespace std;


struct edge {
    long long f, t;
    long long cap, flow;
    bool r;
};

long long n, s, t, m, inf, k, timeNow, maxL;
vector <long long> d, ptr, q;
vector <vector <long long> > matrix;
vector <edge> edges;
vector <vector <pair<long long, long long> > > paths;

void add(long long f, long long t, long long cap, long long capt){
    //cout<<"was"<<endl;
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
    d.resize(1e7, -1);
    d[s]=0;
    while (qh<qt && d[t]==-1){
            //cout<<"kkk";
        long long v=q[qh];
        qh++;
        for (long long i=0; i<matrix[v].size(); i++){
            if (d[edges[matrix[v][i]].t]==-1){
                if (edges[matrix[v][i]].flow<edges[matrix[v][i]].cap && (edges[matrix[v][i]].t % (maxL+1)<=timeNow)){
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
            if (edges[matrix[v][ptr[v]]].flow<edges[matrix[v][ptr[v]]].cap && (edges[matrix[v][ptr[v]]].t % (maxL+1) <=timeNow)){
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
        ptr.resize(1e7, 0);
        while (true){
            long long help=dfs(s, 1e9);
            ans+=help;
            if (help==0) break;

        }
    }
    return ans;
}


void dfsTwo(long long v, long long i){
    for (long long i=0; i<matrix[v].size(); i++){
        edge nowEdge= edges[matrix[v][i]];
        if (nowEdge.flow==1 && nowEdge.cap==1){
            nowEdge.flow=0;
            paths[i].push_back(make_pair(nowEdge.t/(maxL+1)+1, nowEdge.f/(maxL+1)+1));
            dfsTwo(nowEdge.t, i);
            break;
        } else{
            if(nowEdge.flow!=0 && nowEdge.cap>1){
                paths[i].push_back(make_pair(-1, nowEdge.f/(maxL+1)+1));
                dfsTwo(nowEdge.t, i);
            }
        }
    }
}

int main(){
    inf=1e9;
    long long ss, tt;
    cin>>n>>m>>k>>ss>>tt;
    ss--; tt--;
    matrix.resize(1e6);
    q.resize(1e6);
    timeNow=inf;
    for (long long i=0; i<m; i++){
        long long x, y;
        cin>>x>>y;
        x--; y--;
        add(x, y, 1, 1);
    }
    if (ss==tt || k==0){
        cout<<"0";
        return 0;
    }
    maxL=inf;
    s=ss; t=tt;
    bfs();
    maxL=d[t]+k-1;
    //cout<<maxL;
    for (long long i=0; i<2*m; i+=2){
        for (long long j=0; j<maxL; j++){
            //cout<<"jj"<<endl;
            add(edges[i/2].f*(maxL+1)+i/2, edges[i/2].t*(maxL+1)+i/2+1, 1, 0);
            add(edges[i/2].t*(maxL+1)+i/2, edges[i/2].f*(maxL+1)+i/2+1, 1, 0);
        }
    }
    for (long long i=0; i<n; i++){
        for (long long j=0; j<maxL; j++){
            add(i*(maxL+1)+j, i*(maxL+1)+j+1, inf, 0);
        }
    }
   for (long long i=0; i<k; i++){
        long long now=maxL-k+1+i;
       // cout<<now<<endl;
        s=ss*(maxL+1); t=tt*(maxL+1)+now; timeNow=now;
        for (int kk=0; kk<edges.size(); kk++) edges[kk].flow=0;
        long long ans=dinic();
        cout<<ans<<endl;
        if (ans>=k){
            cout<<now<<endl;
            paths.resize(k);
            for (long long j=0; j<k; j++){
                //dfsTwo(ss*(maxL+1), j);
            }
            int help=1;
            /*while (help!=0){
                help=0;
                for (long long one=0; one<k; one++){
                    for (long long two=one+1; two<k; two++){
                        for (long long j=1; j<now; j++){
                            if (paths[one][j].second==paths[two][j].first && paths[two][j].second==paths[one][j].first){
                                help++;
                                vector <pair <long long, long long> > first;
                                for (long long qqq=0; qqq<j; qqq++) first.push_back(paths[one][qqq]);
                                first.push_back(make_pair(-1, paths[one][j].second));
                                for (long long qqq=j+1; qqq<paths[two].size(); qqq++) first.push_back(paths[two][qqq]);
                                paths[one]=first;
                                vector <pair <long long, long long> > second;
                                for (long long qqq=0; qqq<j; qqq++) second.push_back(paths[two][qqq]);
                                second.push_back(make_pair(-1, paths[two][j].second));
                                for (long long qqq=j+1; qqq<paths[one].size(); qqq++) second.push_back(paths[one][qqq]);
                                paths[two]=second;
                            }
                        }
                    }
                }
            }*/

        /*for (int ll=0; ll<paths.size(); ll++){
            for (int kk=0; kk<paths[ll].size(); kk++){
                cout<<paths[ll][kk].first<<" "<<paths[ll][kk].second<<" ";
            }
            cout<<endl;
        }
        /*for (long long j=0; j<now; j++){
            long long numday=0;
            for (long long one=0; one<k; one++){
                //if (paths[one].size()>j && paths[one][j].first!=-1){
                    numday++;
                //}
            }
           /* cout<<numday<<" ";
            for (long long one=0; one<k; one++){
                if (paths[one].size()>j && paths[one][j].first!=-1){
                    cout<<one+1<<" "<<paths[one][j].first<<" ";
                }
            }*/
        //    cout<<endl;
        return 0;
        }
    }
    return 0;
}

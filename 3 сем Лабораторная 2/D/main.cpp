#include <bits/stdc++.h>

using namespace std;

struct e {
    int x, y, w;
};

int main()
{
    int n, m, k, s, inf=1e8;
    cin>>n>>m>>k>>s;
    s--;
    vector <e> edges;
    for (int i=0; i<m; i++){
        int x, y, w;
        cin>>x>>y>>w; x--; y--;
        e help; help.x=x; help.y=y; help.w=w;
        edges.push_back(help);
    }
    vector <vector <int> > d(k+1, vector <int> (n, inf));
    d[0][s]=0;
    for (int i=0; i<k; i++){
        for (e j:edges){
            int help;
            //cout<<j.x<<" "<<j.y<<" "<<j.w<<endl;
            if (d[i][j.x]==-inf) help=-inf;
            else if (j.w == -inf) help=-inf;
            else if (d[i][j.x]==inf) help=inf;
            else if (j.w==inf) help=inf;
            else help=d[i][j.x]+j.w;
            //cout<<help<<endl;
            d[i+1][j.y]=min(d[i+1][j.y], help);
        }
    }
    for (int i=0; i<n; i++){
        if (d[k][i]!=inf && d[k][i]!=-inf) cout<<d[k][i];
        else cout<<"-1";
        cout<<endl;
    }
    return 0;
}

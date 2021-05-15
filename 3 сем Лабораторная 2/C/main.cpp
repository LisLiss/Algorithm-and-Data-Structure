#include <bits/stdc++.h>

using namespace std;

struct e {
    int x, y, w;
};

int main()
{
    int n, m, inf=1e8;
    cin>>n;
    vector <e> edges;
    vector <int> d(n), p(n, -1);
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            int w;
            cin>>w;
            e help; help.x=i; help.y=j; help.w=w;
            if (w!=100000) edges.push_back(help);
        }
    }
    m=edges.size();
    int now;
    for (int i=0; i<n; i++){
        now=-1;
        for (int j=0; j<m; j++){
            if (d[edges[j].y] > d[edges[j].x] + edges[j].w){
                d[edges[j].y] = max (-inf, d[edges[j].x] + edges[j].w);
                p[edges[j].y]=edges[j].x;
                now=edges[j].y;
            }
        }
    }
    if (now==-1){
        cout<<"NO";
        return 0;
    }
    for (int i=0; i<n; i++){
        now=p[now];
    }
    vector <int> ans;
    for (int i=now; ; i=p[i]){
        if (i==now && ans.size()>1) break;
        ans.push_back(i);
    }
    cout<<"YES"<<endl<<ans.size()<<endl;
    for (int i=ans.size()-1; i>-1; i--) cout<<ans[i]+1<<" ";
    return 0;
}

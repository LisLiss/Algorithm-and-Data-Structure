#include <bits/stdc++.h>

using namespace std;
vector <vector <int> > dp, child, minn;
vector <int> d, p;
vector <bool> del;
int n, m;
int inf =1e6+10;
int logTop(int n){
    int i=0;
    while (n>=1){
        n=n/2;
        i++;
    }
    return i;
}

int getAlive(int v){
    if (del[v]==false) return v;
    p[v]=getAlive(p[v]);
    return p[v];
}

int lca(int a, int b){
    int ans;
    if (d[a]>d[b]) swap (a, b);
    int h=d[b]-d[a];
    for (int i=m; i>=0; i--){
        if (pow (2, i)<=h){
            h-=pow(2, i);
            b=dp[b][i];
        }
    }
    if (a==b) return getAlive(a);
    for (int i=m; i>=0; i--){
        if (dp[a][i]!=dp[b][i]){
            a=dp[a][i];
            b=dp[b][i];
        }
    }
    return getAlive(dp[a][0]);
}
void add(int v, int parent){
    p[v]=parent;
    d[v]=d[parent]+1;
    dp[v][0]=p[v];
    for (int i=1; i<m; i++){
        dp[v][i]=dp[dp[v][i-1]][i-1];
    }
}

void deleting(int v){
    del[v]=true;
}

int main()
{
    cin>>n;
    m=logTop(n)+1;
    dp.resize(n+1, vector <int> (m+1, 0));
    minn.resize(n+1, vector <int> (m+1, inf));
    child.resize(n+1);
    dp[1][0]=0;
    p.resize(n+1, 0);
    d.resize(n+1, 0);
    del.resize(n+1, false);
    p[1]=1;
    char c;
    int next=2;
    for (int i=0; i<n; i++){
        cin>>c;
        if (c=='+'){
            int x;
            cin>>x;
            add(next,x);
            next++;
        }
        if (c=='-'){
            int x;
            cin>>x;
            deleting(x);
        }
        if (c=='?'){
            int x, y;
            cin>>x>>y;
            cout<<lca(x, y)<<endl;
        }
    }
    return 0;
}

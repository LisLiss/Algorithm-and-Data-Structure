#include <bits/stdc++.h>

using namespace std;
vector <vector <int> > dp, child;
vector <int> d, p;
int n, m;
int logTop(int n){
    int i=0;
    while (n>=1){
        n=n/2;
        i++;
    }
    return i;
}
int lca(int a, int b){
    if (d[a]>d[b]) swap (a, b);
    int h=d[b]-d[a];
    for (int i=m; i>=0; i--){
        if (pow (2, i)<=h){
            h-=pow(2, i);
            b=dp[b][i];
        }
    } if (a==b) return a;
    for (int i=m; i>=0; i--){
        if (dp[a][i]!=dp[b][i]){
            a=dp[a][i];
            b=dp[b][i];
        }
    }
    if (p[a]==0) return 1;
    return p[a];
}
void depth(int v, int x){
    d[v]=x;
    for (int i=0; i<child[v].size(); i++) depth(child[v][i], x+1);
}
int main()
{
    cin>>n;
    m=logTop(n)+1;
    dp.resize(n+1, vector <int> (m+1, 0));
    child.resize(n+1);
    dp[1][0]=0;
    p.resize(n+1, 0);
    d.resize(n+1, 0);
    p[1]=1;
    for (int i=2; i<n+1; i++) {
        cin>>dp[i][0];
        p[i]=dp[i][0];
        child[dp[i][0]].push_back(i);
    }

    for (int j=1; j<m+1; j++){
        for (int i=1; i<n+1; i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
        }
    }

    depth(1, 0);
    int k;
    cin>>k;
    for (int i=0; i<k; i++){
        int a, b;
        cin>>a>>b;
        cout<<lca(a, b)<<endl;
    }
    return 0;
}

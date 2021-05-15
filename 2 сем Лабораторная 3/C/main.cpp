#include <bits/stdc++.h>

using namespace std;
vector <vector <int> > dp, child, minn;
vector <int> d, p;
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
int lca(int a, int b){
    int ans=inf;
    int ansp=-10;
    if (d[a]>d[b]) swap (a, b);
    int h=d[b]-d[a];
    for (int i=m; i>=0; i--){
        if (pow (2, i)<=h){
            h-=pow(2, i);
            ans=min(ans, minn[b][i]);
            b=dp[b][i];
        }
    }
    if (a==b) ansp=a;
    for (int i=m; i>=0; i--){
        if (dp[a][i]!=dp[b][i]){
            ans=min(min(minn[a][i], minn[b][i]), ans);
            a=dp[a][i];
            b=dp[b][i];
        }
    }
    if (ansp==-10)
        return min(ans, min(minn[a][0], minn[b][0]));
    return ans;
}
void depth(int v, int x){
    d[v]=x;
    for (int i=0; i<child[v].size(); i++) depth(child[v][i], x+1);
}
int main()
{
    ifstream f1("minonpath.in");
    ofstream f2("minonpath.out");
    f1>>n;
    m=logTop(n)+1;
    dp.resize(n+1, vector <int> (m+1, 0));
    minn.resize(n+1, vector <int> (m+1, inf));
    child.resize(n+1);
    dp[1][0]=0;
    p.resize(n+1, 0);
    d.resize(n+1, 0);
    p[1]=1;
    for (int i=2; i<n+1; i++) {
        f1>>dp[i][0];
        f1>>minn[i][0];
        p[i]=dp[i][0];
        child[dp[i][0]].push_back(i);
    }

    for (int j=1; j<m+1; j++){
        for (int i=1; i<n+1; i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
            minn[i][j]=min(minn[i][j-1], minn[dp[i][j-1]][j-1]);
            if (dp[i][j]==0) minn[i][j]=inf;
        }
    }
    depth(1, 0);
    int k;
    f1>>k;
    for (int i=0; i<k; i++){
        int a, b;
        f1>>a>>b;
        f2<<lca(a, b)<<endl;
    }
    return 0;
}

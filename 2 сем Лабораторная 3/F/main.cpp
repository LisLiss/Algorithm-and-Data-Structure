#include <bits/stdc++.h>

using namespace std;
vector <vector <int> > dp, child;
vector <int> d, p, timeT;
vector <int> pow2;
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
        if (pow2[i]<=h){
            h-=pow2[i];
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
int timeHelp=0;
void depth(int v, int x){
    d[v]=x;
    timeT[v]=timeHelp;
    timeHelp++;
    for (int i=0; i<child[v].size(); i++) depth(child[v][i], x+1);
}

bool cmp(int x, int y){
    return timeT[x]<timeT[y];
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n;
    m=logTop(n)+1;
    for (int i=0; i<m+5; i++) pow2.push_back(1<<i);
    dp.resize(n+1, vector <int> (m+1, 0));
    child.resize(n+1);
    dp[1][0]=0;
    p.resize(n+1, 0);
    d.resize(n+1, 0);
    timeT.resize(n+1, 0);
    int root;
    for (int i=1; i<n+1; i++) {
        cin>>dp[i][0];
        if (dp[i][0]==-1) {
            dp[i][0]=0; root=i; p[i]=0; continue;}
        p[i]=dp[i][0];
        child[dp[i][0]].push_back(i);
    }

    for (int j=1; j<m+1; j++){
        for (int i=1; i<n+1; i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
        }
    }

    depth(root, 0);
    int k, s;
    cin>>k;
    vector <int> group;
    for (int i=0; i<k; i++){
        cin>>s;
        group.clear(); group.resize(s+1);
        group[0]=root;
        for (int j=0; j<s; j++) cin>>group[j+1];
        sort(group.begin(), group.end(), cmp);
        int ans=0;
        for (int j=1; j<s+1; j++) ans+=d[group[j]]-d[lca(group[j-1], group[j])];
        cout<<ans+1<<"\n";
    }

    return 0;
}

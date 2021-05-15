#include <bits/stdc++.h>

using namespace std;
vector <vector <int> > dp;
int n, m;
int logTop(int n){
    int i=0;
    while (n>=1){
        n=n/2;
        i++;
    }
    return i;
}
int main()
{
    cin>>n;
    m=logTop(n)+1;
    dp.resize(n+1, vector <int> (m+1, 0));
    for (int i=1; i<n+1; i++) {
        cin>>dp[i][0];
       // if (dp[i][0]==0) dp[i][0]=i;
    }
    for (int j=1; j<m+1; j++){
        for (int i=1; i<n+1; i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
        }
    }
    for (int i=1; i<n+1; i++){
        cout<<i<<": ";
        for (int j=0; j<m+1; j++){
            if (dp[i][j]!=0) cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}

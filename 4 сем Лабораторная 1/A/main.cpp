#include <bits/stdc++.h>

using namespace std;

vector <vector <long long> > matrix;
vector <bool> used;
vector <long long> mt;

bool dfs(long long v){
    if (!used[v]){
        used[v]=true;
        for (long long i=0; i<matrix[v].size(); i++){
            if ((mt[matrix[v][i]]==-1) || (dfs(mt[matrix[v][i]]))){
                mt[matrix[v][i]]=v;
                return true;
            }
        }
        return false;
    }
    return false;
}

int main(){
    long long n, m;
    cin>>n>>m;
    matrix.resize(n);
    for (long long i=0; i<n; i++){
        long long c;
        cin>>c;
        while (c!=0){
            c--;
            matrix[i].push_back(c);
            cin>>c;
        }
    }
    mt.resize(m, -1);
    for (long long i=0; i<n; i++){
        used.resize(0);
        used.resize(n, false);
        dfs(i);
    }
    long long ans=0;
    for (long long i=0; i<m; i++){
        if (mt[i]!=-1) ans++;
    }
    cout<<ans<<endl;
    for (long long i=0; i<m; i++){
        if (mt[i]!=-1) cout<<mt[i]+1<<" "<<i+1<<endl;
    }
    return 0;
}

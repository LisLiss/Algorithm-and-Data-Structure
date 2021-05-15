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
    ifstream f1("dominoes.in");
    ofstream f2("dominoes.out");

    long long a, b, n, m, numzv=0;
    f1>>n>>m>>a>>b;
    vector < vector <char> > cmat(n, vector <char> (m));
    for (long long i=0; i<n; i++){
        for (long long j=0; j<m; j++){
            f1>>cmat[i][j];
            if (cmat[i][j]=='*') numzv++;
        }
    }
    if (a>=2*b){
        f2<<numzv*b;
        return 0;
    }
    matrix.resize(n*m);
    for (long long i=0; i<n; i++){
        for (long long j=0; j<m; j++){
            if (((i+j)%2==0) &&(cmat[i][j]=='*')){
                if (i>0) if (cmat[i-1][j]=='*') matrix[i*m+j].push_back((i-1)*m+j);
                if (j>0) if (cmat[i][j-1]=='*') matrix[i*m+j].push_back(i*m+j-1);
                if (i<n-1) if (cmat[i+1][j]=='*') matrix[i*m+j].push_back((i+1)*m+j);
                if (j<m-1) if (cmat[i][j+1]=='*') matrix[i*m+j].push_back(i*m+j+1);
            }
        }
    }
    mt.resize(n*m, -1);
    for (long long i=0; i<n*m; i++){
        used.resize(0);
        used.resize(n*m, false);
        dfs(i);
    }
    long long ans=0;
    for (long long i=0; i<n*m; i++){
        if (mt[i]!=-1) ans++;
    }
    f2<<ans*a+(numzv-2*ans)*b<<endl;
    return 0;
}

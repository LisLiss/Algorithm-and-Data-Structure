#include <bits/stdc++.h>

using namespace std;

vector <vector <int> > matrix;
vector <bool> used;
vector <int> mt;

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
    ifstream f1("ufo.in");
    ofstream f2("ufo.out");
    int M, v;
    f1>>M>>v;
    vector <int> left(M), right(M);
    vector <pair<int, int>> from(M), to(M);
    for (int i=0; i<M; i++){
        char c;
        int mi=0;
        f1>>c; mi=(c-'0')*10;
        f1>>c; mi+=(c-'0');
        mi*=60;
        f1>>c;
        f1>>c; mi+=(c-'0')*10;
        f1>>c; mi+=(c-'0');
        right[i]=mi;
        int a, b;
        f1>>a>>b;
        from[i].first=a;
        from[i].second=b;
        to[i].first=a;
        to[i].second=b;
        left[i]=right[i];
    }
    matrix.resize(M);
    for (int i=0; i<M; i++){
        for (int j=0; j<M; j++){
            if (i==j) continue;
            if ((left[i]+pow(((to[i].first-from[j].first)*(to[i].first-from[j].first)+ (to[i].second-from[j].second)*(to[i].second-from[j].second)), 0.5)*60/v)<=right[j]){
                matrix[i].push_back(j);
            }
        }
    }
    mt.resize(M, -1);
    for (long long i=0; i<M; i++){
        used.resize(0);
        used.resize(M, false);
        dfs(i);
    }
    long long ans=0;
    for (long long i=0; i<M; i++){
        if (mt[i]!=-1) ans++;
    }
    f2<<M-ans;
    return 0;
}

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
    ifstream f1("taxi.in");
    ofstream f2("taxi.out");
    int M;
    f1>>M;
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
        int a, b, cc, d;
        f1>>a>>b>>cc>>d;
        from[i].first=a;
        from[i].second=b;
        to[i].first=cc;
        to[i].second=d;
        left[i]=mi+(abs(a-cc)+abs(b-d));
    }
    matrix.resize(M);
    for (int i=0; i<M; i++){
        for (int j=0; j<M; j++){
            if (i==j) continue;
            if ((left[i]+abs(to[i].first-from[j].first)+abs(to[i].second-from[j].second))<(right[j])){
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

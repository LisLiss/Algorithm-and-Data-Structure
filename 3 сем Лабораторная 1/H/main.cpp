#include <bits/stdc++.h>

using namespace std;

int n;
vector <vector <long long> > matrix, trmatrix;
vector <bool> used, revused;
long long nowbak;

void dfs(int v){
    used[v]=true;
    for (int i=0; i<n; i++){
        if (matrix[v][i]<=nowbak && !used[i]) dfs(i);
    }
}

void trdfs(int v){
    revused[v]=true;
    for (int i=0; i<n; i++){
        if (trmatrix[v][i]<=nowbak && !revused[i]) trdfs(i);
    }
}

void rip(){
    used.clear();
    revused.clear();
    used.resize(n, false);
    revused.resize(n, false);
}
bool check(){
    dfs(0);
    trdfs(0);
    for (int i=0; i<n; i++){
        if (!used[i] || !revused[i]) {
            rip();
            return false;
        }
    }
    rip();
    return true;
}

int main(){
    ifstream f1("avia.in");
    ofstream f2("avia.out");
    f1>>n;
    matrix.resize(n, vector <long long> (n));
    trmatrix.resize(n, vector <long long> (n));
    used.resize(n, false);
    revused.resize(n, false);
    set<long long> bak;

    int x;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            f1>>x;
            matrix[i][j]=x;
            trmatrix[j][i]=x;
            bak.insert(x);
        }
    }
    vector <long long> a;
    nowbak=0;
    for (auto i : bak) a.push_back(i);
    int l=-1, r=a.size();
    while (l<r-1){
        long long m=l+(r-l)/2;
        nowbak=a[m];
        if (check()) r=m;
        else l=m;
    }
    nowbak=a[r];
    f2<<nowbak;
    f1.close();
    f2.close();
}

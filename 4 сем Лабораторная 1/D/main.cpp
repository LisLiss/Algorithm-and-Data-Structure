#include <bits/stdc++.h>

using namespace std;

vector <vector <long long> > matrix;
vector <bool> used;
vector <long long> mt;
vector <vector <bool> > was;
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

void maxCov(int v, int num){
    if (!was[num][v]){
        was[num][v]=true;
        if (num==1){
            if (mt[v]!=-1) maxCov(mt[v], 0);
        } else {
            for (int i=0; i<matrix[v].size(); i++){
                if (mt[matrix[v][i]]!=v) maxCov(matrix[v][i], 1);
            }
        }
    }
}

int main(){
    ifstream f1("birthday.in");
    ofstream f2("birthday.out");
    int k, n, m;
    f1>>k;
    for (int i=0; i<k; i++){
        matrix.resize(0);
        mt.resize(0);
        used.resize(0);
        was.resize(0);
        f1>>n>>m;
        vector <vector <bool> > matrixRev(n, vector <bool> (m, true));
        for (long long i=0; i<n; i++){
            long long c;
            f1>>c;
            while (c!=0){
                c--;
                matrixRev[i][c]=false;
                f1>>c;
            }
        }
        matrix.resize(n);
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                if (matrixRev[i][j]) {
                    matrix[i].push_back(j);
                }
            }
        }
        mt.resize(m, -1);
        for (long long i=0; i<n; i++){
            used.resize(0);
            used.resize(n, false);
            dfs(i);
        }
        was.resize(2);
        was[0].resize(n, false);
        was[1].resize(m, false);
        vector <bool> wasMT(n, false);
        for (int i=0; i<m; i++){
            if (mt[i]!=-1) wasMT[mt[i]]=true;
        }
        for (int i=0; i<n; i++){
            if (!was[0][i] && !wasMT[i]) maxCov(i, 0);
        }
        vector <vector <int> > ansWas(2);
        for (int i=0; i<n; i++){
            if (was[0][i]) ansWas[0].push_back(i+1);
        }
        for (int i=0; i<m; i++){
            if (!was[1][i]) ansWas[1].push_back(i+1);
        }
        f2<<ansWas[0].size()+ansWas[1].size()<<endl;
        f2<<ansWas[0].size()<<" "<<ansWas[1].size()<<endl;
        for (int i=0; i<ansWas[0].size(); i++) f2<<ansWas[0][i]<<" ";
        f2<<endl;
        for (int i=0; i<ansWas[1].size(); i++) f2<<ansWas[1][i]<<" ";
        f2<<endl<<endl;
    }
    return 0;
}

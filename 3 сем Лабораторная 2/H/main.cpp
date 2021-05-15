    #include <bits/stdc++.h>

    using namespace std;
    int n, m, s;
    vector <vector <int> > matrix, rematrix;
    vector <bool> win, lose, was;
    vector <int> degree;

    void dfsplay(int v){
        was[v]=true;
        for (int i: rematrix[v]){
            if (!was[i]){
                if (lose[v]) win[i]=true;
                else if  (--degree[i]==0) lose[i]=true;
                else continue;
                dfsplay(i);
            }
        }
    }

    int main(){
        ifstream f1 ("game.in");
        ofstream f2 ("game.out");
        f1>>n>>m>>s;

        matrix.resize(n);
        rematrix.resize(n);
        was.resize(n, false);
        win.resize(n, false);
        lose.resize(n, false);
        degree.resize(n, 0);

        for (int i=0; i<m; i++){
            int x, y;
            f1>>x>>y;
            x--; y--;
            matrix[x].push_back(y);
            rematrix[y].push_back(x);
            degree[y]++;
        }
        for (int i=0; i<n; i++){
            if (matrix[i].size()==0) {
                lose[i]=true;
            }
        }

        for (int i=0; i<n; i++){
            if (matrix[i].size()==0 && !was[i]) {
                dfsplay(i);
            }
        }
        if (win[s-1]) f2<<"First player wins";
        else f2<<"Second player wins";
        return 0;
    }

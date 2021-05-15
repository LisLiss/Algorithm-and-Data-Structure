    #include <bits/stdc++.h>

    using namespace std;
    int n, m;
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
        while (cin>>n>>m){
            matrix.clear();
            rematrix.clear();
            was.clear();
            win.clear();
            lose.clear();
            degree.clear();

            matrix.resize(n);
            rematrix.resize(n);
            was.resize(n, false);
            win.resize(n, false);
            lose.resize(n, false);
            degree.resize(n, 0);

            for (int i=0; i<m; i++){
                int x, y;
                cin>>x>>y;
                x--; y--;
                matrix[x].push_back(y);
                rematrix[y].push_back(x);
                degree[x]++;
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

            for (int i=0; i<n; i++){
                if (!was[i]) cout<<"DRAW";
                else{
                if (win[i]) cout<<"FIRST";
                else if (lose[i]) cout<<"SECOND";
                }
                //else cout<<"DRAW";
                cout<<endl;
            }
            cout<<endl;
        }
        return 0;
    }

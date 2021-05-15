#include <bits/stdc++.h>

using namespace std;
vector <bool> was;
vector <vector <bool> > graf, grafrev;
vector <int> ord, numcomp;
int n, m;

void dfs(int v){
    was[v]=true;
    for (int i=0; i<2*n; i++){
        if (!graf[v][i]) continue;
        if (!was[i]) dfs(i);
    }
    ord.push_back(v);
}

void dfstwo(int v, int c){
    numcomp[v]=c;
    for (int i=0; i<2*n; i++){
        if (!grafrev[v][i]) continue;
        if (numcomp[i]==-1) dfstwo(i, c);
    }
}
int main(){
    cin>>n>>m;
    graf.resize(2*n, vector <bool> (2*n, false));
    grafrev.resize(2*n, vector <bool> (2*n, false));
    string s, xs, ys;
    map <string,int> names;
    for (int i=0; i<n; i++) {
        cin>>s;
        names[s]=i;
    }
    int x, y;
    for (int i=0; i<m; i++){
        cin>>xs>>s>>ys;
        x=names.find(xs.substr(1))->second;
        y=names.find(ys.substr(1))->second;
        if (xs[0]=='+'){
            if (ys[0]=='+'){
                graf[x][y]=true;
                graf[y+n][x+n]=true;
                grafrev[y][x]=true;
                grafrev[x+n][y+n]=true;
            }
            else{
                graf[x][y+n]=true;
                graf[y][x+n]=true;
                grafrev[y+n][x]=true;
                grafrev[x+n][y]=true;
            }
        }
        else{
            if (ys[0]=='+'){
                graf[x+n][y]=true;
                graf[y+n][x]=true;
                grafrev[y][x+n]=true;
                grafrev[x][y+n]=true;
            }
            else{
                graf[x+n][y+n]=true;
                graf[y][x]=true;
                grafrev[y+n][x+n]=true;
                grafrev[x][y]=true;
            }
        }
    }
    numcomp.resize(2*n, -1);
    was.resize(2*n, false);
    for (int i=0; i<2*n; i++){
        if (!was[i]) dfs(i);
    }
    int c=0;
    for (int i=0; i<2*n; i++){
        if (numcomp[ord[2*n-i-1]]==-1){
            dfstwo(ord[2*n-i-1], c++);
        }
    }
    for (int i=0; i<n; i++){
        if (numcomp[i]==numcomp[i+n]){
            cout<<"-1";
            return 0;
        }
    }
    vector <int> ans;
    for (int i=0; i<n; i++){
        if (numcomp[i]>numcomp[i+n]){
            ans.push_back(i);
        }
    }
    cout<<ans.size()<<endl;
    for (int i=0; i<ans.size(); i++){
        for (auto j : names){
            if (j.second==ans[i]) cout<<j.first<<endl;
        }
    }
    return 0;
}

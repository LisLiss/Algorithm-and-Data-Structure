#include <bits/stdc++.h>

using namespace std;

vector <int> p;
vector <int> d;
vector <int> zn;

int get(int x){
    int ans = zn[x];
    while (x!=p[x]){
        ans+=d[x];
        x=p[x];
    }
    ans+=d[x];
    return ans;
}
int getp(int x){
    while (x!=p[x]){
        x=p[x];
    }
    return x;
}

void add(int x, int v){
    x=getp(x);
    d[x]+=v;
}

void join(int x, int y){
    x=getp(x);
    y=getp(y);
    if (x!=y){
        p[x]=y;
        d[x]-=d[y];
    }
}

int main(){
    int n, m;
    cin>>n;
    p.resize(n+1);
    d.resize(n+1, 0);
    zn.resize(n+1, 0);
    for (int i=1; i<n+1; i++){
        p[i]=i;
    }
    cin>>m;
    string s;
    for (int i=0; i<m; i++){
        cin>>s;
        if (s=="add"){
            int x, y;
            cin>>x>>y;
            add(x,y);
        }
        if (s=="join"){
            int x, y;
            cin>>x>>y;
            join(x,y);
        }
        if (s=="get"){
            int x;
            cin>>x;
            cout<<get(x)<<endl;
        }
    }
    return 0;
}

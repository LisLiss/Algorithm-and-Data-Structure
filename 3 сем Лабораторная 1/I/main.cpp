#include <bits/stdc++.h>

using namespace std;
int n;
double ans;
vector <int> x, y;

double matrix(int i, int j){
    return sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}

vector <bool> used;
vector <double> minedge;

void prim(){
    for (int i=0; i<n; i++){
        int minv=-1;
        for (int j=0; j<n; j++){
            if (used[j]) continue;
            if (minv==-1){
                minv=j;
                continue;
            }
            if (minedge[j]<minedge[minv]) minv=j;
        }
        ans+=minedge[minv];
        used[minv]=true;
        for (int i=0; i<n; i++){
            double dist=matrix(minv,i);
            if (dist<minedge[i]){
                minedge[i]=dist;
            }
        }
    }
}

int main(){
    cin>>n;
    x.resize(n);
    y.resize(n);
    used.resize(n, false);
    minedge.resize(n, 1e9);
    minedge[0]=0;
    ans=0;
    for (int i=0; i<n; i++){
        cin>>x[i]>>y[i];
    }
    prim();
    cout<<ans;
    return 0;
}

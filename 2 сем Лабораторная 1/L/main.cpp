#include <bits/stdc++.h>

using namespace std;
#define ll long long

vector <vector <vector <ll> > > tree;
ll n;
ll sum(ll x, ll y, ll z){
    ll ans=0;
    for (ll i=x; i>-1; i=(i&(i+1))-1){
        for (ll j=y; j>-1; j=(j&(j+1))-1){
            for (ll k=z; k>-1; k=(k&(k+1))-1){
                ans+=tree[i][j][k];
            }
        }
    }
    return ans;
}

void add(ll x, ll y, ll z, ll d){
    for (ll i=x; i<n; i=(i|(i+1))){
        for (ll j=y; j<n; j=(j|(j+1))){
            for (ll k=z; k<n; k=(k|(k+1))){
                tree[i][j][k]+=d;
            }
        }
    }
}

ll ans(ll x1, ll y1, ll z1, ll x2, ll y2, ll z2){
    ll answer=sum(x2, y2, z2);
    if (x1!=0) answer-=sum(x1-1, y2, z2);
    if (y1!=0) answer-=sum(x2, y1-1, z2);
    if (z1!=0) answer-=sum(x2, y2, z1-1);
    if (x1!=0 && y1!=0) answer+=sum(x1-1, y1-1, z2);
    if (x1!=0 && z1!=0) answer+=sum(x1-1, y2, z1-1);
    if (y1!=0 && z1!=0) answer+=sum(x2, y1-1, z1-1);
    if (x1!=0 && y1!=0 && z1!=0) answer-=sum(x1-1,y1-1,z1-1);
    return answer;
}


int main()
{
    cin>>n;//
    tree.resize (n);
    for (ll i=0; i<n; i++){
        tree[i].resize(n, vector <ll>(n, 0));
    }
    int c;
    ll x1, x2, y1, y2, z1, z2, k;
    cin>>c;
    while(c!=3){
        if (c==1){
            cin>>x1>>y1>>z1>>k;
            add(x1, y1, z1, k);
        } else{
            cin>>x1>>y1>>z1>>x2>>y2>>z2;
            cout<<ans(x1,y1,z1,x2,y2,z2)<<endl;
        }
        cin>>c;
    }
    return 0;
}

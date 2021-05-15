#include <bits/stdc++.h>

using namespace std;

#define ll long long

ll logg(ll x){
    if (x==1) return 0;
    else return logg(x/2)+1;
}
ll n;
vector <vector<ll> > table;

int main()
{
    ll m, a0, u, v;
    cin>>n>>m>>a0>>u>>v;
    vector <ll> a(n), logi(n);
    table.resize(n, vector <ll> (logg(n)+1));
    a[0]=a0;
    for (ll i=1; i<n; i++){
        a[i]=(23*a[i-1]+21563)%16714589;
    }
    ll htable=logg(n)+1;
    for (ll j=0; j<htable; j++){
        for (ll i=0; i<n; i++){
            if (j==0) table[i][j]=a[i];
            else
            if ((i+pow(2,j-1))<n){
                table[i][j]=min(table[i][j-1], table[i+pow(2,j-1)][j-1]);
            }
        }
    }
    for (ll i=0; i<n; i++){
        logi[i]=logg(i+1);
    }
    ll help, l, r, ans;
    for (ll i=1; i<m+1; i++){
        l=min(u,v)-1;
        r=max(v,u)-1;
        help = logi[r-l];
        ans=min(table[l][help],table[r-pow(2,help)+1][help]);
        if (i!=m){
            u=((17*u+751+ans+2*i)%n)+1;
            v=((13*v+593+ans+5*i)%n)+1;
        }
    }
    cout<<u<<" "<<v<<" "<<ans<<endl;
    return 0;
}

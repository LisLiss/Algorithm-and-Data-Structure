#include <bits/stdc++.h>

using namespace std;
#define ll long long
vector <int> a;

ll bin_search_min(ll x){
    ll l=-1, r=a.size(), m;
    while (r>l+1){
        m=l+(r-l)/2;
        if (a[m]<=x){
            l=m;
        }
        else{
            r=m;
        }
    }
    if ((r<a.size()) && (a[r]<=x)) return r;
    return l;
}
ll bin_search_max(ll x){
    ll l=-1, r=a.size(), m;
    while (r>l+1){
        m=l+(r-l)/2;
        if (a[m]<x){
            l=m;
        }
        else{
            r=m;
        }
    }
    if ((r<a.size())&& (a[r]==x)) return r;
    if ((l>-1) && (a[l]>=x)) return l;
    return r;
}

int main()
{
    ll n, k, x, l, r;
    cin>>n>>k;
    for (ll i=0; i<n; i++){
        cin>>x;
        a.push_back(x);
    }
    for (ll i=0; i<k; i++){
        cin>>x;
        l=bin_search_min(x);
        r=bin_search_max(x);
        if (abs(a[l]-x)<abs(a[r]-x)){
            cout<<a[l]<<endl;
        }
        else{
            if (abs(a[l]-x)>abs(a[r]-x)){
                cout<<a[r]<<endl;
            }
            else{
                cout<<min(a[l], a[r])<<endl;
            }
        }
    }
    return 0;
}

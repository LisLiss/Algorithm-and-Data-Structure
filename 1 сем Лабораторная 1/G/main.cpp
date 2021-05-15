#include <bits/stdc++.h>
#define ll long long

using namespace std;
ll n, h, w;
bool check(ll m){
    if (((m/w)*(m/h))<n) return true;
    return false;

}

ll bin_search(ll l, ll r){
    while (r-l>1){
        ll m=l+(r-l)/2;
        if (check(m)){
            l=m;
        }
        else{
            r=m;
        }
    }
    return r;
}
int main()
{
    cin>>w>>h>>n;
    cout<<bin_search(0, n*max(w, h));
    return 0;
}

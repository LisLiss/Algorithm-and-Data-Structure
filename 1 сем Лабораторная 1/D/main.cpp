#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector <ll> a;

void add(ll x){
    a.push_back(x);
    ll i=a.size()-1;
    while ((i>0) && (a[(i-1)/2]<a[i])){
        swap(a[i], a[(i-1)/2]);
        i=(i-1)/2;
    }
}

ll remove(){
    ll ans=a[0];
    swap(a[0], a[a.size()-1]);
    a.pop_back();
    ll i=0;
    while ((2*i+1)<a.size()){
        ll j=2*i+1;
        if (((2*i+2)<a.size()) && (a[2*i+2]>a[j])){
            j=2*i+2;
        }
        if (a[j]>a[i]){
            swap(a[i], a[j]);
            i=j;
        }
        else{
            break;
        }
    }
    return ans;
}
int main()
{
    ll n, x;
    cin>>n;
    for (ll i=0; i<n; i++){
        cin>>x;
        if (x==0){
            cin>>x;
            add(x);
        }
        else{
            cout<<remove()<<endl;
        }
    }
    return 0;
}

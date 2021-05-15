#include <bits/stdc++.h>

using namespace std;
#define ll unsigned long long
int main()
{
    ll ans=0;
    ll n, x, y, a0;
    cin>>n>>x>>y>>a0;
    vector <ll> a(n);
    a[0]=a0;
    for (int i=1; i<n; i++){
        a[i]=(x*a[i-1]+y)%(1<<16);
    }
    for (int i=1; i<n; i++){
        a[i]+=a[i-1];
    }
    ll m,z,t,b0,b1,c0,c1;
    cin>>m>>z>>t>>b0;
    b1=(z*b0+t)%(1<<30);
    for (int i=0; i<m; i++){
        c0=b0%n;
        c1=b1%n;
        if (min(c0,c1)==0){
            ans+=a[max(c0,c1)];
        }
        else{
            ans+=a[max(c0,c1)]-a[min(c0,c1)-1];
        }
        b0=(z*b1+t)%(1<<30);
        b1=(z*b0+t)%(1<<30);
    }
    cout<<ans;
    return 0;
}

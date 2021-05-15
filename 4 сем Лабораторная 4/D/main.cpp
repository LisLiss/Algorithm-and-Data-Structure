#include <bits/stdc++.h>

using namespace std;
#define ll long long

ll mul(ll x, ll y, ll m) {
    ll ans=0;
    while (y) {
        if (y&1) {
            ans = ans+x;
            ans%=m;
        }
        x = x<<1;
        x%=m;
        y=y>>1;
    }
    return ans;
}


ll bpow(ll x, ll y, ll m) {
    ll ans=1;
    while (y) {
        if (y&1) {
            ans = mul(ans, x, m);
        }
        x = mul(x, x, m);
        y=y>>1;
    }
    return ans;
}

ll phi (ll x) {
	ll ans=x;
	for (int i=2; i*i<=x; i++){
		if (x%i==0) {
			while (x%i==0) x/=i;
			ans=ans-ans/i;
		}
	}
	if (x>1){
		ans=ans-ans/x;
	}
	return ans;
}

int main() {
    ll a,b,n,m;
    cin>>a>>b>>n>>m;
    ll t=bpow(m, phi(n)-1, n);
    ll k=bpow(n, phi(m)-1, m);
    cout<<((t*a*m)%(n*m) + (k*b*n)%(n*m))%(n*m);
    return 0;
}

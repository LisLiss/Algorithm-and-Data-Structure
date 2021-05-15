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

pair <ll, ll> makepq(ll n){
    for (ll i=2; i<n+1; i++){
        if (n%i==0){
            return make_pair(i, n/i);
        }
    }
}

int main() {
    ll n,e,c;
    cin>>n>>e>>c;
    pair<ll, ll> pq = makepq(n);
    //cout<<pq.first<<" "<<pq.second<<endl;
    ll pqmin = (pq.first-1)*(pq.second-1);
    ll d = bpow(e, phi(pqmin)-1, pqmin);
    cout<<bpow(c, d, n);
    return 0;
}

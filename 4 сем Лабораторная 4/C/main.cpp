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

bool check(unsigned ll x){
    if (x==1) return false;
    if (x==2) return true;
    if (x&1){
        srand(time(nullptr));
        ll xminone=x-1;
        ll t=0;
        while (xminone%2==0){
            xminone = xminone>>1;
            t++;
        }
        unsigned ll randx, xpow;
        for (int i=0; i<10; i++){
            randx=rand()%(x-2) + 2;
            xpow=bpow(randx, xminone, x);
            if (xpow!=1 && xpow!=x-1){
                for (int j=0; j<t; j++){
                    xpow=bpow(xpow, 2, x);
                    //if (xpow == 1) return false;
                    if (xpow==x-1) break;
                }
                if (xpow==x-1) continue;
                else return false;
            }
        }
        return true;
    } else{
         return false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    unsigned ll x;
    for (int i=0; i<n; i++){
        cin>>x;
        if (check(x)) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}

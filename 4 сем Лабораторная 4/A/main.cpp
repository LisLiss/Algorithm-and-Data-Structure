#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <bool> r(2*1e7, true);
    for (int i=2; i<2*1e7; i++){
        if (!r[i]) continue;
        for (int j=i+i; j<2*1e7; j+=i){
            r[j]=false;
        }
    }
    int n, x;
    cin>>n;
    for (int i=0; i<n; i++){
        cin>>x;
        if (r[x]) cout<<"YES\n";
        else cout<<"NO\n";
    }
    return 0;
}

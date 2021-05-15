#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <int> r(1e6+1, 0);
    for (int i=2; i<1002; i++){
       // cout<<i<<endl;
        if (r[i]==0) r[i]=i;
        else continue;
        for (int j=i*i; j<1e6+1; j+=i){
            if (r[j]==0) r[j]=i;
        }
    }
    int n, x;
    cin>>n;
    for (int i=0; i<n; i++){
        cin>>x;
        if (r[x]==0) r[x]=x;
        while (x!=r[x]){
            if (r[x]==0) {
                r[x]=x;
                break;
            }
            cout<<r[x]<<" ";
            x/=r[x];
        }
        cout<<x<<"\n";
    }
    return 0;
}

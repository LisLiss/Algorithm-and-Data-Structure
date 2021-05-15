#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin>>s;
    int n=s.length();
    vector <int> z(n, 0);
    int l=0, r=0;
    for (int i=1; i<n; i++){
        if (i<=r){
            z[i]=min(r-i+1, z[i-l]);
        }
        while ((z[i]+i<n) && (s[z[i]]==s[i+z[i]])) z[i]++;
        if (r<z[i]+i-1){
            l=i;
            r=z[i]+i-1;
        }
        cout<<z[i]<<" ";
    }
    return 0;
}

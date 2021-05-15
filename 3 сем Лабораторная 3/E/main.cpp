#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s;
    cin>>s;
    int n=s.length();
    vector <int> p(n,0);
    //cout<<"0 ";
    for (int i=1; i<n; i++){
        int j=p[i-1];
        while(j>0 && s[i]!=s[j]){
            j=p[j-1];
        }
        if (s[i]==s[j]) j++;
        p[i]=j;
        //cout<<p[i]<<" ";
    }
    if (n%(n-p[n-1])==0){
        cout<<n-p[n-1];
        return 0;
    }
    cout<<n;
    return 0;
}

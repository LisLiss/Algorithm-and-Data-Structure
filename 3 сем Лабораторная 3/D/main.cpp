#include <bits/stdc++.h>

using namespace std;

int main()
{
    string t;
    string s;
    cin>>t>>s;
    s=t+"#"+s;
    int n=s.length();
    int m=t.length();
    vector <int> p(n,0);
    for (int i=1; i<n; i++){
        int j=p[i-1];
        while(j>0 && s[i]!=s[j]){
            j=p[j-1];
        }
        if (s[i]==s[j]) j++;
        p[i]=j;
    }
    vector <int> ans;
    for (int i=m+1; i<n; i++){
        if (p[i]==m){
            ans.push_back(i-2*m+1);
        }
    }
    cout<<ans.size()<<endl;
    for (int i=0; i<ans.size(); i++) cout<<ans[i]<<" ";
    return 0;
}

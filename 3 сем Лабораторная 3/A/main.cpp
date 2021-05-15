#include <bits/stdc++.h>

using namespace std;

int main()
{
    long n;
    string s;
    cin>>s;
    n=s.length();
    int easy = 31;
    vector <long long> pow(n+1), hashSub(n+1);
    pow[0]=1; hashSub[0]=0;
    for (int i=1; i<=n; i++){
        pow[i]=pow[i-1]*easy;
    }
    for (int i=1; i<=n; i++){
        hashSub[i]=hashSub[i-1]+int(s[i-1])*pow[i-1];
        //cout<<hashSub[i]<<endl;
    }
    long long k, a, b, c, d, hash1, hash2;
    cin>>k;
    for (int i=0; i<k; i++){
        cin>>a>>b>>c>>d;
        hash1=hashSub[b]-hashSub[a-1];
        hash2=hashSub[d]-hashSub[c-1];
        if (hash1*pow[c-1]==hash2*pow[a-1]) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    return 0;
}

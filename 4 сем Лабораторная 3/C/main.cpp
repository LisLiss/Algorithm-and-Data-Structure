#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long r1, s1, p1, r2, s2, p2;
    cin>>r1>>s1>>p1>>r2>>s2>>p2;
    long long ans=0;
    long long help1=s1-s2-r2;
    long long help2=r1-r2-p2;
    long long help3=p1-p2-s2;
    ans=max(ans, max(help1, max(help2, help3)));
    cout<<ans;
    return 0;
}

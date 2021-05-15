#include <bits/stdc++.h>

using namespace std;
long long parseInt(string s){
    long long ans=0;
    long long l=1;
    for (int i=s.length()-1; i>-1; i--){
        ans+=(s[i]-'0')*l;
        l*=10;
    }
    return ans;
}
int main()
{
    stack <long long> num;
    string s;
    string shelp="";
    getline(cin,s);
    int i=0;
    for (int i=0; i<s.length(); i++) {
        if (s[i]==' '){
            if (shelp.length()==0) continue;
            long long x=parseInt(shelp);
            num.push(x);
            shelp="";
            continue;
        }
        if (s[i]=='+'){
            long long a=num.top();
            num.pop();
            long long b=num.top();
            num.pop();
            num.push(a+b);
            continue;
        }
        if (s[i]=='*'){
            long long a=num.top();
            num.pop();
            long long b=num.top();
            num.pop();
            num.push(a*b);
            continue;
        }
        if (s[i]=='-'){
            long long a=num.top();
            num.pop();
            long long b=num.top();
            num.pop();
            num.push(b-a);
            continue;
        }
        if (s[i]=='/'){
            long long a=num.top();
            num.pop();
            long long b=num.top();
            num.pop();
            num.push(b/a);
            continue;
        }
        shelp+=s[i];
    }
    cout<<num.top();
    return 0;
}

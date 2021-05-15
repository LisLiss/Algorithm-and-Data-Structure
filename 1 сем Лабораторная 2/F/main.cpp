#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, mini=1, i=1;
    cin>>n;
    vector <int> a(n);
    vector <string> ans;
    string s1="push", s2="pop";
    stack<int> num;
    for (int i=0; i<n; i++){
        cin>>a[i];
    }
    //if (n==0) return 0;
    num.push(a[0]);
    ans.push_back(s1);
    while (i<n){
        if (a[i]==mini){
            ans.push_back(s1);
            ans.push_back(s2);
            i++;
            mini++;
            continue;
        }
        if (!num.empty()){
                if(num.top()==mini){
                ans.push_back(s2);
                mini++;
                num.pop();
                continue;
                }
        }
        if (a[i]>mini){
            if (num.empty()){
                num.push(a[i]);
                ans.push_back(s1);
                i++;
            } else{
                if (a[i]>num.top()){
                    cout<<"impossible";
                    return 0;
                }
                num.push(a[i]);
                ans.push_back(s1);
                i++;
            }
        }
    }
    while (!num.empty()){
        ans.push_back(s2);
        num.pop();
    }
    for (int j=0; j<ans.size(); j++){
        cout<<ans[j]<<endl;
    }
    return 0;
}

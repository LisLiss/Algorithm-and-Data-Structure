#include <bits/stdc++.h>

using namespace std;

int main()
{
    vector <int> a(101,0);
    int n;
    while (cin>>n){
        a[n]++;
    }
    for (int i=0; i<101; i++){
        for (int j=0; j<a[i]; j++){
            cout<<i<<" ";
        }
    }
    return 0;
}

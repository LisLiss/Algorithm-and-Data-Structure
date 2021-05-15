#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector <int> a;

void Merge(int left, int rigth){
        vector <int> c;
        int m=(rigth+left)/2;
        int i=left, j=m;
        while (i<m || j<rigth){
            if (j==rigth || (i<m && a[i]<a[j])){
                //cout<<a[i]<<" "<<a[j]<<endl;
                c.push_back(a[i]);
                i++;
            }
            else{
                c.push_back(a[j]);
                j++;
            }
        }
        for (int i=0; i<c.size(); i++){
            a[left]=c[i];
            left++;
        }
}
void MergeSort(int left, int right){
    if (left<right-1){
        MergeSort(left, (left+right)/2);
        MergeSort((left+right)/2, right);
        Merge(left, right);
    }
}

ll bin_search_min(ll x){
    ll l=-1, r=a.size(), m;
    while (r>l+1){
        m=l+(r-l)/2;
        if (a[m]<x){
            l=m;
        }
        else{
            r=m;
        }
    }
    return r;
}
ll bin_search_max(ll x){
    ll l=-1, r=a.size(), m;
    while (r>l+1){
        m=l+(r-l)/2;
        if (a[m]<=x){
            l=m;
        }
        else{
            r=m;
        }
    }
    return l;
}
int main()
{
    ll n, l, r;
    cin>>n;
    a.resize(n);
    for (ll i=0; i<n; i++){
        cin>>a[i];
    }
    MergeSort(0,n);
    cin>>n;
    for (ll i=0; i<n; i++){
        cin>>l>>r;
        l=bin_search_min(l);
        r=bin_search_max(r);
        cout<<r-l+1<<" ";
    }
    return 0;
}

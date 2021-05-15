#include <bits/stdc++.h>

using namespace std;

vector <long long> a;
long long ans;
void Merge(long long left, long long right){
        vector <long long> c;
        long long m=(right+left)/2;
        long long i=left, j=m;
        while (i<m || j<right){
            if (j==right || (i<m && a[i]<a[j])){
                c.push_back(a[i]);
                i++;
            }
            else{
                if ((i<m)&& (a[i]>a[j])) ans+=(m-i);
                c.push_back(a[j]);
                j++;
            }
        }
        for (int i=0; i<c.size(); i++){
            a[left]=c[i];
            left++;
        }
}
void MergeSort(long long left, long long right){
    if (left<right-1){
        MergeSort(left, (left+right)/2);
        MergeSort((left+right)/2, right);
        Merge(left, right);
    }
}

int main(){
    long long n, x;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin>>n;
    ans=0;
    for (int i=0; i<n; i++){
        cin>>x;
        a.push_back(x);
    }
    MergeSort(0,n);
    cout<<ans;
    return 0;
}

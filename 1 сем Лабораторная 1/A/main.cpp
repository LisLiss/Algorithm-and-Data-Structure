#include <bits/stdc++.h>

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

int main()
{
    int n;
    cin>>n;
    a.resize(n);
    for (int i=0; i<n; i++){
        cin>>a[i];
    }
    MergeSort(0,n);
    for (int i=0; i<n; i++){
        cout<<a[i]<<" ";
    }

    return 0;
}

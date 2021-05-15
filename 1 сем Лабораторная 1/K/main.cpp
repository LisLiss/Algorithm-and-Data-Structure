#include <bits/stdc++.h>
#define ll long long
using namespace std;

const double e=1e-7;

struct komb{
    ll v, w, i;
    double delta;
};

vector <komb> drag;
ll n, k;


bool cmd(komb a1, komb a2){
    if (a1.delta>a2.delta) return true;
    return false;
}

void Merge(int left, int rigth){
        vector <komb> c;
        int m=(rigth+left)/2;
        int i=left, j=m;
        while (i<m || j<rigth){
            if (j==rigth || (i<m && cmd(drag[i],drag[j]))){
                c.push_back(drag[i]);
                i++;
            }
            else{
                c.push_back(drag[j]);
                j++;
            }
        }
        for (int i=0; i<c.size(); i++){
            drag[left]=c[i];
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

bool check(double maxx){
    double delta=0;
    for (int i=0; i<n; i++) drag[i].delta=drag[i].v-maxx*drag[i].w;
    sort(drag.begin(), drag.end(), cmd);
    for (int i=0; i<k; i++) delta+=drag[i].delta;
    if (delta<=0) return true;
    return false;
}
void bin_search(double l, double r){
    while (r-l>e){
        double m=l+(r-l)/2;
        if (check(m)){
            r=m;
        }
        else{
            l=m;
        }
    }
}
int main(){
    ifstream f1("kbest.in");
    ofstream f2("kbest.out");
    f1>>n>>k;
    drag.resize(n);
    for (int i=0; i<n; i++){
        f1>>drag[i].v>>drag[i].w;
        drag[i].i=i+1;
    }
    bin_search(0, 10e8);
    for (int i=0; i<k; i++){
        f2<<drag[i].i<<endl;
    }
    return 0;
}

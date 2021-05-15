#include <bits/stdc++.h>

using namespace std;

const double e=1e-7;

double c;

bool check(double m){
 if ((m*m+sqrt(m)-c)<0) return true;
 return false;
}

double bin_search(double l, double r){
    while (r-l>e){
        double m=l+(r-l)/2;
        if (check(m)){
            l=m;
        }
        else{
            r=m;
        }
    }
    return r;
}
int main()
{
    cout<<fixed<<setprecision(7);
    cin>>c;
    cout<<bin_search(0, c);
    return 0;
}

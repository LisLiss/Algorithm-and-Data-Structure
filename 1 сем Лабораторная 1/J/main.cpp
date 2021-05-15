#include <bits/stdc++.h>

using namespace std;

const double e=1e-8;

double a, p, f;

double check(double m){
    return (sqrt(m*m+(1-a)*(1-a))/p+sqrt((1-m)*(1-m)+a*a)/f);
}

double ternary_search(double l, double r){
    while(r-l>e){
        double m1=l+(r-l)/3;
        double m2=r-(r-l)/3;
        if (check(m1)>check(m2)){
            l=m1;
        }
        else{
            r=m2;
        }
    }
    return r;
}
int main(){
    cin>>p>>f>>a;
    cout<<fixed<<setprecision(6);
    cout<<ternary_search(0, 1);
    return 0;
}

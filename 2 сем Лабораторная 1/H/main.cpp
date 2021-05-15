#include <bits/stdc++.h>

using namespace std;
#define ll long long

struct triple{
    ll x, type, minn;
};
bool cmp(triple a, triple b){
    if (a.x<b.x) return true;
    if (a.x>b.x) return false;
    return a.type>b.type;
}
vector <ll> tree;
vector <ll> a;
void rec(ll l, ll r, ll v){
    if (r-l==1){
        tree[v]=a[l];
    } else{
        ll m=(l+r)/2;
        rec(l,m,2*v+1);
        rec(m,r,2*v+2);
        tree[v]=min(tree[2*v+1],tree[2*v+2]);
    }
 }

 ll sum(ll nl, ll nr, ll l, ll r, ll v){
    if (r<=nl || l>=nr) return LONG_LONG_MAX;
    if ((nl>=l) && (nr<=r)) return tree[v];
    ll m=(nl+nr)/2;
    return min(sum(nl, m,l,r,2*v+1),sum(m,nr,l,r,2*v+2));
 }

int main(){
    ifstream f1("rmq.in");
    ofstream f2("rmq.out");
    vector <triple> s;
    vector <triple> anss;
    ll n,m;
    f1>>n>>m;
    a.resize(n, 0);
    triple helpOp, helpCl;
    helpOp.type=1;
    helpCl.type=-1;
    for (ll i=0; i<m; i++){
        f1>>helpOp.x>>helpCl.x>>helpOp.minn;
        helpOp.x--;
        helpCl.x--;
        helpCl.minn=helpOp.minn;
        s.push_back(helpCl);
        s.push_back(helpOp);
        helpOp.type=helpCl.x;
        anss.push_back(helpOp);
        helpOp.type=1;
    }
    sort(s.begin(),s.end(), cmp);

    ll left=0, put;
    multiset<ll> mstt;
    for (ll i=0; i<s.size(); i++){
       if (s[i].type==1){
            if (mstt.empty()) put=0;
            else {
                multiset<ll>::iterator it=mstt.end(); it--;
                put=*it;
            }
            for (ll j=left; j<s[i].x; j++){
                a[j]=put;
            }
            left=s[i].x;
            mstt.insert(s[i].minn);
        } else{
            if (mstt.empty()) put=0;
            else {
                multiset<ll>::iterator it=mstt.end(); it--;
                put=*it;
            }
            for (ll j=left; j<=s[i].x; j++){
                a[j]=put;
            }
            left=s[i].x+1;
            mstt.erase(mstt.find(s[i].minn));
        }
    }
    tree.resize(4*n);
    rec(0,n,0);
    for (ll j=0; j<m; j++){
        if (anss[j].minn!=sum(0,n,anss[j].x, anss[j].type+1,0)){
            f2<<"inconsistent "<<endl;
            return 0;
        }
    }

    f2<<"consistent"<<endl;
    for (ll i=0; i<n; i++){
        f2<<a[i]<<" ";
    }
    f1.close();
    f2.close();
    return 0;
}

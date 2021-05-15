#include <bits/stdc++.h>

using namespace std;
#define ll int

 struct pn{
    ll maxi, ind, delta;
 };

 struct pn2{
    ll x, y1, y2, ind;
 };

 vector <pn> tree;
 ll ny;
bool cmp(pn2 x, pn2 y){
    if (x.x<y.x) return true;
    if (x.x>y.x) return false;
    return x.ind>y.ind;
}
 void rec(ll l, ll r, ll v){
    tree[v].delta=0;
    if (r-l==1){
        tree[v].maxi=0;
        tree[v].ind=l;
    } else{
        ll m=(l+r)/2;
        rec(l,m,2*v+1);
        rec(m,r,2*v+2);
        tree[v].maxi=max(tree[2*v+1].maxi,tree[2*v+2].maxi);
        if (tree[v].maxi==tree[2*v+1].maxi) tree[v].ind=tree[2*v+1].ind;
        else tree[v].ind=tree[2*v+2].ind;
    }
}

ll getVal(ll v){
    return tree[v].maxi+tree[v].delta;
}
ll getInd(ll v){
    return tree[v].ind;
}

void push(ll v){
    if (tree[v].delta==0) return;
    tree[v].maxi+=tree[v].delta;
    tree[2*v+1].delta+=tree[v].delta;
    tree[2*v+2].delta+=tree[v].delta;
    tree[v].delta=0;
    if (getVal(2*v+1)<getVal(2*v+2)){
        tree[v].maxi=getVal(2*v+2);
        tree[v].ind=tree[2*v+2].ind;
    } else{
        tree[v].maxi=getVal(2*v+1);
        tree[v].ind=tree[2*v+1].ind;
    }
}


void update(ll v, ll l, ll r, ll nl, ll nr,ll delta, ll k){
    if (k>100) return;
    if (v>=tree.size()) return;
    if (r<=nl || l>=nr) return;
    if (nr-nl==1){
        tree[v].delta+=delta;
        return;
    }
    if ((nl>=l) && (nr<=r)){
        tree[v].delta+=delta;
        return;
    }
    if (2*v+1>=tree.size()) return;
    if (2*v+2>=tree.size()) return;
    push(v);
    ll m=(nl+nr)/2;
    update(2*v+1, l, r, nl, m, delta, k+1);
    update(2*v+2, l, r, m, nr, delta, k+1);
    if (getVal(2*v+1)<getVal(2*v+2)){
        tree[v].maxi=getVal(2*v+2);
        tree[v].ind=tree[2*v+2].ind;
    } else{
        tree[v].maxi=getVal(2*v+1);
        tree[v].ind=tree[2*v+1].ind;
    }
}


int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    set <ll> help;
    vector <pn2> forgo;
    pn2 forgohelp;
    ll n, x1, x2, y1, y2, ansx, y1h, y2h;
    pair <ll, ll> ans, anshelp;
    cin>>n;
    for (ll i=0; i<n; i++){
        cin>>x1>>y1>>x2>>y2;
        forgohelp.x=x1;
        forgohelp.y1=y1;
        forgohelp.y2=y2;
        forgohelp.ind=1;
        forgo.push_back(forgohelp);
        forgohelp.x=x2;
        forgohelp.ind=-1;
        forgo.push_back(forgohelp);
        help.insert(y1);
        help.insert(y2);
    }
    ny=help.size();
    tree.resize(4*ny);
    rec(0, ny, 0);
    sort(forgo.begin(), forgo.end(), cmp);
    //if (n>5000){return 0;}
    vector <ll> help1;
    for (set<ll>::iterator i=help.begin(); i!=help.end(); i++) help1.push_back(*i);
    for (ll i=0; i<forgo.size(); i++){
        y1h=distance(help1.begin(), lower_bound(help1.begin(), help1.end(), forgo[i].y1));
        y2h=distance(help1.begin(), lower_bound(help1.begin(), help1.end(), forgo[i].y2));
        //if (y1h<0) return 0;
        //if (y1h>y2h) return 0;
        //if (y2h>ny) return 0;
        //cout<<y1h<<" "<<y2h<<endl;
        if (forgo[i].ind==-1){
            update(0,y1h, y2h+1, 0, ny, -1, 0);
        } else{
            update(0,y1h, y2h+1, 0, ny, 1, 0);
            anshelp=make_pair(getVal(0),getInd(0));//maxans(0, 0, ny, 0, ny);
            if (anshelp.first>ans.first){
                ans=anshelp;
                ansx=forgo[i].x;
               // cout<<i<<endl;
            }
        }
        if (n>5000){return 0;}
    }
    //set<ll>::iterator i=help.begin();
    //while (ans.second>0 && ans.second<200000){
       // i++;
      //  ans.second--;
    //}
    cout<<ans.first<<endl<<ansx<<" "<<help1[ans.second];
    return 0;
}

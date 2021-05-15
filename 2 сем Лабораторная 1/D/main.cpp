#include <bits/stdc++.h>

using namespace std;
 #define ll long long
 struct pn{
    ll x, sum, b, e;
    ll type;
    //0-w
    //1-b
    //2-not
 };
 vector <pn> tree;
 ll n=1000002, k=500000;

 void rec(){
    for (ll v=0; v<n; v++){
        tree[v].sum=0;
        tree[v].x=0;
        tree[v].type=2;
        tree[v].b=false;
        tree[v].e=false;
    }
}
void push(ll v){
    if (tree[v].type!=2){
        tree[2*v+1].type=tree[v].type;
        tree[2*v+1].b=tree[v].type;
        tree[2*v+1].e=tree[v].type;
        tree[2*v+1].x=tree[v].type;
        tree[2*v+2].type=tree[v].type;
        tree[2*v+2].b=tree[v].type;
        tree[2*v+2].e=tree[v].type;
        tree[2*v+2].x=tree[v].type;
        tree[v].type=2;
    } else{
        if (tree[2*v+1].type!=2){
            tree[2*v+1].b=tree[2*v+1].type;
            tree[2*v+1].e=tree[2*v+1].type;
            tree[2*v+1].x=tree[2*v+1].type;
        }
        if (tree[2*v+2].type!=2){
            tree[2*v+2].b=tree[2*v+2].type;
            tree[2*v+2].e=tree[2*v+2].type;
            tree[2*v+2].x=tree[2*v+2].type;
        }
        tree[v].b=tree[2*v+1].b;
        tree[v].e=tree[2*v+2].e;
        tree[v].x=tree[2*v+1].x+tree[2*v+2].x;
        if (tree[2*v+1].e==tree[2*v+2].b && tree[2*v+2].b==1) tree[v].x--;
    }

}

ll getVal(ll v, ll l, ll r){
    if (tree[v].type==2) return tree[v].sum;
    if (tree[v].type==1) return r-l;
    else return 0;
}

void update(ll v, ll l, ll r, ll nl, ll nr, ll type){
    if (r<=nl || l>=nr) return;
    if ((nl>=l) && (nr<=r)){
        tree[v].type=type;
        tree[v].b=type;
        tree[v].e=type;
        tree[v].x=type;
        tree[v].sum=(nr-nl)*type;
        return;
    }
    push(v);
    ll m=(nl+nr)/2;
    update(2*v+1, l, r, nl, m, type);
    update(2*v+2, l, r, m, nr, type);
    push(v);
    tree[v].sum=getVal(2*v+1, nl, m) + getVal(2*v+2, m, nr);
    tree[v].x=tree[2*v+1].x+tree[2*v+2].x;
    if (tree[2*v+1].e==tree[2*v+2].b  && tree[2*v+2].b==1) tree[v].x--;
}

ll sumans(ll v, ll nl, ll nr, ll l, ll r){
    if (r<=nl || l>=nr) return 0;
    if ((nl>=l) && (nr<=r)) return getVal(v, nl, nr);
    push(v);
    ll m=(nl+nr)/2;
    ll ans= sumans(2*v+1,nl,m,l,r) + sumans(2*v+2,m,nr,l,r);
    tree[v].sum=getVal(2*v+1, nl, m)+getVal(2*v+2, m,nr);
    return ans;
}

ll colans(ll v, ll nl, ll nr, ll l, ll r){
    if (r<=nl || l>=nr) return 0;
    if ((nl>=l) && (nr<=r)){
        if (tree[v].type==2) return tree[v].x;
        return tree[v].type;
    }
    push(v);
    ll m=(nl+nr)/2;
    tree[v].x=colans(2*v+1, nl,m,l,r)+colans(2*v+2,m,nr, l,r);
    if (tree[2*v+1].e==tree[2*v+2].b  && tree[2*v+2].b==1) tree[v].x--;
    return tree[v].x;
}

int main()
{
    tree.resize(4*n);
    rec();
    string com;
    ll x, y, z;
    ll m;
    cin>>m;
    for(int i=0; i<m; i++){
        cin>>com;
        cin>>x>>y;
        if(com=="B"){
            update(0, x+k, x+y+k,0, n, 1);
        } else{
            update(0, x+k, x+y+k,0, n, 0);
        }
        cout<<colans(0,0,n,0,n)<<" "<<sumans(0,0,n,0,n)<<endl;
    }
    return 0;
}

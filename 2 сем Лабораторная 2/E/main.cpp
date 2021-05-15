#include <bits/stdc++.h>

using namespace std;
#define ll long long
typedef struct node{
    node* l=nullptr;
    node* r=nullptr;
    ll x, y;
    ll c;
};
typedef node* pnode;
pnode root=nullptr;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 1000000);

ll getC(pnode v){
    if (v==nullptr) return 0;
    return v->c;
}
void updateC(pnode v){
    if (v!=nullptr) v->c=getC(v->l)+getC(v->r)+v->x;
}
pair<pnode, pnode> split(pnode v, ll x){
    if (v==nullptr) return make_pair(nullptr, nullptr);
    if (v->x<x){
        pair<pnode, pnode> help = split(v->r, x);
        v->r=help.first;
        updateC(v);
        return make_pair(v, help.second);
    } else{
        pair<pnode, pnode> help = split(v->l, x);
        v->l=help.second;
        updateC(v);
        return make_pair(help.first, v);
    }
}
pnode merging(pnode l, pnode r){
    if (l==nullptr) return r;
    if (r==nullptr) return l;
    if (r->y>l->y){
        r->l=merging(l, r->l);
        updateC(r);
        return r;
    } else{
        l->r=merging(l->r, r);
        updateC(l);
        return l;
    }
}

pnode inserting (pnode now, ll key){
    pair < node*, node* > splited = split (now, key);
    node* newRoot = new node;
    newRoot->x=key;
    newRoot->y=rand();
    newRoot->c=key;
    newRoot = merging(splited.first, newRoot);
    newRoot = merging (newRoot, split(splited.second, key + 1).second);
    return newRoot;
}
/*pnode inserting(pnode v, ll x, ll y){
    if (v==nullptr){
        pnode help= new node;
        help->x=x;
        help->y=y;
        help->c=x;
        return help;
    }
    if (y>v->y){
        pair<pnode, pnode> help = split(v, x);
        pnode h= new node;
        h->x=x;
        h->y=y;
        h->l=help.first;
        h->r=help.second;
        updateC(h);
        return h;
    } else{
        if (x<v->x){
            v->l=inserting(v->l, x, y);
        } else{
            v->r=inserting(v->r, x, y);
        }
        updateC(v);
        return v;
    }
}*/

ll getAns(pnode v, ll l, ll r){
    pair <pnode, pnode> help1=split(v, l);
    ll ans=0;
    //cout<<help1.second->x<<endl;
    ans+=getC(help1.first);
    v=merging(help1.first, help1.second);
    pair <pnode, pnode> help2=split(v, r+1);
    //cout<<help2.second->x<<endl;
    //cout<<ans<<endl;
    ans+=getC(help2.second);
    //cout<<ans<<endl;
    root=merging(help2.first, help2.second);
    ans=getC(v)-ans;
    return ans;
}

pnode exists(pnode v, ll x){
    while (v!=nullptr){
        if (v->x>x) v=v->l;
        else{
            if (v->x<x) v=v->r;
            else break;
        }
    }
    return v;
}
int main()
{
    ll n;
    cin>>n;
    string t, ts="+";
    ll x, y, l, r, ansl;
    for (ll i=0; i<n; i++){
        cin>>t;
        if (t=="+"){
            cin>>x;
            y=dis(gen);
            if (ts=="?") x=(x+ansl)%1000000000;
            //cout<<x<<endl;
            //if (exists(root, x)==nullptr)
            root=inserting(root, x);
        }
        if (t=="?"){
            cin>>l>>r;
            ansl=getAns(root, l, r);
            //if (l>r) cout<<0<<endl;
            //else
            cout<<ansl<<endl;
        }
        ts=t;
    }
    return 0;
}

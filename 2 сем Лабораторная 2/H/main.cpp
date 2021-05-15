#include <bits/stdc++.h>

using namespace std;
#define ll long long
typedef struct node{
    node* l=nullptr;
    node* r=nullptr;
    ll y, c, cx;
    bitset<26> words, x;
};
typedef node* pnode;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 1000000);

ll getC(pnode v){
    if (v==nullptr) return 0;
    return v->c;
}
bitset<26> getB(pnode v){
    bitset <26> nulbit;
    if (v==nullptr) return nulbit;
    return v->words;
}
void updateC(pnode v){
    if (v!=nullptr){
        v->c=getC(v->l)+getC(v->r)+v->cx;
        v->words=getB(v->l) | getB(v->r) | v->x;
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

pair<pnode, pnode> split(pnode v, ll x){
    if (v==nullptr) return make_pair(nullptr, nullptr);
    ll l=getC(v->l)+v->cx;
    if (l<=x){
        pair<pnode, pnode> help = split(v->r, x-l);
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
pnode minimum(pnode v){
    while (v->l!=nullptr) v=v->l;
    return v;
}
void updateMinimum(pnode v){
    if (v==nullptr) return;
    updateMinimum(v->l);
    updateC(v);
}
pnode removing(pnode v, ll l, ll r){
    pair <pnode, pnode> help2=split(v, r);
    if (getC(help2.first)<r){
        ll need=r-getC(help2.first);
        pnode minnode=minimum(help2.second);
        pnode needNode2= new node;
        needNode2->x=minnode->x;
        needNode2->words=minnode->x;
        needNode2->y=dis(gen);
        needNode2->cx=need;
        needNode2->c=need;
        minnode->cx-=need;
        updateMinimum(help2.second);
        help2.first=merging(help2.first, needNode2);
        updateC(help2.first);
    }
    pair <pnode, pnode> help1=split(help2.first, l-1);
    if (getC(help1.first)<l-1){
        ll need=l-1-getC(help1.first);
        pnode minnode=minimum(help1.second);
        pnode needNode= new node;
        needNode->x=minnode->x;
        needNode->words=minnode->x;
        needNode->y=dis(gen);
        needNode->cx=need;
        needNode->c=need;
        minnode->cx-=need;
        updateMinimum(help1.second);
        help1.first=merging(help1.first, needNode);
        updateC(help1.first);
    }
    pnode vres=merging(help1.first, help2.second);
    updateC(vres);
    return vres;
}

pnode inserting(pnode v, ll l, ll cx, string x){
    pnode newNode = new node;
    newNode->cx=cx;
    newNode->c=cx;
    newNode->y=dis(gen);
    bitset<26> helpNode;
    helpNode.flip(int (x[0])- int('a'));
    newNode->x=helpNode;
    newNode->words=helpNode;
    if (v==nullptr) return newNode;
    pair <pnode, pnode> help1=split(v, l-1);
    if (getC(help1.first)<l-1){
        ll need=l-1-getC(help1.first);
        pnode minnode=minimum(help1.second);
        pnode needNode= new node;
        needNode->x=minnode->x;
        needNode->words=minnode->x;
        needNode->y=dis(gen);
        needNode->cx=need;
        needNode->c=need;
        minnode->cx-=need;
        updateMinimum(help1.second);
        help1.first=merging(help1.first, needNode);
        updateC(help1.first);
    }
    help1.first=merging(help1.first, newNode);
    return merging(help1.first, help1.second);
}

pnode query(pnode v, ll l, ll r){
    bitset<26> ans;
    //cout<<ans.count()<<endl;
    pair <pnode, pnode> help1=split(v, r);
    if (getC(help1.first)<r) ans=minimum(help1.second)->x;
    //cout<<ans.count()<<endl;
    pair <pnode, pnode> help2=split(help1.first, l-1);
    ans=ans | getB(help2.second);
    cout<<ans.count()<<endl;
    help2.first=merging(help2.first, help2.second);
    return merging(help2.first, help1.second);
}
void print(pnode v){
    if (v==nullptr) return;
    print(v->l);
    cout<<v->x<<" ";
    print(v->r);
}

void print2(pnode v){
    if (v==nullptr) return;
    print2(v->l);
    cout<<v->cx<<" ";
    print2(v->r);
}
int main(){
    ll n,x,y;
    cin>>n;
    string s,s2;
    pnode root=nullptr;
    for (ll i=0; i<n; i++){
        cin>>s;
        if (s=="+"){
            cin>>x>>y>>s2;
            root=inserting(root, x, y, s2);
        }
        if (s=="-"){
            cin>>x>>y;
            root=removing(root, x, y+x-1);
        }
        if (s=="?"){
            cin>>x>>y;
            root=query(root, x, y);
        }
        //print(root);
        //cout<<endl;
        //print2(root);
        //cout<<endl;

    }
    return 0;
}

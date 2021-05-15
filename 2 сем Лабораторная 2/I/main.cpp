#include <bits/stdc++.h>

using namespace std;

typedef struct node{
    node* l=nullptr;
    node* r=nullptr;
    node* p=nullptr;
    int x, y;
    int c=1;
    bool rev=false;
    bool cycle=false;
};
typedef node* pnode;
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, 300000);

int getC(pnode v){
    if (v==nullptr) return 0;
    return v->c;
}
void updateC(pnode v){
    if (v==nullptr) return;
    v->c=getC(v->l)+getC(v->r)+1;
    if (v->l!=nullptr) v->l->p=v;
    if (v->r!=nullptr) v->r->p=v;

}
void makeRev(pnode v){
    if(v==nullptr) return;
    if (!v->rev) return;
    v->rev=false;
    pnode help=v->r;
    v->r=v->l;
    v->l=help;
    if (v->l!=nullptr) v->l->rev=!(v->l->rev);
    if (v->r!=nullptr) v->r->rev=!(v->r->rev);
    updateC(v);
}
pair<pnode, pnode> split(pnode v, int x){
    if (v==nullptr) return make_pair(nullptr, nullptr);
    makeRev(v);
    int l=getC(v->l);
    if (l<x){
        pair<pnode, pnode> help = split(v->r, x-l-1);
        if (v->r!=nullptr) v->r->p=nullptr;
        v->r=help.first;
        if (v->r!=nullptr) v->r->p=v;
        updateC(v);
        updateC(help.second);
        return make_pair(v, help.second);
    } else{
        pair<pnode, pnode> help = split(v->l, x);
        if (v->l!=nullptr) v->l->p=nullptr;
        v->l=help.second;
        if (v->l!=nullptr) v->l->p=v;
        updateC(v);
        updateC(help.first);
        return make_pair(help.first, v);
    }
}
pnode merging(pnode l, pnode r){
    if (l==nullptr) return r;
    if (r==nullptr) return l;
    makeRev(l);
    makeRev(r);
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

pnode getRoot(pnode v){
    while (v->p!=nullptr) v=v->p;
    return v;
}
int getNumber(pnode v){
    int ans=1;
    if (v->rev){
        ans+=getC(v->r);
    } else{
        ans+=getC(v->l);
    }
    while (true){
        if (v->p==nullptr) break;
        if (v->p->rev){
            ans=-ans+v->c+1;
            makeRev(v->p);
        } else{
            if (v==v->p->r) ans+=getC(v->p->l)+1;
            if (v->p==nullptr) break;
            v=v->p;
        }
    }
    return ans-1;

}

bool getPosition(pnode v){
    if (getNumber(v)==0) return true;
    return false;
}
void makeRoad(pnode x, pnode y){
    pnode rootX=getRoot(x);
    pnode rootY=getRoot(y);
    if (rootX==rootY) rootX->cycle=true;
    else{
        if (getPosition(x)){
            if (getPosition(y)){
                rootX->rev=!(rootX->rev);
                merging(rootX, rootY); return;
            } else{
                merging(rootY, rootX);
            }
        } else{
            if (getPosition(y)){
                merging(rootX, rootY); return;
            } else{
                rootY->rev=!(rootY->rev);
                merging(rootX, rootY); return;
            }
        }
    }
}


void unCycle(pnode v){
    if (v==nullptr) return;
    v->cycle=false;
}
void ripRoad(pnode x, pnode y){
    pnode root=getRoot(x);
    int numX=getNumber(x);
    int numY=getNumber(y);
    if (root->cycle){
        root->cycle=false;
        if (!(((numX==0) && (numY==(root->c-1))) || ((numY==0) && (numX==(root->c-1))))){
            pair <pnode, pnode> help=split(root, min(numX, numY)+1);
            merging(help.second, help.first);
            unCycle(getRoot(help.first));
            return;
        }
    } else{
        pair <pnode, pnode> help=split(root, min(numX, numY)+1);
        unCycle(help.first);
        unCycle(help.second);
    }
}

void ans(pnode x, pnode y){
    if (x==y){cout<<"0"<<endl; return;}
    pnode rootX=getRoot(x);
    pnode rootY=getRoot(y);
    if (rootX!=rootY) {cout<<"-1"<<endl; return;}
    int numX=getNumber(x);
    int numY=getNumber(y);
    if (rootX->cycle) cout<<(min(abs(numX-numY), rootX->c-abs(numX-numY))-1)<<endl;
    else cout<<abs(numX-numY)-1<<endl;
}

int main(){
    int n, m, q;
    cin>>n>>m>>q;
    vector <pnode> city(n);
    for (int i=1; i<n+1; i++){
        city[i-1]=new node;
        city[i-1]->x=i;
        city[i-1]->y=dis(gen);
    }
    int x,y;
    for (int i=0; i<m; i++){
        cin>>x>>y;
        x--; y--;
        makeRoad(city[x], city[y]);
    }
    string s;
    for (int i=0; i<q; i++){
        cin>>s;
        cin>>x>>y;
        x--; y--;
        if (s=="?"){
            ans(city[x], city[y]);
        }
        if (s=="-"){
            ripRoad(city[x], city[y]);
        }
        if (s=="+"){
            makeRoad(city[x], city[y]);
        }
    }
    return 0;
}

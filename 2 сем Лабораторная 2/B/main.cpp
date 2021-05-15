#include <bits/stdc++.h>

using namespace std;
#define ll long long

typedef struct node{
    ll x;
    node* l=nullptr;
    node* r=nullptr;
};
typedef node* pnode;

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

pnode inserting(pnode v, ll x){
    if (v==nullptr){
        pnode z = new node;
        z->x=x;
        return z;
    }
    if (x<v->x) v->l=inserting(v->l, x);
    else v->r = inserting(v->r, x);
    return v;
}

pnode deleting(pnode v, ll x){
    if (v==nullptr) return v;
    if (v->x<x) v->r=deleting(v->r, x);
    else if (v->x>x) v->l = deleting(v->l, x);
        else if ((v->l!=nullptr) && (v->r!=nullptr)){
                pnode help=v->r;
                while (help->l!=nullptr) help=help->l;
                v->x=help->x;
                v->r=deleting(v->r, help->x);
            } else{
                if (v->l!=nullptr) v=v->l;
                else v=v->r;
            }
    return v;
}

pnode next(pnode v, ll x){
    pnode ans=nullptr;
    while (v!=nullptr){
        if (v->x<=x){
            v=v->r;
        }
        else {
            ans=v;
            v=v->l;
        }
    }
    return ans;
}

pnode prev(pnode v, ll x){
    pnode ans=nullptr;
    while (v!=nullptr){
        if (v->x<x){
            ans=v;
            v=v->r;
        } else v=v->l;
    }
    return ans;
}

vector <ll> massiv;
void toArray(pnode v){
    if (v==nullptr) return;
    toArray(v->l);
    massiv.push_back(v->x);
    toArray(v->r);
}
void reqMakeTree(pnode root, ll l, ll r){
    if (r-l<1) return;
    ll m=(r+l)/2;
    inserting(root, massiv[m]);
    reqMakeTree(root, l, m);
    reqMakeTree(root, m+1, r);
}
pnode makeNewTree(){
    pnode root = nullptr;
    ll m=massiv.size()/2;
    root=inserting(root, massiv[m]);
    reqMakeTree(root, 0, m);
    reqMakeTree(root, m+1, massiv.size());
    return root;
}

int main()
{
    pnode root = nullptr;
    string c;
    ll x, i=0;
    while(cin>>c){
        i++;
        if (i==5000){
            i=0;
            if (root!=nullptr){
                massiv.clear();
                toArray(root);
                root=makeNewTree();
            }
        }
        if (c=="insert"){
            cin>>x;
            if (exists(root, x)==nullptr) root=inserting(root, x);
        }
        if (c=="delete"){
            cin>>x;
            if (exists(root, x)!=nullptr) root=deleting(root, x);
        }
        if (c=="exists"){
            cin>>x;
            pnode help=exists(root,x);
            if (help==nullptr) cout<<"false";
            else cout<<"true";
            cout<<endl;
        }
        if (c=="next"){
            cin>>x;
            pnode help=next(root, x);
            if (help==nullptr) cout<<"none";
            else cout<<help->x;
            cout<<endl;
        }
        if (c=="prev"){
            cin>>x;
            pnode help=prev(root, x);
            if (help==nullptr) cout<<"none";
            else cout<<help->x;
            cout<<endl;
        }
    }
    return 0;
}

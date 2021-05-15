#include <bits/stdc++.h>

using namespace std;
#define ll long long

vector  < pair < pair< ll, ll >, ll > > a, ans;
ll n;
typedef struct node{
    node* l=nullptr;
    node* r=nullptr;
    node* p=nullptr;
    ll x, y, i;
};
typedef node* pnode;

pnode root;
void makeTree(){
    root = new node;
    root->x=a[0].first.first;
    root->y=a[0].first.second;
    root->i=a[0].second;
    pnode last=root;
    for (ll i=1; i<n; i++){
        bool f=false;
        if (last->y>a[i].first.second){
            while (last->y>a[i].first.second){
                if (last->p!=nullptr) {f = false; last=last->p;}
                else {
                    f=true;
                    break;
                }
            }
            if (f){
                pnode help = new node;
                help->x=a[i].first.first;
                help->y=a[i].first.second;
                help->i=a[i].second;
                help->l=root;
                help->l->p=help;
                root=help;
                last=root;
            } else{
                pnode help = new node;
                help->x=a[i].first.first;
                help->y=a[i].first.second;
                help->i=a[i].second;
                help->l=last->r;
                help->l->p=help;
                last->r=help;
                help->p=last;
                last=help;
            }
        } else{
            pnode help = new node;
            help->x=a[i].first.first;
            help->y=a[i].first.second;
            help->i=a[i].second;
            last->r=help;
            help->p=last;
            last=help;
        }
    }
}
vector <ll> massiv;
void toArray(pnode v){
    if (v==nullptr) return;
    toArray(v->l);
    massiv.push_back(v->y);
    toArray(v->r);
}

void toAns(pnode v){
    if (v==nullptr) return;
    ll i=v->i;
    if (v->l==nullptr) ans[i].first.first=0;
    else ans[i].first.first=v->l->i+1;
    if (v->r==nullptr) ans[i].first.second=0;
    else ans[i].first.second=v->r->i+1;
    if (v->p==nullptr) ans[i].second=0;
    else ans[i].second=v->p->i+1;
    toAns(v->l);
    toAns(v->r);
}
int main()
{
    cin>>n;
    a.resize(n);
    ans.resize(n);
    for (ll i=0; i<n; i++){
        cin>>a[i].first.first>>a[i].first.second;
        a[i].second=i;
    }
    sort(a.begin(), a.end());
    makeTree();
    toAns(root);
    cout<<"YES"<<endl;
    for (ll i=0; i<ans.size(); i++){
        cout<<ans[i].second<<" "<<ans[i].first.first<<" "<<ans[i].first.second<<endl;
    }
    return 0;
}

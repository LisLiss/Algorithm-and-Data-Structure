#include <bits/stdc++.h>

using namespace std;
typedef struct node{
    int h, l, r, sum, maxi;
    bool delta;
    node* left;
    node* right;
};
typedef node* pnode;

 pnode tree;

void push(pnode v){
    if (v->left == NULL){
        v->left = new node;
        v->right = new node;
        int m=(v->l+v->r)/2;
        v->left->l=v->l;
        v->left->r=m;
        v->left->h=v->h;
        v->left->sum=(v->h)*(m+1-v->l);
        v->left->maxi=v->left->sum;
        v->left->delta=true;
        v->left->left=NULL;
        v->left->right=NULL;

        v->right->l=m+1;
        v->right->r=v->r;
        v->right->h=v->h;
        v->right->sum=(v->h)*(v->r-m);
        v->right->maxi=v->right->sum;
        v->right->delta=true;
        v->right->left=NULL;
        v->right->right=NULL;

    } else{
        if (v->delta){
            v->left->sum=v->h*(v->left->r - v->left->l +1);
            v->left->maxi=v->left->sum;
            v->left->h=v->h;
            v->left->delta=true;

            v->right->sum=v->h*(v->right->r - v->right->l +1);
            v->right->maxi=v->right->sum;
            v->right->h=v->h;
            v->right->delta=true;
        }
    }
    v->delta=false;
}

void update(pnode v, int l, int r, int delta){
    int nl = v->l, nr=v->r;
    if (r<nl || l> nr) return;
    if ((nl>=l) && (nr<=r)){
        v->h=delta;
        v->delta=true;
        v->sum=v->h*(nr-nl+1);
        v->maxi=v->sum;
        return;
    }
    push(v);
    update(v->left, l, r, delta);
    update(v->right, l, r, delta);
    v->maxi=max(v->left->maxi, v->right->maxi+v->left->sum);
    v->sum=v->left->sum+v->right->sum;
}

int minans(pnode v, int nh){
    int nl=v->l, nr=v->r;
    if (nl==nr) return nl-1;
    if (v->maxi<=nh) return nr;
    push(v);
    if (v->left->maxi>nh) return minans(v->left, nh);
    nh-=v->left->sum;
    return minans(v->right, nh);
}
void print(pnode v){
    cout<<v->l<<" "<<v->r<<" "<<v->h<<" "<<v->maxi<<" "<<v->delta<<endl;
    if (v->left!=NULL) print(v->left);
    if (v->right!=NULL) print(v->right);
}
int main()
{
    int n;
    cin>>n;
    tree=new node;
    tree->l=1;
    tree->r=n;
    tree->maxi=0;
    tree->h=0;
    tree->sum=0;
    tree->delta=true;
    tree->left=NULL;
    tree->right=NULL;
    string com;
    int x=-1, y, z;
    while(cin>>com){
        //print(tree);
        if(com=="Q"){
            cin>>x;
            cout<<minans(tree, x)<<endl;
        } else{
            if (com=="I"){
                cin>>x>>y>>z;
                update(tree, x, y, z);
            } else{
                return 0;
            }
        }
    }
    return 0;
}

#include <iostream>

using namespace std;
typedef struct node{
    int x;
    int minEl;
    node* next;
};
typedef node* pnode;

pnode add(pnode root, int x){
    int minEl;
    if (root==NULL){
        minEl=x;
    }
    else{
        minEl=min(x, root->minEl);
    }
    pnode a = new node;
    a->x=x;
    a->next=root;
    a->minEl=minEl;
    root=a;
    return root;
}

pnode del(pnode root){
    root=root->next;
    return root;
}

int minEl(pnode root){
    return root->minEl;
}

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n, m, x, i;
    cin>>n;
    pnode root = NULL;
    for (int j=0; j<n; j++){
        cin>>i;
        if (i==1){
            cin>>x;
            root = add(root, x);
        }
        if (i==2){
            root = del(root);
        }
        if (i==3){
            cout<<minEl(root)<<endl;
        }
    }
    return 0;
}


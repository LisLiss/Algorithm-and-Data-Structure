#include <bits/stdc++.h>

using namespace std;

typedef struct node{
    node* next;
    node* prev;
    int x;
};
typedef node* pnode;

pnode root, tail;
void add(int x){
    if (root==NULL){
        pnode a = new node;
        a->x=x;
        a->next=NULL;
        a->prev=NULL;
        root=a;
        tail=a;
    } else{
        pnode a = new node;
        a->x=x;
        a->prev=tail;
        tail->next=a;
        a->next=NULL;
        tail=a;
    }
}

void delroot(){
    if (root->next==NULL){
        root=NULL;
        tail=NULL;
    } else{
        root=root->next;
        root->prev=NULL;
    }
}

void deltail(){
    if (root==tail){
        root=NULL;
        tail=NULL;
    } else{
        tail=tail->prev;
        tail->next=NULL;
    }
}

int numbefore(int x){
    pnode a = root;
    int ans=0;
    while (a->x!=x){
        ans++;
        a=a->next;
    }
    return ans;
}

int numfirst(){
    return root->x;
}

void print(){
    cout<<endl<<"--------"<<endl;
    pnode a = root;
    while(a!=NULL){
        cout<<a->x<<" ";
        a=a->next;
    }
    cout<<endl<<"--------"<<endl;
}
int main()
{
    int n, j, x;
    cin>>n;
    root=NULL;
    tail=NULL;
    for (int i=0; i<n; i++){
        //print();
        cin>>j;
        if (j==1){
            cin>>x;
            add(x);
        }
        if (j==2){
            delroot();
        }
        if (j==3){
            deltail();
        }
        if (j==4){
            cin>>x;
            cout<<numbefore(x)<<endl;
        }
        if (j==5){
            cout<<numfirst()<<endl;
        }
    }
    return 0;
}

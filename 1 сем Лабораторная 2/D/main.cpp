#include <iostream>

using namespace std;

typedef struct node{
    int x;
    node* prev;
    node* next;
};
typedef node* pnode;

pnode root, tail, median;
int n;

void addtop(int x){
    if (n==0){
        root = new node;
        root->x=x;
        root->next=NULL;
        root->prev=NULL;
        tail=root;
        median=root;
    } else{
        pnode a = new node;
        a->x=x;
        if (n==1){
            a->next=NULL;
            root->next=a;
            a->prev=root;
            tail=a;
            median=root;
        } else{
            a->next=median->next;
            a->prev=median;
            median->next=a;
            a->next->prev=a;
            if (n%2==0) median=a;
        }
    }
    n++;
}

void addluz(int x){
    if (n==0){
        root = new node;
        root->x=x;
        root->next=NULL;
        root->prev=NULL;
        tail=root;
        median=root;
    } else{
        pnode a= new node;
        a->x=x;
        a->next=NULL;
        a->prev=tail;
        tail->next=a;
        tail=a;
        if (n==1){
            median=root;
        } else{
            if (n%2==0){
                median=median->next;
            }
        }
    }
    n++;
}

int del(){
    int ans=root->x;
    if (n==1){
        root=NULL;
        tail=NULL;
        median=NULL;
        n--;
        return ans;
    }
    root=root->next;
    if (n%2==0){
        median=median->next;
    }
    n--;
    return ans;
}

int main(){
    int nn, x;
    cin>>nn;
    string s;
    for (int i=0; i<nn; i++){
        cin>>s;
        if (s=="+"){
            cin>>x;
            addluz(x);
        } else{
            if (s=="*"){
                cin>>x;
                addtop(x);
            } else{
                cout<<del()<<endl;
            }
        }
    }
    return 0;
}

#include <iostream>

using namespace std;

typedef struct node{
    node* next;
    node* last;
    int color;
};
typedef node* pnode;

int answer=0, nn;
pnode root;

void add(int x){
    pnode h= new node;
    h->color=x;
    h->next=root;
    h->last=NULL;
    if (root!=NULL) root->last=h;
    root=h;
}
pnode del(pnode ball){
    int ans=1;
    pnode left = ball;
    pnode right = ball;
    while (true){
        if (left->last==NULL) break;
        if (left->last->color!=ball->color) break;
        ans++;
        left=left->last;
    }
    while (true){
        if (right->next==NULL) break;
        if (right->next->color!=ball->color) break;
        ans++;
        right=right->next;
    }
    if (ans>2){
        answer+=ans;
        nn-=ans;
        if (left->last==NULL && right->next==NULL) return NULL;
        if (left->last==NULL) {
            right->next->last=NULL;
            root=right->next;
            return root;
        }
        if (right->next==NULL){
            left->last->next=NULL;
            return left->last;
        }
        left->last->next=right->next;
        right->next->last=left->last;
        return left->last;
    }
    else{
        return NULL;
    }
}
int main(){
    int n, x;
    root=NULL;
    cin>>n;
    nn = n;
    for (int i=0; i<n; i++){
        cin>>x;
        add(x);
    }
    pnode it=root;
    while (it!=NULL){
        pnode help = del(it);
        if (nn==0) break;
        if (help!=NULL) {it = help; break;}
        it = it->next;
    }
    if (nn==0){
        cout<<n;
        return 0;
    }
    if (it==NULL){
        cout<<"0";
        return 0;
    }
    while (true){
        pnode help = del(it);
        it = help;
        if (help==NULL) break;
    }
    cout<<answer;
    return 0;
}

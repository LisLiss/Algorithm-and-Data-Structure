#include <bits/stdc++.h>

using namespace std;
struct aaa{
    int mini, maxi, x, num;
};

vector <aaa> number;
int get(int x1){
    while (x1!=(number[x1].x)){
        x1=number[x1].x;
    }
    return x1;
}

int main()
{
    int n;
    cin>>n;
    number.resize(n+1);
    for (int i=1; i<n+1; i++){
        number[i].x=i;
        number[i].mini=i;
        number[i].maxi=i;
        number[i].num=1;
    }
    string s;
    while (cin>>s){
        if (s=="union"){
            int x, y;
            cin>>x>>y;
            x=get(x);
            y=get(y);
            number[y].mini=min(number[y].mini,number[x].mini);
            number[y].maxi=max(number[y].maxi,number[x].maxi);
            if (x!=y) number[y].num+=number[x].num;
            number[x].x=y;
        } else{
            int x;
            cin>>x;
            x=get(x);
            cout<<number[x].mini<<" "<<number[x].maxi<<" "<<number[x].num<<endl;
        }
    }
    return 0;
}

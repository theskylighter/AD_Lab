#include<bits/stdc++.h>
using namespace std;

int mystery(int x)
{
    int ret;
    if(x==1){
        return 2;
     
    }
    else{
        ret =mystery(x/2);
        ret=ret*ret;
        if(x%2==1){
            ret=ret*2;
        }
        return ret;
    }
}
int main(){
    cout<<"running"<<endl;
    cout<<"enter n"<<endl;
    int n;
    cin>>n;
    cout<<mystery(n)<<endl;

    return 0;
}
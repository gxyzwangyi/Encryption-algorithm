#include <iostream>
using namespace std;

int S[256];
int k[256];
void swap(int &a,int &b){
int t=a;
a=b;
b=t;
}

void Init(int k[]){

for(int i=0;i<256;i++){
    S[i]=i;
    k[i]=k[i%16];
}
int j=0;
for (int i=0;i<256;i++){
j=(j+S[i]+k[i])%256;
swap(S[i],S[j]);
}
cout<<S;
}

int GetBits(int S[],int i,int j){
i=(i+1)%256;
j=(j+S[i])%256;
swap(S[i],S[j]);
int t = (S[i]+S[j])%256;
return S[t];
}
int main(){
    memset(k , 0 , 256);
    memset(S , 0 , 256);


    Init(k);
    cout<<endl;
cout<< GetBits(S,1,2);


}
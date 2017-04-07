#include <iostream>
#include <algorithm>

#include "timer.hpp"

using namespace std;

#define NOISY 0

inline void print_perm(int *cur,int n)
{
	if (NOISY) {
		for(int i=0;i<n;i++)cout<<cur[i]<<"\t";
		cout<<endl;
	}
}

int Ascend_add1(int *num,int n)
{
    if(n<=0)return 1;
    for(int i=0;i<n;i++){
        if(num[i]+1>=i+2){
            num[i]=num[i]-i-1;
            if(i==n-1)return 1;
        }
        else {
            num[i]=num[i]+1;
            break;
        }
    }
    return 0;
}

int Descend_add1(int *num,int n)
{
    if(n<=0)return 1;
    for(int i=0;i<n;i++){
        if(num[i]+1>=n+1-i){
            num[i]=num[i]+i-n;
            if(i==n-1)return 1;
        }
        else {
            num[i]=num[i]+1;
            break;
        }
    }
    return 0;
}

//InterNumber to permutation (Ascending)
int Num2permutation(int *num,int *per, int n)
{
    int pos;
    for(int i=0;i<n;i++)per[i]=0;
    for(int i=n;i>1;i--){
        pos = n-1-num[i-2];
        for(int j=n-1;j>n-2-num[i-2];j--)if(per[j]>i)pos--;
        while(per[pos])pos--;
        per[pos]=i;
    }
    pos=n-1;
    while(per[pos])pos--;
    per[pos]=1;
    print_perm(per,n);
    return 0;
}

int Number2Serial(int *num, int n)
{
    int s=0;
    for(int j=n-1;j>=0;j--)s=(s+num[j])*(j+1);
    return s;
}

void Swap(int &a,int &b)
{
    int t=a;
    a=b;
    b=t;
}

void Reverse(int *src,int *rst,int n)
{
    for(int i=0;i<n;i++){
        rst[i]=src[n-i-1];
    }
}

int FindMinLarge(int a,int *cur,int pos,int n)
{
    int m=pos;
    for(int i=pos+1;i<n;i++){
        if(cur[i]>a&&cur[i]<cur[m])m=i;
    }
    return m;
}

//Next Lexico_permutation
int Next_permutation(int *cur,int n)
{
    int i;
    for(i=n-2;i>=0;i--)if(cur[i]<cur[i+1])break;
    if(i<0)return 1;
    int toSwap=FindMinLarge(cur[i],cur,i+1,n);
    Swap(cur[i],cur[toSwap]);
    sort(cur+i+1,cur+n);
    print_perm(cur,n);
    return 0;
}

int Lexico_permutation(int n)
{
    int *cur=new int[n];
    for(int i=0;i<n;i++)cur[i]=i+1;
    print_perm(cur,n);
    while(!Next_permutation(cur,n));
    return 0;
}

void Ascend_permutation(int n)
{
    int *num=new int[n-1];
    int *cur=new int[n];
    for(int i=0;i<n-1;i++)num[i]=0;
    do{
        Num2permutation(num,cur,n);
    }while(!Ascend_add1(num,n-1));
}

void Descend_permutation(int n)
{
    int *num=new int[n-1];
    int *tmp=new int[n-1];
    int *cur=new int[n];
    for(int i=0;i<n-1;i++)num[i]=0;
    do{
        Reverse(num,tmp,n-1);
        Num2permutation(tmp,cur,n);
    }while(!Descend_add1(num,n-1));
}

void SJT_permutation(int n)
{
    int *cur=new int[n];
    int *dir=new int[n];
    for(int i=0;i<n;i++){cur[i]=i+1;dir[i]=0;}
    print_perm(cur,n);
    int MaxMobileIdx=0;
    int MaxMobile=0;
    int hasMobile=0;
    while(1){
        for(int i=n-1;i>=0;i--){
            if(dir[i]&&i!=n-1)
                if(cur[i]>cur[i+1]){
                    hasMobile=1;
                    if(cur[i]>MaxMobile){
                        MaxMobile=cur[i];
                        MaxMobileIdx=i;
                    }
                }
            if(!dir[i]&&i!=0)
                if(cur[i]>cur[i-1]){
                    hasMobile=1;
                    if(cur[i]>MaxMobile){
                        MaxMobile=cur[i];
                        MaxMobileIdx=i;
                    }
                }
        }
        if(!hasMobile)break;
        if(dir[MaxMobileIdx]){Swap(cur[MaxMobileIdx],cur[MaxMobileIdx+1]);Swap(dir[MaxMobileIdx],dir[MaxMobileIdx+1]);}
        else {Swap(cur[MaxMobileIdx],cur[MaxMobileIdx-1]);Swap(dir[MaxMobileIdx],dir[MaxMobileIdx-1]);}
        if(MaxMobile<n){
            for(int i=0;i<n;i++){
                if(cur[i]>MaxMobile)dir[i]=1-dir[i];
            }
        }
        print_perm(cur,n);
        hasMobile=0;
        MaxMobile=0;
    }
}

int main()
{

    int input;
	double start, end;
    do{
        cin>>input;
        cout<<"Lexico_permutation:"<<endl;
        start = get_time();
		Lexico_permutation(input);
        end = get_time();
		cout << "Takes " << end-start << "s" << endl;
        cout<<endl;
        cout<<"Ascend_permutation:"<<endl;
        start = get_time();
        Ascend_permutation(input);
        end = get_time();
		cout << "Takes " << end-start << "s" << endl;
        cout<<endl;
        cout<<"Descend_permutation:"<<endl;
        start = get_time();
        Descend_permutation(input);
        end = get_time();
		cout << "Takes " << end-start << "s" << endl;
        cout<<endl;
        cout<<"SJT_permutation:"<<endl;
        start = get_time();
        SJT_permutation(input);
        end = get_time();
		cout << "Takes " << end-start << "s" << endl;
        cout<<endl;

    }while(input);
    return 0;
}

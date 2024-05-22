//不要求同余方程模数互质 
#include<bits/stdc++.h>
#define LL __int128
#define ll long long
#define MAX_N 100010
using namespace std;
void exgcd(LL a,LL b,LL&k1,LL&k2)
{
    if(a==0)
    {
        k1=0,k2=1;
        return;
    }
    exgcd(b%a,a,k1,k2);
    LL kk1=k1,kk2=k2;
    k2=kk1;
    k1=kk2-k2*(b/a);
}
pair<LL,LL>excrt(pair<LL,LL>f1,pair<LL,LL>f2)//合并 f1 和 f2 两个同余方程
{
    LL r1=f1.first,m1=f1.second;
    LL r2=f2.first,m2=f2.second;
    if(r1==-1||r2==-1)return {-1,-1};
    LL d=__gcd(m1,m2),k1,k2;
    exgcd(m1,m2,k1,k2);
    if((r2-r1)%d)return {-1,-1};//无解返回-1 
    LL M=m1/d*m2;
    LL R=(((r2-r1)/d*k1%M*m1%M+r1)%M+M)%M;//R=(r2-r1)/d*k1*m1+r1
    //这里是取 r1 算的，为了避免溢出r1应当尽可能小，所以应当把数值小的同余方程放前面！！！
    return {R,M};
}
pair<ll,ll>func[MAX_N];
int main()
{
    ll n;cin>>n;
    for(LL i=1;i<=n;++i)
        cin>>func[i].second>>func[i].first;//输入 x = first (mod second)  ->  x=r mod m
    for(LL i=2;i<=n;++i)
        func[i]=excrt(func[i],func[i-1]);//务必把数小的放前面！！！不然可能溢出
//    cout<<func[n].first<<" "<<func[n].second<<endl;
	cout<<func[n].first<<endl;
    return 0;
}
/*
3
1 2
2 3
3 5
*/

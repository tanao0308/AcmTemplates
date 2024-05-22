//https://www.luogu.com.cn/problem/P5656
#include<bits/stdc++.h>
#define ll long long
using namespace std;
//k1*a+k2*b=gcd(a,b)
ll exgcd(ll a,ll b,ll&x,ll&y)
{
    if(!b)return x=1,y=0,a;
    ll d=exgcd(b,a%b,x,y),t=x;
    return x=y,y=t-a/b*y,d;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int T;cin>>T;
    while(T--)
    {
        ll a,b,c;
        cin>>a>>b>>c;
        ll k1,k2;
        ll gcd=exgcd(a,b,k1,k2);
        if(c%gcd)
        {
            cout<<-1<<endl;
            continue;
        }
        a/=gcd,b/=gcd,c/=gcd;
        k1*=c,k2*=c;
        ll t1=ceil((double)(1-k1)/b);//k1+t*b>0
        k1+=t1*b,k2-=t1*a;
        if(k2<=0)
        {
            ll t2=ceil((double)(1-k2)/a);k2+=t2*a;
            cout<<k1<<" "<<k2<<endl;
            continue;
        }
        ll k1min=k1,k2max=k2;
        ll t2=ceil((double)(1-k2)/a);
        k2+=t2*a,k1-=t2*b;
        ll k1max=k1,k2min=k2;
        cout<<(k1max-k1min)/b+1<<" "<<k1min<<" "<<k2min<<" "<<k1max<<" "<<k2max<<endl;
    }
    return 0;
}
/*
求解 k1*a + k2*b=c 的整数方程组时
不妨设 a<b
则有 k1*a + k2*b = k1*a + k2*(b%a+[b/a]*a) = c
     (k1+k2*[b/a])*a + k2*(b%a) = c
     k2*(b%a) + (k1+k2*[b/a])*a = c
     
     可将 k1*a + k2*b=c 记为 (a,b,&k1,&k2)
     则 (a,b,k1,k2) = (b%a,a,k2,k1+k2*[b/a])
     将已知量 (b%a,a,k2,k1+k2*[b/a]) 记为 (b%a,a,t1,t2)
     则很容易反推出k1,k2的值
结束
*/

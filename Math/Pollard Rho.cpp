#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define endl '\n'
using namespace std;

ll mul(ll x,ll y,ll Mod){
    ll r=x*y-Mod*(ll)(1.L/Mod*x*y);
    return r-Mod*(r>=Mod)+Mod*(r<0);
}
ll ksm(ll a,ll b,ll mod) {
    ll ans=1;
    for(;b;a=(LL)a*a%mod,b/=2) {
        if(b&1) ans=(LL)ans*a%mod;
    }
    return ans;
}
namespace MR{
    const ll pr[7]={2,325,9375,28178,450775,9780504,1795265022};
    bool isprime(ll x){
        if(x<3||x%2==0)return x==2;
        int r=0;
        ll k=x-1;
        for(;!(k&1);k>>=1,++r);
        for(int T=7,j;T--;){
            ll p=pr[T];
            if(p%x==0)continue;
            ll v=ksm(p,k,x);
            if(v==1)continue;
            for(j=1;j<=r;++j,v=mul(v,v,x))
                if(v==x-1)break;
            if(j>r)return 0;
        }
        return 1;
    }
}
namespace PR{
    ll calc(ll n){
        if(!(n&1))return 2;
        ll x=0,y=0,z=0,p=1,q,g;
        for(int i=0;(i&255)||(g=__gcd(p,n))==1;
            ++i,x=mul(x,x,n)+1,y=mul(y,y,n)+1,y=mul(y,y,n)+1){
            if(x==y)x=z++,y=mul(x,x,n)+1;
            q=mul(p,x-y+n,n);
            if(q)p=q;
        }
        return g;
    }
    vector<ll> split(ll n){
        if(n==1)return {};
        if(MR::isprime(n))return {n};
        ll d=calc(n);
        while(d==1||d==n)d=calc(n);
        vector<ll>v1=split(d),v2=split(n/d),v3(v1.size()+v2.size());
        merge(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
        return v3;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int times; cin>>times;
    while(times--) 
    {
        ll n; cin>>n;
        vector<ll>ans=PR::split(n);
        if(MR::isprime(n)) cout<<"Prime"<<endl;
        else cout<<ans.back()<<endl;
        // for(int i=0;i<ans.size();++i)cout<<ans[i]<<" ";cout<<endl;
    }
    return 0;
}
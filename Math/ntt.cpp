#include<bits/stdc++.h>
#define Pi acos(-1)
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
const ll MOD=998244353;
ll power(ll a,ll b=MOD-2)
{
    ll ans=1;
    for(;b;b>>=1,a=a*a%MOD)
        if(b&1)ans=ans*a%MOD;
    return ans;
}
namespace NTT
{
    const int M=4000005;
    const ll G=3,Gi=332748118;
    int bit,tot;
    int rev[M];
    void ntt(vector<ll>&a,int on)
    {
        for(int i=0;i<tot;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
        for(int n=1;n<tot;n*=2)
        {
            ll w1=power(on==1?G:Gi,(MOD-1)/(2*n));
            for(int i=0;i<tot;i+=n*2)
            {
                ll wk=1;
                for(int j=0;j<n;j++,wk=wk*w1%MOD)
                {
                    ll x=a[i+j];
                    ll y=wk*a[i+j+n]%MOD;
                    a[i+j]=(x+y)%MOD;
                    a[i+j+n]=(x-y+MOD)%MOD;
                }
            }
        }
        if(on==-1)//就不用后面除了
        {
            ll intot=power(tot);
            for(int i=0;i<tot;i++)
                a[i]=a[i]*intot%MOD;
        }
    }
    vector<ll>mul(vector<ll>a,vector<ll>b)
    {
        int deg=(int)a.size()+b.size()-1;
        bit=0;
        while((1<<bit)<deg)bit++;
        tot=1<<bit;
        for(int i=0;i<tot;i++)
            rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
        vector<ll>c(tot);
        a.resize(tot),b.resize(tot);
        ntt(a,1),ntt(b,1);
        for(int i=0;i<tot;i++)c[i]=a[i]*b[i]%MOD;
        ntt(c,-1);
        c.resize(deg);
        return c;
    }
}
int main()
{
	int n,m;cin>>n>>m;
	ll x;vector<ll>a,b;
	for(int i=0;i<=n;++i)cin>>x,a.push_back(x);
	for(int i=0;i<=m;++i)cin>>x,b.push_back(x);
	vector<ll>h=NTT::mul(a,b);
	for(int i=0;i<h.size();++i)cout<<h[i]<<" ";cout<<endl;
	return 0;
}

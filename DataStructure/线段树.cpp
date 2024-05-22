#include<bits/stdc++.h>
#define MAX_N 100010
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
struct node
{
    ll sum,laz;
}seg[MAX_N<<2];
ll a[MAX_N];
struct SEGM
{
    node*s;
    void up(node&a,node&b,node&c)
    {
        c.sum=a.sum+b.sum;
    }
    void build(ll p,ll l,ll r)
    {
        if(l==r)
        {
            s[p]={a[l],0};
            return;
        }
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        up(s[p<<1],s[p<<1|1],s[p]);
    }
    void down(node&a,node&b,node&c,ll l,ll r)
    {
        a.sum+=(mid-l+1)*c.laz;
        b.sum+=(r-mid)*c.laz;
        a.laz+=c.laz,b.laz+=c.laz;
        c.laz=0;
    }
    void change(ll p,ll l,ll r,ll x,ll y,ll c)
    {
        if(x<=l&&r<=y)
        {
            s[p].sum+=(r-l+1)*c;
            s[p].laz+=c;
            return;
        }
        down(s[p<<1],s[p<<1|1],s[p],l,r);
        if(x<=mid)change(p<<1,l,mid,x,y,c);
        if(y>mid)change(p<<1|1,mid+1,r,x,y,c);
        up(s[p<<1],s[p<<1|1],s[p]);
    }
    ll query(ll p,ll l,ll r,ll x,ll y)
    {
        if(x<=l&&r<=y)
            return s[p].sum;
        ll ans=0;
        down(s[p<<1],s[p<<1|1],s[p],l,r);
        if(x<=mid)ans+=query(p<<1,l,mid,x,y);
        if(y>mid)ans+=query(p<<1|1,mid+1,r,x,y);
        return ans;
    }
};
int main()
{
    ll n,m;
    cin>>n>>m;
    for(ll i=1;i<=n;++i)cin>>a[i];

    SEGM SEG;SEG.s=seg;SEG.build(1,1,n);
    while(m--)
    {
        ll op,x,y;
        cin>>op>>x>>y;
        if(op==1)
        {
            ll k;
            cin>>k;
            SEG.change(1,1,n,x,y,k);
        }
        else
            cout<<SEG.query(1,1,n,x,y)<<endl;
    }
    return 0;
}
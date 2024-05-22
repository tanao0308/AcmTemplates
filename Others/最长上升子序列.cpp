#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 100010
using namespace std;
int a[MAX_N];
struct node
{
    int val,p;
}dp[MAX_N];
node seg[MAX_N<<2];
void up(int p)
{
    if(seg[p<<1].val>=seg[p<<1|1].val)seg[p]=seg[p<<1];
    else seg[p]=seg[p<<1|1];
}
void build(int p,int l,int r)
{
    if(l==r)
    {
        seg[p]={0,l};
        return;
    }
    build(p<<1,l,mid);
    build(p<<1|1,mid+1,r);
    up(p);
}
void change(int p,int l,int r,int x,node c)
{
    if(l==r)
    {
        seg[p]=c;
        return;
    }
    if(x<=mid)change(p<<1,l,mid,x,c);
    else change(p<<1|1,mid+1,r,x,c);
    up(p);
}
node query(int p,int l,int r,int x,int y)
{
    if(x<=l&&r<=y)
        return seg[p];
    node a={0,0},b={0,0};
    if(x<=mid)a=query(p<<1,l,mid,x,y);
    if(y>mid)b=query(p<<1|1,mid+1,r,x,y);
    if(a.val>b.val)return a;
    else return b;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n,cnt=0;cin>>n;
    map<int,int>mp;
    for(int i=1;i<=n;++i)cin>>a[i],mp[a[i]]=1;
    for(map<int,int>::iterator it=mp.begin();it!=mp.end();++it)
        mp[it->first]=++cnt;
    for(int i=1;i<=n;++i)a[i]=mp[a[i]];

    build(1,1,n);
    for(int i=1;i<=n;++i)
    {
        dp[i]=query(1,1,n,1,a[i]);dp[i].val++;
        change(1,1,n,a[i],(node){dp[i].val,i});
    }
    int p=n;vector<int>b;
    while(p)b.push_back(p),p=dp[p].p;
    for(int i=b.size()-1;i>=0;--i)cout<<b[i]<<" ";cout<<endl;
    return 0;
}

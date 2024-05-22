#include<bits/stdc++.h>
#define MAX_N 1000010
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
int pm[MAX_N<<1];
namespace SEG
{
//特制线段树，香甜可口，标记不下传
//离散化线段树，每个节点代表一个左闭右开的区间
    ll len[MAX_N<<3],laz[MAX_N<<3];
    void up(int p,int l,int r)
    {
        if(laz[p]>0)len[p]=pm[r+1]-pm[l];
        else len[p]=len[p<<1]+len[p<<1|1];
    }
    void build(int p,int l,int r)
    {
        len[p]=laz[p]=0;
        if(l==r)return;
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        up(p,l,r);
    }
    void change(int p,int l,int r,int x,int y,int c)
    {
        if(x<=l&&r<=y)
        {
            laz[p]+=c;
            up(p,l,r);
            return;
        }
        if(x<=mid)change(p<<1,l,mid,x,y,c);
        if(y>mid)change(p<<1|1,mid+1,r,x,y,c);
        up(p,l,r);
    }
}
struct LINE
{
    int l,r,y,v;
};vector<LINE>line;
bool cmp(LINE a,LINE b)
{
    if(a.y==b.y)return a.v<b.v;
    return a.y<b.y;
}
int main()
{
    int n;cin>>n;
    map<int,int>mp;int cnt=0;
    for(int i=1;i<=n;++i)
    {
        int x,y,xx,yy;
        cin>>x>>y>>xx>>yy;
        mp[x]=mp[xx]=1;
        line.push_back((LINE){x,xx,y,1});
        line.push_back((LINE){x,xx,yy,-1});
    }
    for(map<int,int>::iterator it=mp.begin();it!=mp.end();++it)
        it->second=++cnt,pm[cnt]=it->first;
    for(int i=0;i<line.size();++i)
        line[i].l=mp[line[i].l],line[i].r=mp[line[i].r];
    sort(line.begin(),line.end(),cmp);
    SEG::build(1,1,cnt);
    ll ans=0;
    for(int i=0;i<line.size()-1;++i)
    {
        SEG::change(1,1,cnt,line[i].l,line[i].r-1,line[i].v);
        ans+=(ll)(line[i+1].y-line[i].y)*SEG::len[1];
//        cout<<line[i+1].y-line[i].y<<" "<<SEG::len[1]<<endl;
    }
    cout<<ans<<endl;
    return 0;
}

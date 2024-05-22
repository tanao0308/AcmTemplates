/*
这题的去重和答案不算自身超级恶心！
哪个sb出的这种无价值的题设？
*/
#include<bits/stdc++.h>
#define ll long long
#define MAX_N 200010
#define lowbit(x) (x&(-x))
#define mid ((l+r)>>1)
using namespace std;
int k;
struct node
{
    int a,b,c,n,cnt;
}y[MAX_N];
vector<node>x;
bool cmp(node x,node y)
{
    if(x.a==y.a)
    {
        if(x.b==y.b)
            return x.c<y.c;
        return x.b<y.b;
    }
    return x.a<y.a;
}
int sum[MAX_N];
void add(int x,int c)
{
    for(;x<=k;x+=lowbit(x))
        sum[x]+=c;
}
int query(int x)
{
    int ans=0;
    for(;x;x-=lowbit(x))
        ans+=sum[x];
    return ans;
}

//ans[i]: 有几个其他三元组小于idx=i的三元组
int ans[MAX_N],antians[MAX_N];
void solve(int l,int r)
{
    if(l==r)return;
    solve(l,mid);
    solve(mid+1,r);
    vector<node>s;
    for(int i=l;i<=mid;++i)
        s.push_back((node){x[i].b,x[i].c,0,x[i].n,x[i].cnt});
    for(int i=mid+1;i<=r;++i)
        s.push_back((node){x[i].b,x[i].c,1,x[i].n,x[i].cnt});
    sort(s.begin(),s.end(),cmp);
    for(int i=0;i<s.size();++i)
    {
        if(s[i].c==0)add(s[i].b,s[i].cnt);
        else ans[s[i].n]+=query(s[i].b);
    }
    for(int i=0;i<s.size();++i)
        if(s[i].c==0)add(s[i].b,-s[i].cnt);
}
int n;
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>y[i].a>>y[i].b>>y[i].c,y[i].cnt=1;
    sort(y+1,y+n+1,cmp);
    x.push_back(y[1]);
    for(int i=2;i<=n;++i)
    {
        if(y[i].a==y[i-1].a&&y[i].b==y[i-1].b&&y[i].c==y[i-1].c)
            x[x.size()-1].cnt++;
        else x.push_back(y[i]);
    }
    for(int i=0;i<x.size();++i)
        x[i].n=i,ans[i]=x[i].cnt-1;//一开始除了自身以外，和自身相同的三元组都算作比自身小的三元组
        
    solve(0,x.size()-1);//计算严格小于自身的三元组个数
    for(int i=0;i<x.size();++i)antians[ans[i]]+=x[i].cnt;
    for(int i=0;i<n;++i)cout<<antians[i]<<endl;
    return 0;
}

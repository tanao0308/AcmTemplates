#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 200010
using namespace std;
map<string,int>ans;
string str[MAX_N];
struct edge
{
    int v,next;
}e[MAX_N<<1];
int eid,p[MAX_N];
void insert1(int u,int v)
{
    e[++eid].v=v;
    e[eid].next=p[u];
    p[u]=eid;
}
namespace AC
{
    int idx,son[MAX_N][26],ter[MAX_N],fail[MAX_N],num[MAX_N];
    void init()
    {
        for(int i=0;i<=idx;++i)
            memset(son[i],0,sizeof son[i]),num[i]=fail[i]=ter[i]=0;
        idx=0;
    }
    void insert(string s,int n)
    {
        int p=0;
        for(int i=0;s[i];++i)
        {
            if(!son[p][s[i]-'a'])son[p][s[i]-'a']=++idx;
            p=son[p][s[i]-'a'];
        }
        ter[p]=1,num[p]=n;
    }
    void buildfail()
    {
        queue<int>q;
        for(int i=0;i<26;++i)
            if(son[0][i])
                fail[son[0][i]]=0,q.push(son[0][i]);
        while(!q.empty())
        {
            int p=q.front();q.pop();
            for(int i=0;i<26;++i)
            {
                //如果没有这个子节点，那直接指向之前可能有这个子节点的最长前缀
                if(!son[p][i])son[p][i]=son[fail[p]][i];
                //如果有子节点，子节点fail值=父节点的fail的这个子节点
                else fail[son[p][i]]=son[fail[p]][i],q.push(son[p][i]);
            }
        }
    }
    int sum[MAX_N];
    void match(string s)
    {
        int p=0;
        for(int i=0;s[i];++i)
        {
            p=son[p][s[i]-'a'];
            sum[p]++;
        }
    }
    int dfs(int u)
    {
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v;
            sum[u]+=dfs(v);
        }
        return sum[u];
    }
    void calans()
    {
        for(int i=1;i<=idx;++i)
            insert1(fail[i],i);//fail[i]深度一定<i
        dfs(0);
        for(int i=0;i<=idx;++i)
            if(ter[i])
                ans[str[num[i]]]=sum[i];
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;++i)
    {
        cin>>str[i];
        AC::insert(str[i],i);
    }
    AC::buildfail();
    string s;cin>>s;
    AC::match(s);
    AC::calans();
    for(int i=1;i<=n;++i)
        cout<<ans[str[i]]<<endl;
    return 0;
}

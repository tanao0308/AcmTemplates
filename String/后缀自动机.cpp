#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 2000010
using namespace std;
struct edge
{
    int v,next;
}e[MAX_N<<1];
int eid,p[MAX_N<<1];
void insert(int u,int v)
{
    e[++eid].v=v;
    e[eid].next=p[u];
    p[u]=eid;
}
namespace SAM
{
    int sz,last,nxt[MAX_N<<1][26],link[MAX_N<<1],len[MAX_N<<1],leaf[MAX_N<<1];
    void init()
    {
        len[0]=0,link[0]=-1,sz=1,last=0;
    }
    void extend(int c)
    {
        int cur=sz++;
        leaf[cur]=1,len[cur]=len[last]+1;
        int p=last;
        while(p!=-1&&!nxt[p][c])
            nxt[p][c]=cur,p=link[p];
        if(p==-1)link[cur]=0;
        else
        {
            int q=nxt[p][c];
            if(len[q]==len[p]+1)link[cur]=q;
            else
            {
                int clone=sz++;
                len[clone]=len[p]+1,link[clone]=link[q];
                for(int i=0;i<26;++i)nxt[clone][i]=nxt[q][i];
                while(p!=-1&&nxt[p][c]==q)
                    nxt[p][c]=clone,p=link[p];
                link[q]=link[cur]=clone;
            }
        }
        last=cur;
    }
    int siz[MAX_N];
    void dfs(int u)
    {
        if(leaf[u])siz[u]=1;
        for(int i=p[u];i;i=e[i].next)
        {
            int v=e[i].v;
            dfs(v);
            siz[u]+=siz[v];
        }
    }
    void calans()
    {
        ll ans=0;
        for(int i=1;i<sz;++i)
            insert(link[i],i);
        dfs(0);
        for(int i=1;i<sz;++i)
            if(siz[i]>1)
                ans=max(ans,(ll)len[i]*(ll)siz[i]);
        cout<<ans<<endl;
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    string s;cin>>s;
    SAM::init();
    for(int i=0;s[i];++i)
        SAM::extend(s[i]-'a');
    SAM::calans();
    return 0;
}

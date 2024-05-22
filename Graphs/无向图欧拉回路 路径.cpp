//https://www.luogu.com.cn/problem/P1341
#include<bits/stdc++.h>
#define mid ((l+r)>>1)
#define MAX_N 100010
using namespace std;
typedef long long ll;
int fa[MAX_N];
int find(int u)
{
    if(fa[u]==u)return u;
    return fa[u]=find(fa[u]);
}

int eid,d[MAX_N];
vector<pair<int,int> >g[MAX_N];
bool vis[MAX_N];string ans;
void dfs(int u)
{
	sort(g[u].begin(),g[u].end());

	// cout<<(char)u<<endl;
	// for(auto x:g[u])cout<<(char)x.first<<" ";cout<<endl;
	
	for(auto x:g[u])
	{
		if(vis[x.second])continue;
		vis[x.second]=vis[x.second^1]=1;
		dfs(x.first);
	}
	ans.push_back(u);
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    eid=1;for(int i=1;i<128;++i)fa[i]=i;
    int n;cin>>n;string a;
    while(n--)
    {
    	string s;cin>>s;
    	g[s[0]].push_back({s[1],++eid});
    	g[s[1]].push_back({s[0],++eid});

    	fa[find(s[1])]=find(s[0]);
    	a.push_back(s[0]),a.push_back(s[1]);
    	d[s[0]]++,d[s[1]]++;
    }
    for(int i=0;a[i+1];++i)
    	if(find(a[i])!=find(a[i+1]))
    		{cout<<"No Solution"<<endl;return 0;}
    sort(a.begin(),a.end());
    int sta=0,cnt=0;
    for(int i=1;i<128;++i)
    	if(d[i]&1)
    		++cnt,sta=(sta?sta:i);
    if(cnt!=2&&cnt!=0){cout<<"No Solution"<<endl;return 0;}
    sta=(sta?sta:a[0]);
    dfs(sta);reverse(ans.begin(),ans.end());
    cout<<ans<<endl;
    return 0;
}
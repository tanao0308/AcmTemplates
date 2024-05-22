#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 3000010
using namespace std;
namespace TRIE
{
    int getnum(char x)
    {
        if(x>='A'&&x<='Z')
            return x-'A';
        else if(x>='a'&&x<='z')
            return x-'a'+26;
        else
            return x-'0'+52;
    }
    int idx,son[MAX_N][80],cnt[MAX_N];
    void init(int p)
    {
        idx=0;
        for(int i=0;i<26+26+10;++i)
            if(son[p][i])
                init(son[p][i]),son[p][i]=0;
        cnt[p]=0;
    }
    void insert(string s)
    {
        int p=0;
        for(int i=0;s[i];++i)
        {
            int num=getnum(s[i]);
            if(!son[p][num])son[p][num]=++idx;
            p=son[p][num];
            cnt[p]++;
        }
    }
    int query(string t)
    {
        int p=0;
        for(int i=0;t[i];++i)
        {
            int num=getnum(t[i]);
            if(!son[p][num])return 0;
            p=son[p][num];
        }
        return cnt[p];
    }
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int T;cin>>T;
    while(T--)
    {
        TRIE::init(0);
        int n,m;cin>>n>>m;
        string s;
        for(int i=1;i<=n;++i)
        {
            cin>>s;
            TRIE::insert(s);
        }
        while(m--)
        {
            cin>>s;
            cout<<TRIE::query(s)<<endl;
        }
    }
    return 0;
}

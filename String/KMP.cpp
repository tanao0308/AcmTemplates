#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
#define MAX_N 1000010
using namespace std;
namespace KMP
{
	int nxt[MAX_N];
	void getnxt(string t)
	{
	    int len=t.length();
	    nxt[0]=-1;
	    for(int i=1,p=-1;i<len;++i)
	    {
	        while(p!=-1&&t[i]!=t[p+1])p=nxt[p];
	        if(t[p+1]==t[i])p++;
	        nxt[i]=p;
	    }
	}
	void kmp(string s,string t)
	{
		getnxt(t);
	    int ls=s.length(),lt=t.length();
	    for(int i=0,p=-1;i<ls;++i)
	    {
	        while(p!=-1&&s[i]!=t[p+1])p=nxt[p];
	        if(t[p+1]==s[i])p++;
	        if(p==lt-1)
	        {
	            cout<<i-lt+2<<endl;
	            p=nxt[p];
	        }
	    }
	    for(int i=0;i<lt;++i)
	        cout<<nxt[i]+1<<" ";cout<<endl;
	}
}
int main()
{
    string s,t;cin>>s>>t;
    KMP::kmp(s,t);
    return 0;
}

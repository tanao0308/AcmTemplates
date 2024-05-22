/*
一些质数：
    1e2+
101 103 107 109 113
127 131 137 139 149

    1e3+
1009 1013 1019 1021 1031
1033 1039 1049 1051 1061

    1e7-
9999889 9999901 9999907 9999929 9999931
9999937 9999943 9999971 9999973 9999991

    1e9+
1000000007 1000000009 1000000021 1000000033 1000000087
1000000093 1000000097 1000000103 1000000123 1000000181
*/
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
int mod[10]={131,137,139,149,151,157,163,167,173,179};
int MOD[10]={9999889,9999901,9999907,9999929,9999931,9999937,9999943,9999971,9999973,9999991};
char s[1510];
bool vis[2][10000000];
int hsh(char*s,int mod,int MOD)
{
    ll ans=0;
    for(int i=0;s[i];++i)
        ans=(ans*mod+s[i])%MOD;
    return ans;
}
int main()
{
    srand(time(NULL));
    int h1=rand()%10,h2=rand()%10;
    while(h2==h1)h2=rand()%10;
    int H1=rand()%10,H2=rand()%10;
    while(H2==H1)H2=rand()%10;
    
    int n;
    cin>>n;
    int ans=0;
    for(int i=1;i<=n;++i)
    {
        cin>>s;
        int ha=hsh(s,mod[h1],MOD[H1]),hb=hsh(s,mod[h2],MOD[H2]);
        if(vis[0][ha]&&vis[1][hb])continue;
        ans++;
        vis[0][ha]=1;
        vis[1][hb]=1;
    }
    cout<<ans<<endl;
    return 0;
}

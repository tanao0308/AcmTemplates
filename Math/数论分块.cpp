#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
int main()
{
    ll T;cin>>T;
    while(T--)
    {
        ll n;
        cin>>n;
        
        ll ans=0;
        for(int l=1,r;l<=n;l=r+1)
        {
            r=n/(n/l);
            ans+=(r-l+1)*(n/l);
        }
        cout<<ans<<endl;
    }
    return 0;
}

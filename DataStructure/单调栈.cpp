#include<bits/stdc++.h>
#define ll long long
#define MAX_N 3000010
using namespace std;
struct node
{
    int v,n;
};
int a[MAX_N],lbg[MAX_N];
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<=n;++i)scanf("%d",&a[i]);
    
    stack<node>s;s.push((node){(int)1e9,0});
    for(int i=n;i>=1;--i)
    {
        while(s.top().v<=a[i])s.pop();
        lbg[i]=s.top().n;
        s.push((node){a[i],i});
    }
    for(int i=1;i<=n;++i)printf("%d ",lbg[i]);
    return 0;
}

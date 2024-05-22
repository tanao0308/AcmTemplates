#include<bits/stdc++.h>
#define ll long long
#define MAX_N 1000010
using namespace std;
struct node
{
    int v,n;
};
int a[MAX_N],minn[MAX_N],maxx[MAX_N];
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;++i)cin>>a[i];
    
    //min
    deque<node>q;//求最小值维护一个队头最小的递增序列
    for(int i=1;i<k;++i)
    {
        while(!q.empty()&&q.back().v>=a[i])q.pop_back();
        q.push_back((node){a[i],i});
    }
    for(int i=k;i<=n;++i)
    {
        while(!q.empty()&&q.front().n+k-1<i)q.pop_front();
        while(!q.empty()&&q.back().v>=a[i])q.pop_back();
        q.push_back((node){a[i],i});
        minn[i]=q.front().v;
    }
    for(int i=k;i<=n;++i)cout<<minn[i]<<" ";cout<<endl;

    q.clear();
    for(int i=1;i<k;++i)
    {
        while(!q.empty()&&q.back().v<=a[i])q.pop_back();
        q.push_back((node){a[i],i});
    }
    for(int i=k;i<=n;++i)
    {
        while(!q.empty()&&q.front().n+k-1<i)q.pop_front();
        while(!q.empty()&&q.back().v<=a[i])q.pop_back();
        q.push_back((node){a[i],i});
        maxx[i]=q.front().v;
    }
    for(int i=k;i<=n;++i)cout<<maxx[i]<<" ";cout<<endl;
    return 0;
}

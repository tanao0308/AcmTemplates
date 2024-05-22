#include<bits/stdc++.h>
#define MAX_N 11000010
using namespace std;
int man[MAX_N<<1];
void manacher(char*str,int n)
{
    for(int i=0;i<n;++i)man[i]=0;
    
    // (maxp,maxr)：当前最大 p+r的下标和对称半径，初始化为 idx=0 的值
    int maxp=0,maxr=0;
    for(int i=1;i<n;++i)
    {
        int mirror_i=2*maxp-i;
        if(maxp+maxr>=i)man[i]=min(man[mirror_i],maxp+maxr-i);//这里一定要取 min
        
        //这里不用分类讨论了，直接更新，如果不满足条件会自动停下来的
        while(i-man[i]-1>=0&&i+man[i]+1<n&&str[i-man[i]-1]==str[i+man[i]+1])
            man[i]++;
            
        if(i+man[i]>=maxp+maxr)
            maxp=i,maxr=man[i];
    }
    str[n]='\0';cout<<str<<endl;
    for(int i=0;i<n;++i)cout<<man[i]<<" ";cout<<endl;
}
int n;
char s[MAX_N],t[MAX_N<<1];
int main()
{
    cin>>s;n=strlen(s);
    for(int i=0;i<n;++i)
        t[2*i]='#',t[2*i+1]=s[i];
    t[2*n]='#',n=2*n+1;
    manacher(t,n);
    int ans=0;
    for(int i=0;i<n;++i)ans=max(ans,man[i]);
    cout<<ans<<endl;
    return 0;
}

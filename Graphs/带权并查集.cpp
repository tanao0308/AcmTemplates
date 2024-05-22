//NOI2001 食物链
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
struct node
{
    int f,v;//上一级结点 | 到上级节点的距离
}uni[500010];
void update(int x)//返回x的集合的根节点，同时更新x的信息
{
    if(uni[x].f==x)return;
    update(uni[x].f);//首先更新父节点
    
    uni[x].v=(uni[x].v+uni[uni[x].f].v)%3;
    uni[x].f=uni[uni[x].f].f;
}
void merge(int x,int y,int d)//将 y接到 x后面，和 x的距离为 d （这里merge操作的一定是根节点）
{
    uni[y].f=x;
    uni[y].v=(d+3)%3;//这里先不急着更新
}
int main()
{
    int n,k;
    cin>>n>>k;
    for(int i=1;i<=n;++i)uni[i].f=i;
    int ans=0;
    while(k--)
    {
        int op,x,y;
        cin>>op>>x>>y;
        if(max(x,y)>n)
        {
            ans++;
            continue;
        }
        
        update(x),update(y);
        int rx=uni[x].f,ry=uni[y].f;//顺便更新了uni[x]和uni[y]
        if(op==1)
        {
            if(rx==ry&&uni[x].v!=uni[y].v)
                ans++;
                //因为x和y是同类，所以将x和y合并，x的天敌同时也是y的天敌，x的猎物同时是y的猎物
            else merge(rx,ry,uni[x].v-uni[y].v);//这里合并为了让 x和 y是同类，而不是让他们的祖先是同类
        }
        else
        {
            if(rx==ry&&(uni[x].v+1)%3!=uni[y].v)//x吃y
                ans++;
            else merge(rx,ry,uni[x].v-uni[y].v+1);
        }
    }
    cout<<ans<<endl;
    return 0;
}

//NOI2001 ʳ����
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
struct node
{
    int f,v;//��һ����� | ���ϼ��ڵ�ľ���
}uni[500010];
void update(int x)//����x�ļ��ϵĸ��ڵ㣬ͬʱ����x����Ϣ
{
    if(uni[x].f==x)return;
    update(uni[x].f);//���ȸ��¸��ڵ�
    
    uni[x].v=(uni[x].v+uni[uni[x].f].v)%3;
    uni[x].f=uni[uni[x].f].f;
}
void merge(int x,int y,int d)//�� y�ӵ� x���棬�� x�ľ���Ϊ d ������merge������һ���Ǹ��ڵ㣩
{
    uni[y].f=x;
    uni[y].v=(d+3)%3;//�����Ȳ����Ÿ���
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
        int rx=uni[x].f,ry=uni[y].f;//˳�������uni[x]��uni[y]
        if(op==1)
        {
            if(rx==ry&&uni[x].v!=uni[y].v)
                ans++;
                //��Ϊx��y��ͬ�࣬���Խ�x��y�ϲ���x�����ͬʱҲ��y����У�x������ͬʱ��y������
            else merge(rx,ry,uni[x].v-uni[y].v);//����ϲ�Ϊ���� x�� y��ͬ�࣬�����������ǵ�������ͬ��
        }
        else
        {
            if(rx==ry&&(uni[x].v+1)%3!=uni[y].v)//x��y
                ans++;
            else merge(rx,ry,uni[x].v-uni[y].v+1);
        }
    }
    cout<<ans<<endl;
    return 0;
}

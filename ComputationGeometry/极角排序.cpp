#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
struct pit
{
	ll x,y;
}a[2000010];
//������������
bool up(pit a){return a.y>0||(a.y==0&&a.x>=0);}//��x���ϲ�����x�������ᣩ
bool cmp(pit a,pit b)
{//��ԭ��Ϊ��׼�㣬��x�������Ὺʼ��ʱ������
	if(up(a)!=up(b))return up(a)>up(b);
    return a.x*b.y-a.y*b.x>0;
}
//�������ø�����
//bool cmp(node a,node b)
//{
//	return atan2((long double)a.x,(long double)a.y)>atan2((long double)b.x,(long double)b.y);
//}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    ll T;cin>>T;
    while(T--)
    {
    	ll n;cin>>n;
	    for(ll i=0;i<n;++i)
	    	cin>>a[i].x>>a[i].y;
        sort(a,a+n,cmp);
        for(int i=0;i<n;++i)cout<<a[i].x<<" "<<a[i].y<<endl;
    }
	return 0;
}

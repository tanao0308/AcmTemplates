//��Ҫ��ͬ�෽��ģ������ 
#include<bits/stdc++.h>
#define LL __int128
#define ll long long
#define MAX_N 100010
using namespace std;
void exgcd(LL a,LL b,LL&k1,LL&k2)
{
    if(a==0)
    {
        k1=0,k2=1;
        return;
    }
    exgcd(b%a,a,k1,k2);
    LL kk1=k1,kk2=k2;
    k2=kk1;
    k1=kk2-k2*(b/a);
}
pair<LL,LL>excrt(pair<LL,LL>f1,pair<LL,LL>f2)//�ϲ� f1 �� f2 ����ͬ�෽��
{
    LL r1=f1.first,m1=f1.second;
    LL r2=f2.first,m2=f2.second;
    if(r1==-1||r2==-1)return {-1,-1};
    LL d=__gcd(m1,m2),k1,k2;
    exgcd(m1,m2,k1,k2);
    if((r2-r1)%d)return {-1,-1};//�޽ⷵ��-1 
    LL M=m1/d*m2;
    LL R=(((r2-r1)/d*k1%M*m1%M+r1)%M+M)%M;//R=(r2-r1)/d*k1*m1+r1
    //������ȡ r1 ��ģ�Ϊ�˱������r1Ӧ��������С������Ӧ������ֵС��ͬ�෽�̷�ǰ�棡����
    return {R,M};
}
pair<ll,ll>func[MAX_N];
int main()
{
    ll n;cin>>n;
    for(LL i=1;i<=n;++i)
        cin>>func[i].second>>func[i].first;//���� x = first (mod second)  ->  x=r mod m
    for(LL i=2;i<=n;++i)
        func[i]=excrt(func[i],func[i-1]);//��ذ���С�ķ�ǰ�棡������Ȼ�������
//    cout<<func[n].first<<" "<<func[n].second<<endl;
	cout<<func[n].first<<endl;
    return 0;
}
/*
3
1 2
2 3
3 5
*/

#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
int main()
{
    int l=1,r=1e9,ans=1;
    while(l<=r)
    {
        if(check(mid))ans=mid,l=mid+1;
        else r=mid-1;
    }
    return 0;
}
/*
	�������У�lower_bound ���ص�һ�����ڵ���x��λ�ã�upper_bound ���ص�һ������x��λ��
	�½����У�lower_bound ���ص�һ��С�ڵ���x��λ�ã�upper_bound ���ص�һ��С��x��λ�ã�Ҫ����ȽϺ���
*/

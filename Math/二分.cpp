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
	上升序列：lower_bound 返回第一个大于等于x的位置，upper_bound 返回第一个大于x的位置
	下降序列：lower_bound 返回第一个小于等于x的位置，upper_bound 返回第一个小于x的位置，要定义比较函数
*/

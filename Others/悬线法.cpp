/*
求网格中最大的全1|全0子矩阵
*/
#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
bool a[2010][2010];
int h[2010],l[2010],r[2010];
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
			cin>>a[i][j];
	int ans=0;
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=m;++j)
			if(a[i][j]==a[i-1][j])h[j]++;
			else h[j]=1;
		for(int j=0;j<=m+1;++j)l[j]=j,r[j]=j;
		for(int j=1;j<=m;++j)
			while(l[l[j]-1]>=1&&h[l[j]-1]>=h[j]&&a[i][j]==a[i][l[j]-1])
				l[j]=l[l[j]-1];
		for(int j=m;j>=1;--j)
			while(r[r[j]+1]<=m&&h[r[j]+1]>=h[j]&&a[i][j]==a[i][r[j]+1])
				r[j]=r[r[j]+1];
		for(int j=1;j<=m;++j)
			ans=max(ans,h[j]*(r[j]-l[j]+1));
	}
	cout<<ans<<endl;
	return 0;
}

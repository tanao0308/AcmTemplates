#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
const ll MAX_N=(1<<19)+9;
const long double Pi=acos(-1);
typedef complex<long double> comp;
void fft(comp a[],int n,int on)
{
	static comp w[MAX_N<<2];w[0].real(1);
	for(int i=0,j=0;i<n;i++)
	{
		if(i>j)swap(a[i],a[j]);
		for(int l=n/2;(j^=l)<l;l/=2);
	}
	for(int i=1;i<n;i*=2)
	{
		comp wn(cos(Pi/i),on*sin(Pi/i));
		for(int j=(i-2)/2;~j;j--)
			w[j*2+1]=(w[j*2]=w[j])*wn;
		for(int j=0;j<n;j+=i*2)
			for(int k=j;k<j+i;k++)
			{
				comp x=a[k],y=a[k+i]*w[k-j];
				a[k]=x+y,a[k+i]=x-y;
			}
	}
	if(on!=1)for(int i=0;i<n;i++)a[i]/=n;
}
template<typename T>
void operator*=(vector<T>&a,vector<T>&b)
{
	static comp c[MAX_N<<2],d[MAX_N<<2];
	int n=a.size(),m=b.size(),len=1<<int(ceil(log2(n+m)));
	for(int i=0;i<n;++i)c[i]=a[i];
	fill(c+n,c+len,comp());
	for(int i=0;i<m;++i)d[i]=b[i];
	fill(d+m,d+len,comp());
	fft(c,len,1),fft(d,len,1);
	for(int i=0;i<len;++i)c[i]*=d[i];
	fft(c,len,-1);
	a.resize(len=n+m-1);
	for(int i=0;i<len;++i)a[i]=c[i].real()+0.5;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
	int n,m;cin>>n>>m;
	double x;vector<int>a,b;
	for(int i=0;i<=n;++i)cin>>x,a.push_back(x);
	for(int i=0;i<=m;++i)cin>>x,b.push_back(x);
	a*=b;
	for(int i=0;i<a.size();++i)cout<<a[i]<<" ";cout<<endl;
	return 0;
}

int phi(int n)
{
	int t=1,i;
	if(!(n&1))for(n>>=1;!(n&1);n>>=1,t<<=1);
	for(i=3;i*i<=n;i+=2)if(n%i==0)for(n/=i,t*=i-1;n%i==0;n/=i,t*=i);
	if(n>1)t*=n-1;
	return t;
}
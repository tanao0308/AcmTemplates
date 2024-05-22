#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Poly
{
    template<const int Mod> struct ModInt
    {
        int x;
        ModInt(int X=0):x(X) {}
        inline ModInt operator = (int &T) {this->x=T; return *this;}
        inline ModInt operator = (const ModInt &T) {this->x=T.x; return *this;}
        inline friend ModInt operator + (ModInt a,ModInt b) {return a.x+b.x>=Mod?a.x+b.x-Mod:a.x+b.x;}
        inline friend ModInt operator - (ModInt a,ModInt b) {return a.x-b.x<0?a.x-b.x+Mod:a.x-b.x;}
        inline friend ModInt operator * (ModInt a,ModInt b) {return a.x*b.x%Mod;}
        inline friend ModInt operator ^ (ModInt a,int b) {ModInt res=1; while(b) {if(b&1) res=res*a; a=a*a; b>>=1;} return res;}
        inline friend ModInt operator / (ModInt a,ModInt b) {return a*(b^(Mod-2));}
        inline ModInt operator += (const ModInt &T) {*this=*this+T; return *this;}
        inline ModInt operator -= (const ModInt &T) {*this=*this-T; return *this;}
        inline ModInt operator *= (const ModInt &T) {*this=*this*T; return *this;}
        inline ModInt operator ^= (const ModInt &T) {*this=*this^T; return *this;}
        inline ModInt operator /= (const ModInt &T) {*this=*this/T; return *this;}
        template<typename T> inline friend ModInt operator + (ModInt a,T x) {return a+ModInt(x);}
        template<typename T> inline friend ModInt operator - (ModInt a,T x) {return a-ModInt(x);}
        template<typename T> inline friend ModInt operator * (ModInt a,T x) {return a*ModInt(x);}
        template<typename T> inline friend ModInt operator / (ModInt a,T x) {return a/ModInt(x);}
        inline friend bool operator == (ModInt a,ModInt b) {return a.x==b.x;}
        inline friend bool operator != (ModInt a,ModInt b) {return a.x!=b.x;}
        inline friend bool operator >  (ModInt a,ModInt b) {return a.x>b.x;}
        inline friend bool operator <  (ModInt a,ModInt b) {return a.x<b.x;}
        inline friend bool operator >= (ModInt a,ModInt b) {return a>b||a==b;}
        inline friend bool operator <= (ModInt a,ModInt b) {return a<b||a==b;}
        template<typename T> inline friend bool operator == (ModInt a,T b) {return a==ModInt(b);}
        template<typename T> inline friend bool operator != (ModInt a,T b) {return a!=ModInt(b);}
        template<typename T> inline friend bool operator >  (ModInt a,T b) {return a>ModInt(b);}
        template<typename T> inline friend bool operator <  (ModInt a,T b) {return a<ModInt(b);}
        template<typename T> inline friend bool operator >= (ModInt a,T b) {return a>=ModInt(b);}
        template<typename T> inline friend bool operator <= (ModInt a,T b) {return a<=ModInt(b);}
        inline bool operator ! () {return !x;}
        inline ModInt operator - () {return x?Mod-x:0;}
    };
    static const int Mod=998244353;
    static const int MAX=4000010;
    static const double PI=acos(-1);
    static const ModInt<Mod> gn=332748118,gni=3,ZERO=0,ONE=1;
    
    namespace Quadraticresidue
    {
        ModInt<Mod> I;
        struct Complex
        {
            ModInt<Mod> x,y;
            Complex(ModInt<Mod> X=0,ModInt<Mod> Y=0):x(X),y(Y) {}
            inline friend bool operator == (Complex a,Complex b) {return a.x==b.x&&a.y==b.y;}
            inline friend Complex operator * (Complex a,Complex b) {return Complex(a.x*b.x+a.y*b.y*I,a.x*b.y+a.y*b.x);}
        };
        inline Complex qpow(Complex a,int b) {Complex res(1,0); while(b) {if(b&1) res=res*a; a=a*a; b>>=1;} return res;}
        inline ModInt<Mod> random(int l,int r)
        {
            static mt19937_64 sd(20070707);
            static uniform_int_distribution<int> range(l,r);
            return ModInt<Mod>(range(sd));
        }
        inline pair<ModInt<Mod>,ModInt<Mod>> Cipointa(ModInt<Mod> n)
        {
            if(!n) return make_pair(0,0);
            ModInt<Mod> x,x1,x2;
            do x=random(1,Mod-1); while(((x*x+Mod-n)^((Mod-1)>>1))==ONE);
            I=x*x+Mod-n,x1=qpow(Complex(x,1),(Mod+1)>>1).x,x2=Mod-x1;
            return make_pair(min(x1,x2),max(x1,x2));
        }
    }
    using namespace Quadraticresidue;
    
    struct poly
    {
        vector<ModInt<Mod>> a;
        inline ModInt<Mod> &operator [] (int i) {return a[i];}
        inline poly operator = (const poly &T) {this->a=T.a; return *this;}
        inline int size()         {return a.size();}
        inline void resize(int N) {return a.resize(N),void();}
        inline void reverse()     {return std::reverse(a.begin(),a.end());}
        inline void pin(int x)    {return a.emplace_back(ModInt<Mod>(x)),void();}
        inline void pout()        {for(auto it:a) cout<<it.x<<' ';}
    };
    
    inline int Sup(int N) {int K=1; while(K<N) K<<=1; return K;}
    
    static const int GT=21,GR=31;
    ModInt<Mod> omega[MAX]; poly zero,one;
    inline void Prework(int N)
    {
        zero.a.emplace_back(ZERO),one.a.emplace_back(ONE);
        int K=1; while((1<<K)<N) ++K; K=min(K-1,(int)21);
        omega[0]=1,omega[1<<K]=(ModInt<Mod>(GR))^(1<<(GT-K));
        for(int i=K;i>=1;--i) omega[1<<(i-1)]=omega[1<<i]*omega[1<<i];
        for(int i=1;i<(1<<K);++i) omega[i]=omega[i&(i-1)]*omega[i&(-i)];
    }
    inline void NTT(poly &F,int typ)
    {
        ModInt<Mod> U,V;
        int N=F.size();
        if(typ==1)
        {
            for(int mid=N>>1;mid>=1;mid>>=1)
                for(int i=0,k=0;i<N;i+=mid<<1,++k)
                    for(int j=0;j<mid;++j)
                        U=F[i+j],V=F[i+j+mid]*omega[k],
                        F[i+j]=U+V,F[i+j+mid]=U-V;
        }
        if(typ==-1)
        {
            for(int mid=1;mid<N;mid<<=1)
                for(int i=0,k=0;i<N;i+=mid<<1,++k)
                    for(int j=0;j<mid;++j)
                        U=F[i+j],V=F[i+j+mid],
                        F[i+j]=U+V,F[i+j+mid]=(U-V)*omega[k];
            ModInt<Mod> Ninv=ONE/N;
            for(int i=0;i<N;++i) F[i]*=Ninv;
            reverse(F.a.begin()+1,F.a.end());
        }
    }
    inline poly operator * (poly a,ModInt<Mod> b) {for(int i=0;i<a.size();++i) a[i]*=b; return a;}
    inline poly operator / (poly a,ModInt<Mod> b) {for(int i=0;i<a.size();++i) a[i]/=b; return a;}
    inline poly operator - (poly a) {for(int i=0;i<a.size();++i) a[i]=-a[i]; return a;}
    inline poly operator + (poly a,poly b)
    {
        int N=max(a.size(),b.size());
        a.resize(N),b.resize(N);
        for(int i=0;i<N;++i) a[i]+=b[i];
        return a;
    }
    inline poly operator - (poly a,poly b)
    {
        int N=max(a.size(),b.size());
        a.resize(N),b.resize(N);
        for(int i=0;i<N;++i) a[i]-=b[i];
        return a;
    }
    inline poly operator * (poly a,poly b)
    {
        int K=a.size()+b.size()-1,N=Sup(K);
        a.resize(N),b.resize(N);
        NTT(a,1),NTT(b,1);
        for(int i=0;i<N;++i) a[i]*=b[i];
        NTT(a,-1);
        a.resize(K);
        return a;
    }
    inline poly operator >> (poly a,int d)
    {
        int N=a.size(); poly b; 
        b.resize(N+d);
        for(int i=0;i<N;++i) b[i+d]=a[i];
        return b; 
    }
    inline poly operator << (poly a,int d)
    {
        int N=a.size(); if(N<=d) return zero;
        poly b; b.resize(N-d);
        for(int i=0;i<N-d;++i) b[i]=a[i+d];
        return b;
    }
    inline poly Dvt(poly a)
    {
        int N=a.size()-1;
        for(int i=0;i<N;++i) a[i]=a[i+1]*(i+1);
        return a.resize(N),a;
    }
    inline poly Itg(poly a)
    {
        int N=a.size()+1; a.resize(N);
        for(int i=N;i>=1;--i) a[i]=a[i-1]/i;
        return a[0]=0,a;
    }
    inline poly Inv(poly a)
    {
        int K=a.size(),N=Sup(K);
        poly b,c,d; a.resize(N),b.resize(N);
        b[0]=ONE/a[0];
        for(int len=2;len<=N;len<<=1)
        {
            c.resize(len),d.resize(len);
            for(int i=0;i<len;++i) c[i]=a[i];
            for(int i=0;i<(len>>1);++i) d[i]=b[i];
            NTT(c,1),NTT(d,1);
            for(int i=0;i<len;++i) c[i]=c[i]*d[i];
            NTT(c,-1); for(int i=1;i<(len>>1);++i) c[i]=0; c[0]=Mod-1;
            NTT(c,1);  for(int i=0;i<len;++i) d[i]=d[i]*c[i];
            NTT(d,-1); for(int i=len>>1;i<len;++i) b[i]=-d[i];
        }
        b.resize(K);
        return b;
    }
    inline poly operator / (poly a,poly b)
    {
        int N=a.size(),M=b.size();
        poly c=a,d=b;
        c.reverse(),d.reverse();
        d.resize(N-M+1),d=Inv(d);
        c=c*d;c.resize(N-M+1),c.reverse();
        return c;
    }
    inline poly operator % (poly a,poly b)
    {
        int M=b.size();
        poly q=a/b; b=b*q;
        poly r=a-b; r.resize(M-1);
        return r;
    }
    inline pair<poly,poly> Div(poly a,poly b)
    {
        int M=b.size();
        poly q=a/b; b=b*q;
        poly r=a-b; r.resize(M-1);
        return make_pair(q,r);
    }
    
    namespace DivideConquer
    {
        poly F[20][8],G[20][8];
        inline void brute(poly &a,poly &b,int l,int r,void work(poly &a,poly &b,int i))
        {
            work(a,b,l);
            for(int i=l+1;i<=r;++i) 
            {
                for(int j=l;j<i;++j) a[i]+=a[j]*b[i-j];
                work(a,b,i);
            }
        }
        inline void Divide(poly &a,poly &b,int l,int r,int dep,void work(poly &a,poly &b,int i))
        {
            if(r-l+1<=32) return brute(a,b,l,r,work);
            if(l>=r) return;
            int coef=1<<((dep-1)*3);
            poly tmp; tmp.resize(coef<<1);
            for(int i=0;;++i)
            {
                int L=l+i*coef,R=min(r,L+coef-1);
                if(i)
                {
                    for(int j=0;j<(coef<<1);++j) tmp[j]=0;
                    for(int j=0;j<i;++j) for(int k=0;k<(coef<<1);++k) tmp[k]+=F[dep][j][k]*G[dep][i-j][k];
                    NTT(tmp,-1);
                    for(int j=L;j<=R;++j) a[j]+=tmp[j-L+coef];
                }
                Divide(a,b,L,R,dep-1,work);
                if(R==r) return;
                for(int j=0;j<(coef<<1);++j) F[dep][i][j]=0;
                for(int j=L;j<=R;++j) F[dep][i][j-L]=a[j];
                NTT(F[dep][i],1);
            }
        }
        inline void solve(poly &a,poly &b,int N,void work(poly &a,poly &b,int i))
        {
            if(N<=128) return brute(a,b,0,N-1,work);
            int len=1,dep=0;
            while(len<N) len<<=3,++dep;
            len>>=3;
            for(int i=1;i<=dep;++i)
            {
                int coef=1<<((i-1)*3),mix=min((N-1)/coef,(int)7);
                for(int j=1;j<=mix;++j)
                {
                    int L=(j-1)*coef+1,R=min(N-1,(j+1)*coef-1);
                    F[i][j-1].resize(coef<<1),G[i][j].resize(coef<<1);
                    for(int k=0;k<(coef<<1);++k) G[i][j][k]=0;
                    for(int k=L;k<=R;++k) G[i][j][k-L+1]=b[k];
                    NTT(G[i][j],1);
                }
            }
            Divide(a,b,0,N-1,dep,work);
        }
    }
    using namespace DivideConquer;
    
    inline void workln(poly &a,poly &b,int i)
    {
        if(!i) a[i]=0;
        else a[i]=i*b[i]-a[i];
    }
    inline poly Ln(poly a)
    {
        int N=a.size();
        poly b; b.resize(N);
        solve(b,a,N,workln);
        b[0]=0; for(int i=1;i<N;++i) b[i]*=ONE/i;
        return b;
    }
    inline void workexp(poly &a,poly &b,int i)
    {
        if(!i) a[i]=1;
        else a[i]*=ONE/i;
    }
    inline poly Exp(poly a)
    {
        int N=a.size();
        for(int i=0;i<N;++i) a[i]=a[i]*i;
        poly b; b.resize(N);
        solve(b,a,N,workexp);
        return b;
    }
    inline void PrePow(char *s,int &k1,int &k2,int &k3)
    {
        int len=strlen(s+1);
        for(int i=1;i<=len;++i) k1=((k1*10)+(s[i]^48))%Mod,k2=((k2*10)+(s[i]^48))%(Mod-1);
        for(int i=1;i<=min((int)7,len);++i) k3=(k3*10)+(s[i]^48);
    }
    inline poly Pow(poly a,ModInt<Mod> b)
    {
        int N=a.size();
        a=Exp(Ln(a)*b),a.resize(N);
        return a;
    }
    inline poly Pow(poly a,char *s)
    {
        int N=a.size(),lst=N;
        ModInt<Mod> k1,k2,k3;
        PrePow(s,k1.x,k2.x,k3.x);
        poly b; b.resize(N);
        if(a[0]==0&&k3>=N) return b;
        for(int i=0;i<N;++i) if(a[i]!=0) {lst=i; break;}
        if(lst*k1>=N) return b;
        ModInt<Mod> inv=ONE/a[lst],p=a[lst]^(k2.x);
        for(int i=0;i<N-lst;++i) a[i]=a[i+lst]*inv;
        for(int i=N-lst;i<N;++i) a[i]=0;
        a=Ln(a); for(int i=0;i<N;++i) a[i]*=k1;
        a=Exp(a),lst=lst*k1.x; for(int i=N-1;i>=lst;--i) b[i]=a[i-lst]*p;
        return b;
    }
    inline poly Sqr(poly a,int typ)
    {
        int K=a.size(),N=Sup(K);
        poly f,g,h,tmp,res,ans; 
        f.resize(N),g.resize(N),h.resize(N),res.resize(1);
        f[0]=g[0]=Cipointa(a[0]).first,h[0]=ONE/g[0];
        for(int len=2;len<=N;len<<=1)
        {
            tmp.resize(len),ans.resize(len);
            for(int i=0;i<(len>>1);++i) tmp[i]=h[i],res[i]=g[i]*g[i];
            NTT(res,-1); for(int i=0;i<(len>>1);++i) ans[i+(len>>1)]=res[i]-a[i]-a[i+(len>>1)],ans[i]=0;
            NTT(ans,1),NTT(tmp,1); for(int i=0;i<len;++i) ans[i]*=tmp[i]*(ONE/2);
            NTT(ans,-1); for(int i=len>>1;i<len;++i) f[i]=-ans[i];
            if(len!=N||typ==-1) 
            {
                res.resize(len); for(int i=0;i<len;++i) res[i]=f[i];
                NTT(res,1);  for(int i=0;i<len;++i) g[i]=res[i],res[i]*=tmp[i];
                NTT(res,-1); res[0]=Mod-1; for(int i=1;i<(len>>1);++i) res[i]=0;
                NTT(res,1);  for(int i=0;i<len;++i) res[i]*=tmp[i];
                NTT(res,-1); for(int i=len>>1;i<len;++i) h[i]=-res[i];
            }
        }
        f.resize(K),h.resize(K);
        if(typ==1) return f; else return h;
    }
    inline poly sin(poly a)
    {
        ModInt<Mod> E=((ModInt<Mod>(3))^((Mod-1)>>2));
        return (Exp(a*E)-Exp(a*(-E)))*((E*2)^(Mod-2));
    }
    inline poly cos(poly a)
    {
        ModInt<Mod> E=((ModInt<Mod>(3))^((Mod-1)>>2));
        return (Exp(a*E)+Exp(a*(-E)))*((Mod+1)>>1);
    }
    inline poly tan(poly a)
    {
        int N=a.size();
        a=sin(a)*Inv(cos(a)),a.resize(N);
        return a;
    }
    inline poly arcsin(poly a)
    {
        int N=a.size();
        poly b=a*a; b.resize(N),b=-b,b[0]+=1;
        a=Itg(Dvt(a)*Sqr(b,-1)); a.resize(N);
        return a;
    }
    inline poly arctan(poly a)
    {
        int N=a.size();
        poly b=a*a; b.resize(N),b[0]+=1;
        a=Itg(Dvt(a)*Inv(b)); a.resize(N);
        return a;
    }
}
using namespace Poly;

signed main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int T;cin>>T;
    for(int tt=1;tt<=T;++tt)
    {cout<<"Case "<<tt<<": ";
    	int n,l,m;cin>>n>>l>>m;Prework(n<<1);
    	poly a,f;a.resize(n);f.resize(n);
    	for(int i=0;i<n;++i)cin>>a[n-1-i].x;
    	for(int i=0;i<l;++i)f[i].x=1;
    	for(int i=l;i<n;++i)f[i].x=0;
    	a=Pow(f,m)*a;a.resize(n);
    	for(int i=n-1;i>=0;--i)cout<<a[i].x<<" ";cout<<endl;
    }
    return 0;
}
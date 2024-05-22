#include<bits/stdc++.h>
#define ll long long
#define mid ((l+r)>>1)
using namespace std;
const double inf0=1e-10;
struct pit
{
    double c[2];
    pit(){c[0]=0;c[1]=0;};
    pit(double x,double y){c[0]=x;c[1]=y;};
    bool operator==(const pit&b)const
    {
    	return (fabs(c[0]-b.c[0])<inf0&&fabs(c[1]==b.c[1])<inf0);
    }
    double&operator[](int i){return c[i];};
    double operator[](int i) const {return c[i];};
};
pit operator+(pit a,pit b){pit ans(a[0]+b[0],a[1]+b[1]);return ans;}
pit operator-(pit a,pit b){pit ans(a[0]-b[0],a[1]-b[1]);return ans;}
pit operator*(pit a,const double s){pit ans(a[0]*s,a[1]*s);return ans;}
pit operator/(pit a,const double s){pit ans(a[0]/s,a[1]/s);return ans;}
double operator^(pit a,pit b){return (a[0]*b[1]-a[1]*b[0]);}
double operator*(pit a,pit b){return a[0]*b[0]+a[1]*b[1];}
double dis(pit a,pit b){return sqrt((a[0]-b[0])*(a[0]-b[0])+(a[1]-b[1])*(a[1]-b[1]));}
	
pit spt;
bool cmp(pit a,pit b)
{//逆时针排序
    double cross=(a-spt)^(b-spt);
    if(cross>inf0)return 1;
    else if(abs((a-spt)^(b-spt))<inf0)
        return dis(a,spt)<dis(b,spt);
    return 0;
}
vector<pit>convex_hull(vector<pit>dot)//按逆时针求凸包
{
    for(int i=1;i<dot.size();++i)
        if(dot[i][1]+inf0<dot[0][1]||(abs(dot[i][1]-dot[0][1])<inf0&&dot[i][0]<dot[0][0]))
            swap(dot[i],dot[0]);
    spt=dot[0];
    sort(dot.begin()+1,dot.end(),cmp);
//    for(int i=0;i<dot.size();++i)cout<<dot[i][0]<<"|"<<dot[i][1]<<endl;
    stack<pit>s;
    s.push(dot[0]);
    for(int i=1;i<dot.size();++i)
    {
        while(1)
        {
            if(s.size()<=1)break;
            pit b=s.top();s.pop();
            pit a=s.top();s.push(b);
            double cross=(b-a)^(dot[i]-a);
            if(cross<-inf0||abs(cross)<inf0)s.pop();
            else break;
        }
        s.push(dot[i]);
    }
    vector<pit>ans;
    while(s.size())//在s里是逆序存放，输出成倒序，所以为顺时针
    {
        ans.push_back(s.top());
        s.pop();
    }
    for(int i=0;i<ans.size()/2;++i)
        swap(ans[i],ans[ans.size()-1-i]);
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n;cin>>n;
    vector<pit>dot;
    for(int i=1;i<=n;++i)
    {
        pit x;
        cin>>x[0]>>x[1];
        dot.push_back(x);
    }
    dot=convex_hull(dot);
//    for(int i=0;i<dot.size();++i)
//        cout<<dot[i][0<<"||"<<dot[i][1]<<endl;
    double ans=0;
    for(int i=0;i<dot.size();++i)
        ans+=dis(dot[i],dot[(i+1)%dot.size()]);
    cout<<fixed<<setprecision(2)<<ans<<endl;
    return 0;
}
/*
叉积：
(x1,y1)^(x2,y2)=x1y2-x2y1>0：(x2,y2)在(x1,y1)左手边
(x1,y1)^(x2,y2)=x1y2-x2y1<0：(x2,y2)在(x1,y1)右手边
*/

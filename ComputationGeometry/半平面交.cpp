//http://poj.org/problem?id=1279
#include<iostream>
#include<deque>
#include<vector>
#include<cmath>
#include<assert.h>
#include<algorithm>
#include<iomanip>
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

struct line
{
    pit v,s;//direct, start point
};
bool cmp(line a,line b)
{
    double theta1=atan2(a.v[1],a.v[0]),theta2=atan2(b.v[1],b.v[0]);
    if(abs(theta1-theta2)<inf0)//碰到角度相同的向量只保留靠左的那个
        return (a.v^(b.s-a.s))<0;
    return atan2(a.v[1],a.v[0])<atan2(b.v[1],b.v[0]);
}
pit lineline(line a,line b)
{
    double A1=a.v[0],B1=-b.v[0],C1=a.s[0]-b.s[0];
    double A2=a.v[1],B2=-b.v[1],C2=a.s[1]-b.s[1];
    double t=-(C1*B2-C2*B1)/(A1*B2-A2*B1);
    return a.s+(a.v*t);
}
void Half_plane_Intersection(vector<line>a)
{
    vector<line>vec;
    sort(a.begin(),a.end(),cmp);
    vec.push_back(a[0]);
    for(int i=1;i<a.size();++i)
        if(abs(atan2(a[i].v[1],a[i].v[0])-atan2(a[i-1].v[1],a[i-1].v[0]))>inf0)
            vec.push_back(a[i]);
    deque<line>q;deque<pit>qdot;
    q.push_back(vec[0]),q.push_back(vec[1]),qdot.push_back(lineline(vec[0],vec[1]));
    for(int i=2;i<vec.size();++i)
    {
        while(!qdot.empty()&&(vec[i].v^(qdot.back()-vec[i].s))<inf0)//前一个点在新向量右边
            q.pop_back(),qdot.pop_back();
        while(!qdot.empty()&&(vec[i].v^(qdot.front()-vec[i].s))<inf0)//队头点在新向量右边
            q.pop_front(),qdot.pop_front();
        qdot.push_back(lineline(q.back(),vec[i]));
        q.push_back(vec[i]);
    }
    while(!qdot.empty()&&(q.front().v^(qdot.back()-q.front().s))<inf0)
        q.pop_back(),qdot.pop_back();
    while(!qdot.empty()&&(q.back().v^(qdot.front()-q.back().s))<inf0)
        q.pop_front(),qdot.pop_front();
    qdot.push_back(lineline(q.back(),q.front()));
    double ans=0;
    for(int i=1;i<qdot.size()-1;++i)
        ans+=abs((qdot[i]-qdot[0])^(qdot[i+1]-qdot[0]));
    cout<<fixed<<setprecision(3)<<ans/2<<endl;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    vector<line>a;
	int num;cin>>num;
    while(num--)
    {
        int n;cin>>n;
        vector<pit>dot;
        for(int i=0;i<n;++i)
        {
            double x,y;
            cin>>x>>y;
            dot.push_back((pit){x,y});
        }
        for(int i=0;i<dot.size();++i)//逆时针方向给出点，向量的左边是可行的区域
            a.push_back((line){dot[(i+1)%dot.size()]-dot[i],dot[i]});
    }
    Half_plane_Intersection(a);
    return 0;
}
/*
叉积：
(x1,y1)^(x2,y2)=x1y2-x2y1>0：(x2,y2)在(x1,y1)左手边
(x1,y1)^(x2,y2)=x1y2-x2y1<0：(x2,y2)在(x1,y1)右手边


atan2(y,x):=
arctan(y/x)       x>0
arctan(y/x)+pi    y>=0,x<0
arctan(y/x)-pi    y<0,x<0
+pi/2             y>0,x=0
-pi/2             y<0,x=0
undefined         y=0,x=0


极角排序后，向量从(-10,-1)到(10,1)绕一圈（数据只是打个比方）
*/

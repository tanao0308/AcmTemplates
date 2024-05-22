#include<bits/stdc++.h>
#define ll long long
using namespace std;
double eps=1e-9;
//------------------------------------------------------------
// Fundamental
//------------------------------------------------------------
int sgn(double x){
	if(x<-eps)return -1;
	if(x>eps)return 1;
	return 0;
}
//二次方程
bool Quadratic(double A,double B,double C,double*t0,double*t1){
	double discrim=B*B-4.f*A*C;
	if (discrim<0.)return false;
	double rootDiscrim=sqrt(discrim);
	double q;
	if(B<0)q=-.5f*(B-rootDiscrim);
	else q=-.5f*(B+rootDiscrim);
	*t0=q/A;
	*t1=C/q;
	if(*t0>*t1)swap(*t0,*t1);
	return true;
}
struct vec{
	double x,y;
	vec(){x=y=0;}
	vec(double _x,double _y){x=_x,y=_y;}
	vec operator+(vec v){return vec(x+v.x,y+v.y);}
	vec operator-(vec v){return vec(x-v.x,y-v.y);}
	vec operator*(double v){return vec(x*v,y*v);}
	vec operator/(double v){return vec(x/v,y/v);}
	double operator*(vec v){return x*v.x+y*v.y;}
	double len(){return hypot(x,y);}
	double len_sqr(){return x*x + y*y;}
	//逆时针旋转
	vec rotate(double c){return vec(x*cos(c)-y*sin(c),x*sin(c)+y*cos(c));}
	vec trunc(double l){return (*this)*l/len();}
	vec rot90(){return vec(-y,x);}
};
double cross(vec a,vec b){return a.x*b.y-a.y*b.x;}
//计算 a,b 间的角度
double get_angle(vec a,vec b){return fabs(atan2(fabs(cross(a,b)),a*b));}
//直线插值
vec lerp(vec a,vec b,double t){return a*(1-t)+b*t;}
//判断点是否在线段上(包含端点)
bool point_on_segment(vec p,vec a,vec b){
	return sgn(cross(b-a,p-a))==0&&sgn((p-a)*(p-b))<=0;
}
//判断线段ab,pq间是否有交点
int has_intersection(vec a,vec b,vec p,vec q){
	int d1=sgn(cross(b-a,p-a)),d2=sgn(cross(b-a,q-a));
	int d3=sgn(cross(q-p,a-p)),d4=sgn(cross(q-p,b-p));
	if(d1*d2<0&&d3*d4<0)
		return 1; //有交点，且交点不在端点
	if( (d1==0&&point_on_segment(p,a,b))||
		(d2==0&&point_on_segment(q,a,b))||
		(d3==0&&point_on_segment(a,p,q))||
		(d4==0&&point_on_segment(b,p,q)))
			return -1; //重合或交点在端点上
	return 0;
}
//直线求交点，需保证p!=q,a!=b（ab，pq为两条给定直线上的两点，o为交点）
int line_intersection(vec a,vec b,vec p,vec q,vec&o,double*t=0){
	double U=cross(p-a,q-p);
	double D=cross(b-a,q-p);
	if(sgn(D)==0)
		return sgn(U)==0?2:0;//重叠|平行
	o=a+(b-a)*(U/D);
	if(t)*t=U/D;
	return 1;
}
//点p到直线ab距离
double dist_point_to_line(vec p,vec a,vec b){
	return fabs(cross(p-a,b-a))/(b-a).len();
}
//点p到线段ab距离
double dist_point_to_segment(vec p,vec a,vec b){
	if((b-a).len()>eps&&sgn((p-a)*(b-a))>=0&&sgn((p-b)*(a-b))>=0)
		return fabs(cross(p-a,b-a))/(b-a).len();
	return min((p-a).len(),(p-b).len());
}
//------------------------------------------------------------
// Circle
//------------------------------------------------------------
struct circle{
	vec c;double r;
	circle(){c=vec(0,0),r=0;}
	circle(vec _c,double _r){c=_c,r=_r;}
	vec point(double a){return vec(c.x+r*cos(a),c.y+r*sin(a));}
};
const double PI=acos(-1.0);
//过点p做圆C的切线，返回切线个数。v[i]表示第i条切线的方向向量
int getTangents(vec p,circle C,vec*v){
	vec u=C.c-p;
	double dist=u.len();
	if(sgn(dist-C.r)<0)return 0;
	if(!sgn(dist-C.r)){
		v[0]=u.rot90();
		return 1;
	}
	double ang=asin(C.r/dist);
	v[0]=u.rotate(-ang);
	v[1]=u.rotate(ang);
	return 2;
}
// 121 //两圆的公切线
// 122 //返回切线的个数，-1表示有无数条公切线。
// 123 //a[i],b[i]表示第i条切线在圆A，圆B上的切点
// 124 int getTangents(circle A,circle B,vec*a,vec*b){
// 125 int cnt=0;
// 126 if(A.r<B.r)swap(A,B),swap(a,b);
// 127 double d2=(A.c.x-B.c.x)*(A.c.x-B.c.x)+(A.c.y-B.c.y)*(A.c.y-B.c.y);
// 128 double rdiff=A.r-B.r;
// 129 double rsum=A.r+B.r;
// 130 if(sgn(d2-rdiff*rdiff)<0)return 0;//内含
// 131 double base=atan2(B.c.y-A.c.y,B.c.x-A.c.x);
// 132 if(!sgn(d2)&&!sgn(A.r-B.r))return -1;//无限多条切线
// 133 if(!sgn(d2-rdiff*rdiff)){//内切一条切线
// 134 a[cnt]=A.point(base);
// 135 b[cnt]=B.point(base);
// 136 cnt++;
// 137 return 1;
// 138 }
// 139 //有外共切线
// 140 double ang=acos((A.r-B.r)/sqrt(d2));
// 141 a[cnt]=A.point(base+ang);b[cnt]=B.point(base+ang);cnt++;
// 142 a[cnt]=A.point(base-ang);b[cnt]=B.point(base-ang);cnt++;
// 143 if(!sgn(d2-rsum*rsum)){//一条公切线
// 144 a[cnt]=A.point(base);
// 145 b[cnt]=B.point(PI+base);
// 146 cnt++;
// 147 }else if(sgn(d2-rsum*rsum)>0){//两条公切线
// 148 double ang=acos((A.r+B.r)/sqrt(d2));
// 149 a[cnt]=A.point(base+ang);b[cnt]=B.point(PI+base+ang);cnt++;
// 150 a[cnt]=A.point(base-ang);b[cnt]=B.point(PI+base-ang);cnt++;
// 151 }
// 152 return cnt;
// 153 }

//圆直线交点，交点是lerp(a,b,*t0)和lerp(a,b,*t1)
bool circle_line_intersection(circle c,vec a,vec b,double*t0,double*t1){
	vec d=b-a;
	double A=d*d;
	double B=d*(a-c.c)*2.0;
	double C=(a-c.c).len_sqr()-c.r*c.r;
	return Quadratic(A,B,C,t0,t1);
}
// 164 //圆圆相交
// 165 bool circle_circle_intersection(circle a,circle b,vec &p1,vec &p2) {
// 166 double d = (a.c-b.c).len();
// 167 if( d > a.r + b.r || d < fabs(a.r-b.r) ) return false;//相离|内含
// 168 double l = ( (a.c-b.c).len_sqr() + a.r*a.r - b.r*b.r ) / (2*d);
// 169 double h = sqrt(a.r*a.r-l*l);
// 170 vec vl = (b.c-a.c).trunc(l),vh = vl.rot90().trunc(h);
// 171 p1 = a.c + vl + vh;
// 172 p2 = a.c + vl - vh;
// 173 return true;
// 174 }
// 175
// 176 //圆和三角形abo交的面积，o是圆心
// 177 double circle_triangle_intersection_area(circle c,vec a,vec b) {
// 178 if( sgn(cross(a-c.c,b-c.c)) == 0 ) return 0;
// 179 vec q[5];
// 180 int len = 0;
// 181 double t0,t1;
// 182 q[len++] = a;
// 183 if( circle_line_intersection(c,a,b,&t0,&t1) ) {
// 184 if( 0 <= t0 && t0 <= 1 ) q[len++] = lerp(a,b,t0);
// 185 if( 0 <= t1 && t1 <= 1 ) q[len++] = lerp(a,b,t1);
// 186 }
// 187 q[len++] = b;
// 188 double s = 0;
// 189 for(int i=1;i<len;++i) {
// 190 vec z = (q[i-1] + q[i])/2;
// 191 if( (z-c.c).len_sqr() <= c.r*c.r )
// 192 s += fabs( cross(q[i-1]-c.c,q[i]-c.c) ) / 2;
// 193 else
// 194 s += c.r*c.r*get_angle(q[i-1]-c.c,q[i]-c.c) / 2;
// 195 }
// 196 return s;
// 197 }
// 198
// 199 //------------------------------------------------------------
// 200 // Polygon
// 201 //------------------------------------------------------------
// 202 //多边形与圆交的面积
// 203 double circle_polygon_intersection_area(circle c,vec *v,int n) {
// 204 double s = 0;
// 205 for(int i=0;i<n;++i) {
// 206 int j = (i+1) % n;
// 207 s += circle_triangle_intersection_area(c,v[i],v[j])
// 208 * sgn( cross(v[i]-c.c,v[j]-c.c) );
// 209 }
// 210 return fabs(s);
// 211 }
// 212
// 213 //切割多边形
// 214 //顶点按逆时针给，保留有向直线a->b左侧的部分
// 215 int polygon_cut(vec *v,int n,vec a,vec &b,vec *o) {
// 216 int len = 0;
// 217 for(int i=0;i<n;++i) {
// 218 if( cross(v[i]-a,b-a) <= 0 ) o[len++] = v[i];
// 219 vec c;double t;
// 220 if( line_intersection(v[i],v[(i+1)%n],a,b,c,&t) && t > 0 && t < 1 )
// 221 o[len++] = c;
// 222 }
// 223 return len;
// 224 }
//判点在是否在多边形内或边上
bool point_in_polygon(vec*a,int n,vec p){
	int ret=0;
	for(int i=0;i<n;i++){
		vec u=a[i],v=a[(i+1)%n];
		if(point_on_segment(p,u,v))return 1;
		if(sgn(u.y-v.y)<=0)swap(u,v);
		if(sgn(p.y-u.y)>0||sgn(p.y-v.y)<=0)continue;
		ret+=sgn(cross(v-p,u-p))>0;
	}
	return ret&1;
}
//凸包, 不可有重复点
bool cmpXY(vec a,vec b){
	if(sgn(a.x-b.x))return a.x<b.x;
	return a.y<b.y;
}
int convex_hull(vec* v,int n,vec *z){
	sort(v,v+n,cmpXY);
	int m=0;
	for(int i=0;i<n;++i){
		while(m>1&&cross(z[m-1]-z[m-2],v[i]-z[m-2])<=0)--m;
		z[m++]=v[i];
	}
	int k=m;
	for(int i=n-2;i>=0;--i){
		while(m>k&&cross(z[m-1]-z[m-2],v[i]-z[m-2])<=0)--m;
		z[m++]=v[i];
	}
	if(n>1)--m;
	return m;
}
//返回多边形的重心，面积为 0 时需要特别处理
// point MassCenter(){
// 	point ans=point(0,0);
// 	if(sgn(area())==0)while(1);
// 	a[n]=a[0];
// 	for(int i=0;i<n;i++)ans=ans+(a[i]+a[i+1])*det(a[i+1],a[i]);
// 	return ans/area()/6.0;
// }
// 269 //------------------------------------------------------------
// 270 // Misc
// 271 //------------------------------------------------------------
// 272 //绕轴旋转矩阵,使用列向量,matrix::I()是单位阵
// 273 //注意：对应法线的变换矩阵是Inverse(Transpose(R))
// 274 //verified HDU 5388
// 275 matrix rotate(double x,double y,double z,double d) {
// 276 double len = sqrt( x*x + y*y + z*z );
// 277 x/=len;y/=len;z/=len;
// 278 matrix K;
// 279 K.v[0][1] = -z;K.v[0][2] = y;
// 280 K.v[1][0] = z;K.v[1][2] = -x;
// 281 K.v[2][0] = -y;K.v[2][1] = x;
// 282 return matrix::I() + K * sin(d) + K * K * (1 - cos(d));
// 283 }
//三角形面积，海伦公式，a,b,c为三边长
double get_triangle_area(double a,double b,double c){
	double s=(a+b+c)/2;
	return sqrt(s*(s-a)*(s-b)*(s-c));
}
int main()
{
	return 0;
}
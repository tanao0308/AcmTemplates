int sum[MAX_N];
void add(int x,int y){for(;x<=n;x+=(-x&x)){sum[x]+=y;}}
int query(int x,int y=0){for(;x;x-=(-x&x)){y+=sum[x];}return y;}

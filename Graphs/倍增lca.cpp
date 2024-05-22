//±¶Ôölca
int fa[MAX_N][20],dep[MAX_N];
void init(int u,int f)
{
    dep[u]=dep[f]+1;
    fa[u][0]=f;
    for(int i=1;i<20;++i)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(int i=p[u];i;i=e[i].next)
    {
        int v=e[i].v;
        if(v==f)continue;
        init(v,u);
    }
}
int cal_lca(int u,int v)
{
    if(dep[u]<dep[v])swap(u,v);
    for(int i=19;i>=0;--i)
        if(dep[fa[u][i]]>=dep[v])
            u=fa[u][i];
    if(u==v)return u;
    for(int i=19;i>=0;--i)
        if(fa[u][i]!=fa[v][i])
            u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
